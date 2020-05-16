#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * DEFINICIONES
 * */

typedef struct nodo nodo_t;

nodo_t* nodo_crear(void* dato);

void nodo_destruir(nodo_t* nodo);


/**
 * ESTRUCTURAS
 * */

typedef struct nodo {
    void* dato;
    nodo_t* proximo;
} nodo_t;

typedef struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
} cola_t;


/**
 * PRIMITIVAS
 * */
 
cola_t* cola_crear(void)
{
    cola_t* cola = malloc(sizeof(cola_t));

    if(!cola) return NULL;

    cola->primero = NULL;
    cola->ultimo = NULL;

    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void*))
{
    while(!cola_esta_vacia(cola))
    {
        if(destruir_dato)
            (*destruir_dato)(cola_desencolar(cola));
        else
            cola_desencolar(cola);
    }
    free(cola);
}


bool cola_encolar(cola_t *cola, void* valor) 
{
    nodo_t* nuevo_nodo = nodo_crear(valor);
    if(!nuevo_nodo) 
        return false;
    
    if(cola_esta_vacia(cola)) 
        cola->primero = nuevo_nodo;
    else 
        cola->ultimo->proximo = nuevo_nodo;
    
    cola->ultimo = nuevo_nodo;

    return true;
}

void* cola_desencolar(cola_t *cola)
{
    if(cola_esta_vacia(cola))
        return NULL;

    nodo_t* nodo_desencolado = cola->primero;
    void* dato_desencolado = nodo_desencolado->dato;
    
    if(cola->primero->proximo == NULL)
        cola->primero = NULL;
    else
        cola->primero = cola->primero->proximo;

    nodo_destruir(nodo_desencolado);
    
    return dato_desencolado;
}

bool cola_esta_vacia(const cola_t *cola)
{
    return !cola->primero;
}

void* cola_ver_primero(const cola_t *cola)
{
    return cola_esta_vacia(cola) ? NULL : cola->primero->dato;
}


/**
 * AUXILIARES
 * */

nodo_t* nodo_crear(void* dato)
{
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if(!nodo) return NULL;

    nodo->dato = dato;
    nodo->proximo = NULL;

    return nodo;
}

void nodo_destruir(nodo_t* nodo)
{
    free(nodo);
}
