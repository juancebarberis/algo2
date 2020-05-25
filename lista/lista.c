#include "lista.h"
#include <stdlib.h>

typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

struct lista_iter {
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
};

/**
 * PRIMITIVAS DE NODO
 * */

nodo_t* nodo_crear(void* dato, nodo_t* proximo)
{
    nodo_t* nodo = malloc(sizeof(nodo_t));
    
    if(!nodo) return NULL;

    nodo->dato = dato;
    nodo->proximo = proximo;

    return nodo;
}

/**
 * PRIMITIVAS DE LA LISTA
 * */

lista_t* lista_crear(void)
{
    lista_t* lista = malloc(sizeof(lista_t));

    if(!lista) return NULL;

    lista->largo = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;

    return lista;
}

bool lista_esta_vacia(const lista_t *lista)
{
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato)
{
    nodo_t* nuevo_nodo = nodo_crear(dato, lista->primero);

    if(!nuevo_nodo) return false;

    lista->primero = nuevo_nodo;

    if(!lista->ultimo)
        lista->ultimo = nuevo_nodo;
    
    lista->largo++;
    
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato)
{
    nodo_t* nuevo_nodo = nodo_crear(dato, NULL);

    if(!nuevo_nodo) return false;
    
    if(lista->ultimo)
        lista->ultimo->proximo = nuevo_nodo;
    
    if(!lista->primero)
        lista->primero = nuevo_nodo;

    lista->ultimo = nuevo_nodo;
    lista->largo++;

    return true;
}

void *lista_borrar_primero(lista_t *lista)
{
    if(lista_esta_vacia(lista)) return NULL;

    nodo_t* nodo_borrado = lista->primero;
    void* dato = nodo_borrado->dato;

    if(!lista->primero->proximo) 
    {
        lista->primero = NULL; 
        lista->ultimo = NULL;
    }
    else
    {
        lista->primero = lista->primero->proximo;
    }

    free(nodo_borrado);
    lista->largo--;

    return dato;
}

void *lista_ver_primero(const lista_t *lista)
{
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t *lista)
{
    return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista)
{
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *))
{
    while(!lista_esta_vacia(lista))
    {
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato)
            (*destruir_dato)(dato);
    }
    free(lista);
}


/**
 * PRIMITIVAS DEL ITERADOR INTERNO
 * */

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra)
{
    nodo_t* actual = lista->primero;

    while(actual && visitar(actual->dato, extra))
    {
        actual = actual->proximo;
    }
}

/**
 * PRIMITIVAS DEL ITERADOR EXTERNO
 * */

lista_iter_t *lista_iter_crear(lista_t *lista)
{
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));

    if(!iter) return NULL;

    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter)
{
    if(lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)) 
        return false;

    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;

    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter)
{
    return iter->actual ? iter->actual->dato : NULL;
}

bool lista_iter_al_final(const lista_iter_t *iter)
{
    return !iter->actual || iter->actual == iter->lista->ultimo  ? true : false;
}

void lista_iter_destruir(lista_iter_t *iter)
{
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato)
{
    bool resultado = true;
    if(!iter->anterior && lista_insertar_primero(iter->lista, dato)) 
    {
        iter->actual = iter->lista->primero;
    }
    else if(lista_iter_al_final(iter) && lista_insertar_ultimo(iter->lista, dato))
    {
        iter->actual->proximo = iter->lista->ultimo;
        iter->actual = iter->lista->ultimo;
    }
    else 
    {
        nodo_t* nuevo_nodo = nodo_crear(dato, iter->actual);

        if(!nuevo_nodo && !lista_insertar_primero(iter->lista, dato)) 
            resultado = false;
        else
        {
            iter->anterior->proximo = nuevo_nodo;
            iter->actual = nuevo_nodo;
            iter->lista->largo++;
        }
    }
    return resultado;
}

void *lista_iter_borrar(lista_iter_t *iter)
{
    if(lista_esta_vacia(iter->lista)) return NULL;

    if(!iter->anterior || lista_largo(iter->lista) == 1)
    {
        iter->actual = iter->actual->proximo;
        return lista_borrar_primero(iter->lista);
    }

    nodo_t* nodo_proximo = iter->actual->proximo;
    void* dato = iter->actual->dato;
    free(iter->actual);

    if(!nodo_proximo) 
    {
        iter->anterior->proximo = NULL;
        iter->actual = iter->anterior;
        iter->lista->ultimo = iter->actual;
    }
    else
    {
        iter->actual = nodo_proximo;
        iter->anterior->proximo = nodo_proximo;
    }
    iter->lista->largo--;

    return dato;
}  