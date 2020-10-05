#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#define CAPACIDAD_INICIAL 23
#define FACTOR_CARGA 0.7
#define FACTOR_REDIMENSION 2

typedef enum estado
{
    VACIO,
    OCUPADO,
    BORRADO
} estado_t;

typedef struct campo_hash
{
    char *clave;
    void *dato;
    estado_t estado;
} campo_hash_t;

struct hash
{
    campo_hash_t *tabla;
    size_t capacidad;
    size_t cantidad;
    size_t cantidad_borrados;
    hash_destruir_dato_t destruir_dato;
};

struct hash_iter
{
    hash_t *hash;
    size_t pos_actual;
    size_t ya_recorridos;
};

/***********************
    Funciones auxiliares.
************************/

/**
 * Devuelve un índice único (o al menos eso intenta) a partir de una cadena.
 * Implementado en base a el siguiente algorítmo: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 * La decisión se vio influenciada por este ser de luz: https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
 * */
int hashing(const char *clave, size_t capacidad);

/**
 * Busca la posición de la clave en el hash. Si no la encuentra, devuelve una posición donde el estado es vacío.
 * Es posible pasarle un long* (como precondición, inicializado en -1) para que guarde en éste la posición del primer 
 * borrado que encuentre en el recorrido (si no lo encuentra, el long* sigue apuntando a -1)
 * */
size_t buscar_posicion_clave(const hash_t *hash, size_t posicion, const char *clave, long *primer_borrado);

/**
 * Busca y devuelve la próxima posición ocupada a partir de la posición actual del iterador. Si no la encuentra,
 * devuelve una posición igual a la capacidad de la tabla de hash (posición inválida).
 * */
size_t buscar_proximo_ocupado(const hash_iter_t *iter, size_t posicion);

/**
 * Devuelve true si el hash está por sobre el factor de carga preestablecido para redimensionar hacia arriba, 
 * false en caso contrario.
 * */
bool hash_sobrecargado(hash_t *hash);

/**
 * Devuelve true si el hash está por debajo del factor de carga preestablecido para redimensionar hacia abajo, 
 * false en caso contrario.
 * */
bool hash_subcargado(hash_t *hash);

/**
 * Redimensiona el hash completo. Usamos esta función cuando nuestro hash está sobrecargado.
 * Devuelve false si hubo algún error, true en caso contrario.
 * */
bool hash_redimensionar(hash_t *hash, size_t nueva_capacidad);

/*****************************************************
    Primitivas Hash. Se implementó su versión cerrada. 
******************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato)
{
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;

    hash->tabla = malloc(sizeof(campo_hash_t) * CAPACIDAD_INICIAL); // Inicializamos la tabla
    if (!hash->tabla)
    {
        free(hash);
        return NULL;
    }
    for (size_t i = 0; i < CAPACIDAD_INICIAL; i++)
    {
        hash->tabla[i].estado = VACIO;
        hash->tabla[i].clave = NULL;
    }

    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->cantidad_borrados = 0;
    hash->destruir_dato = destruir_dato;

    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato)
{   
    if (hash_sobrecargado(hash) && !hash_redimensionar(hash, hash->capacidad * FACTOR_REDIMENSION))
        return false;

    long primer_borrado = -1;

    // Buscamos si está el elemento a guardar (si está, devuelve una pos. OCUPADA con la misma clave)
    size_t posicion = buscar_posicion_clave(hash, hashing(clave, hash->capacidad), clave, &primer_borrado);

    if (hash->tabla[posicion].estado == OCUPADO)
    { // Reemplazamos el dato
        if (hash->destruir_dato)
        {
            hash->destruir_dato(hash->tabla[posicion].dato); // Liberamos el dato anterior
        }
    }
    else 
    {                       
        if(primer_borrado >= 0) posicion = primer_borrado; // Si hubo un primer borrado, guardamos ahi, sino en el primer vacio
        char *nueva_clave = strdup(clave); // Duplicar la clave para evitar disgustos
        hash->tabla[posicion].estado = OCUPADO;
        hash->tabla[posicion].clave = nueva_clave;
        hash->cantidad++;
    }
    hash->tabla[posicion].dato = dato;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave)
{
    size_t posicion = buscar_posicion_clave(hash, hashing(clave, hash->capacidad), clave, NULL);

    if (hash->tabla[posicion].estado == VACIO)
        return NULL;

    if (hash_subcargado(hash) && !hash_redimensionar(hash, hash->capacidad / FACTOR_REDIMENSION))
        return false;

    free(hash->tabla[posicion].clave); // Liberamos clave
    hash->tabla[posicion].estado = BORRADO;
    hash->cantidad--;
    hash->cantidad_borrados++;
    return hash->tabla[posicion].dato;
}

void *hash_obtener(const hash_t *hash, const char *clave)
{
    size_t posicion = buscar_posicion_clave(hash, hashing(clave, hash->capacidad), clave, NULL);
    return hash->tabla[posicion].estado == VACIO ? NULL : hash->tabla[posicion].dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave)
{
    size_t posicion = buscar_posicion_clave(hash, hashing(clave, hash->capacidad), clave, NULL);
    return hash->tabla[posicion].estado == OCUPADO;
}

size_t hash_cantidad(const hash_t *hash)
{
    return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
    for (size_t i = 0; i < hash->capacidad; i++)
    {
        if (hash->tabla[i].estado != OCUPADO) continue;

        if (hash->destruir_dato)
        {
            hash->destruir_dato(hash_borrar(hash, hash->tabla[i].clave));
        }    
        else
        {
            hash_borrar(hash, hash->tabla[i].clave);
        }
    }
    free(hash->tabla);
    free(hash);
}

/**********************
    Primitivas Iterador
***********************/

