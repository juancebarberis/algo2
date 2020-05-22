#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


/**
 * Definición de estructuras de datos
 * */

typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;


/**
 * PRIMITIVAS DE LA LISTA
 * */

/**
 * Crea una nueva lista (vacía).
 * */
lista_t *lista_crear(void);

/**
 * Devuelve true si la lista está vacía, false en caso contrario.
 * Pre: la lista fue creada.
 * */
bool lista_esta_vacia(const lista_t *lista);

/**
 * Inserta un nuevo elemento al principio de la lista. Devuelve false en caso
 * de no poder alojar el nuevo dato en memoria. True si se guardó correctamente.
 * Pre: la lista fue creada.
 * */
bool lista_insertar_primero(lista_t *lista, void *dato);

/**
 * Inserta un elemento al final de la lista. Devuelve false si no se pudo
 * alojar el nuevo dato en memoria. True si se guardó correctamente.
 * Pre: la lista fue creada.
 * */
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/**
 * Borra el primer elemento de la lista y devuelve el dato que estaba almacenado allí.
 * Si la lista está vacía, devuelve NULL.
 * Pre: la lista fue creada.
 * */
void *lista_borrar_primero(lista_t *lista);

/**
 * Devuelve el dato que se encuentra en la primera posición de la lista.
 * Si la lista está vacía, devuelve NULL.
 * Pre: la lista fue creada.
 * */
void *lista_ver_primero(const lista_t *lista);

/**
 * Devuelve el dato que se encuentra al final de la lista.
 * Si la lista está vacía, devuelve NULL.
 * Pre: la lista fue creada.
 * */
void *lista_ver_ultimo(const lista_t* lista);

/**
 * Devuelve el largo de la lista.
 * Pre: la lista fue creada.
 * */
size_t lista_largo(const lista_t *lista);

/**
 * Destruye la lista y todos sus elementos.
 * Pre: la lista fue creada.
 * */
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/**
 * PRIMITIVAS DEL ITERADOR INTERNO
 * */

/**
 * Itera la lista hasta que visitar devuelva false. En caso de que visitar no devuelva false,
 * se itera hasta el último elemento de la lista.
 * Pre: la lista fue creada.
 * */
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/**
 * PRIMITIVAS DEL ITERADOR EXTERNO
 * */

/**
 * Crea un iterador para la lista recibida por parámetro.
 * Inicializa en la primera posición de la lista.
 * */
lista_iter_t *lista_iter_crear(lista_t *lista);

/**
 * Avanza una posición la iteración. Devuelve false en caso de que esté al final
 * de la iteración.
 * Pre: el iterador fue creado
 * */
bool lista_iter_avanzar(lista_iter_t *iter);

/**
 * Devuelve el dato que se encuentra en la misma posición que el iterador.
 * Devuelve NULL si la lista que se está iterando está vacía.
 * Pre: el iterador fue creado
 * */
void *lista_iter_ver_actual(const lista_iter_t *iter);

/**
 * Devuelve True si el iterador se encuentra al final de la lista.
 * Pre: el iterador fue creado.
 * */
bool lista_iter_al_final(const lista_iter_t *iter);

/**
 * Destruye el iterador.
 * Pre: el iterador fue creado.
 * */
void lista_iter_destruir(lista_iter_t *iter);

/**
 * Inserta un nuevo elemento en la lista antes del elemento actual.
 * Pre: el iterador fue creado.
 * */
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/**
 * Borra el elemento actual que se esté iterando.
 * Pre: el iterador fue creado.
 * Post: el elemento ya no se encuentra en la lista.
 * */
void *lista_iter_borrar(lista_iter_t *iter);


/**
 * Pruebas unitarias del alumno
 * */

void pruebas_lista_alumno(void);

/**
 * Ejemplo de iteradores
 * */
void ejemplo_iteradores();

#endif