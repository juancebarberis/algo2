#ifndef ABB_H
#define ABB_H

#include<stdlib.h>
#include<stdbool.h>

typedef struct abb abb_t;

typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

/**
 * Crea un nuevo ABB. Recibe una función (ptr) de comparación y una función (ptr) para destruir los datos al borrar o pisar.
 * En caso de que falle, devuelve NULL. 
 * */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/**
 * Guarda un nuevo elemento en el ABB referenciado por la clave recibida.
 * Devuelve false en caso de que se produzca un error.
 * Pre: La estructura ABB fue inicializada
 * */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/**
 * Borra el elemento que se encuentre referenciado por una clave.
 * Si el elemento no se encuentra, devuelve NULL.
 * Pre: La estructura ABB fue inicializada
 * */
void *abb_borrar(abb_t *arbol, const char *clave);

/**
 * Devuelve el elemento (ptr) referenciado por la clave.
 * Si el elemento no se encuentra, devuelve NULL.
 * Pre: La estructura ABB fue inicializada
 * */
void *abb_obtener(const abb_t *arbol, const char *clave);

/**
 * Devuelve true si existe un elemento asociado a dicha clave en el ABB.
 * En caso contrario, devuelve false.
 * Pre: La estructura ABB fue inicializada
 * */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/**
 * Devuelve la cantidad de elementos que contiene el ABB.
 * Pre: La estructura ABB fue inicializada
 * */
size_t abb_cantidad(abb_t *arbol);

/**
 * Destruye el ABB y todos sus datos asociados, por medio de la función (ptr), obtenida en abb_crear(). 
 * Pre: La estructura ABB fue inicializada
 * */
void abb_destruir(abb_t *arbol);

/**
 * Itera el ABB usando la función visitar que recibe la clave, el valor y un puntero extra, y devuelve true si se debe seguir iterando, 
 * false en caso contrario.
 * Pre: La estructura ABB fue inicializada.
 * */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

void abb_por_rangos(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, const char* inicio, const char* fin);

// Iterador externo

/**
 * Crea un nuevo iterador externo.
 * Devuelve NULL en caso de que no pueda inicializarse.
 * Pre: La estructura ABB fue inicializada
 * */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/**
 * Avanza a la siguiente posición de iteración siguiento un patrón 'in order' y devuelve true si fue posible avanzar.
 * Si no pudo avanzar, devuelve false.
 * */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/**
 * Devuelve la clave actual sobre la cual el iterador está iterando.
 * En caso de que el iterador se encuentre al final, o el ABB esté vacío, devuelve NULL; 
 * */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/**
 * Devuelve true si el iterador se encuentra al final, sino, false.
 * */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/**
 * Destruye el iterador.
 * */
void abb_iter_in_destruir(abb_iter_t* iter);

#endif