hash_iter_t *hash_iter_crear(const hash_t *hash)
{
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));
    if (!iter)
        return NULL;

    iter->hash = (hash_t *)hash;

    if(hash->cantidad != 0)
    {
        iter->pos_actual = buscar_proximo_ocupado(iter, 0);
    }
    else 
    { // Aunque esto no es necesario para el funcionamiento, lo hacemos para mantener la invariante de la pos_actual
        iter->pos_actual = hash->capacidad;
    }

    iter->ya_recorridos = 0;
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter)
{
    if(hash_iter_al_final(iter)) return false;

    if(iter->ya_recorridos +1 == iter->hash->cantidad) // Si estaba en la última clave, voy directamente al final
    { 
        iter->pos_actual = iter->hash->capacidad; // Esta línea es para mantener la invariante de la pos_actual
        iter->ya_recorridos++;
        return true;
    }

    iter->pos_actual = buscar_proximo_ocupado(iter, ++iter->pos_actual);
    iter->ya_recorridos++;
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter)
{
    return hash_iter_al_final(iter) ? NULL : iter->hash->tabla[iter->pos_actual].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter)
{   
    return iter->ya_recorridos >= iter->hash->cantidad;
}

void hash_iter_destruir(hash_iter_t *iter)
{
    free(iter);
}

/****************************************
    Funciones auxiliares (implementación)
*****************************************/

int hashing(const char *clave, size_t capacidad)
{
    long int_max = 4294967296; // pow(2, 32)
    long prime = 16777619;
    long val = 2166136261;

    for (int i = 0; clave[i] != '\0'; i++)
    {
        val = val ^ clave[i];
        val = (val * prime) % int_max;
    }
    long resultado = val % capacidad;   // El corrector automático me obligó a hacerlo
    return (int) resultado;
}

size_t buscar_posicion_clave(const hash_t *hash, size_t posicion, const char *clave, long *primer_borrado)
{
    while(!( hash->tabla[posicion].estado == VACIO || (hash->tabla[posicion].estado == OCUPADO && strcmp(hash->tabla[posicion].clave, clave) == 0)))
    {
        if(primer_borrado && *primer_borrado == -1 && hash->tabla[posicion].estado == BORRADO)
            *primer_borrado = posicion;

        posicion++;
        if(posicion == hash->capacidad) posicion = 0;
    }
    return posicion;
}

size_t buscar_proximo_ocupado(const hash_iter_t *iter, size_t posicion)
{
    while (posicion < iter->hash->capacidad && iter->hash->tabla[posicion].estado != OCUPADO) {
        posicion++; 
    }
    return posicion;
}

bool hash_sobrecargado(hash_t *hash)
{   
    return (double) (hash->cantidad + hash->cantidad_borrados) / (double) hash->capacidad >= FACTOR_CARGA;
}

bool hash_subcargado(hash_t *hash)
{   
    return hash->capacidad > CAPACIDAD_INICIAL && 
        (hash->cantidad + hash->cantidad_borrados) <= FACTOR_CARGA * (double) hash->capacidad / (FACTOR_REDIMENSION * FACTOR_REDIMENSION);
}

bool hash_redimensionar(hash_t *hash, size_t nueva_capacidad)
{   
    size_t capacidad_anterior = hash->capacidad;
    campo_hash_t *tabla_anterior = hash->tabla;
    campo_hash_t *tabla_nueva = malloc(sizeof(campo_hash_t) * nueva_capacidad);

    if (!tabla_nueva)
        return false;

    hash->capacidad = nueva_capacidad;
    hash->tabla = tabla_nueva;
    hash->cantidad = 0;
    hash->cantidad_borrados = 0;

    for (int i = 0; i < nueva_capacidad; i++)
    {
        (tabla_nueva)[i].estado = VACIO;
        (tabla_nueva)[i].clave = NULL;
    }

    for (int j = 0; j < capacidad_anterior; j++)
    {
        if (tabla_anterior[j].estado != OCUPADO)
            continue;

        if (!hash_guardar(hash, tabla_anterior[j].clave, tabla_anterior[j].dato))
            return false;

        free(tabla_anterior[j].clave);
    }
    free(tabla_anterior);

    return true;
}