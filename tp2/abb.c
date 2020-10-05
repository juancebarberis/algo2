#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"

typedef struct nodo
{
    char* clave;
    void* dato;
    struct nodo* nodo_izq;
    struct nodo* nodo_der;
} nodo_t;

struct abb
{
    nodo_t* raiz;
    abb_destruir_dato_t destruir_dato;
    abb_comparar_clave_t comparar_dato;
    size_t cantidad;
};

struct abb_iter
{
    const abb_t* arbol;   
    pila_t* pila;
};


/************************************
    Declaración funciones auxiliares.
*************************************/

/**
 * Crea un nuevo nodo para el árbol. Si no puede hacer malloc, devuelve NULL.
 * */
nodo_t* crear_nodo(char* clave, void* dato);

/**
 * Libera la memoria del nodo y la de su clave asociada.
 * */
void destruir_nodo(nodo_t* nodo);

/**
 * Busca un nodo en el árbol recursivamente. Si no lo encuentra, devuelve NULL. Además, se le debe pasar
 * un nodo_t** donde se guardará el puntero del padre del nodo devuelto (si se devolvió NULL, el último nodo en el camino).
 * Si no se modifica el valor de padre, quiere decir que el nodo buscado es la raíz del árbol.
 * */
nodo_t* buscar_nodo(const abb_t* arbol, const char* clave, nodo_t* actual, nodo_t** padre);

/**
 * Devuelve true si hijo es hijo izquierdo de padre, false si es hijo derecho.
 * */
bool es_hijo_izq(nodo_t* hijo, nodo_t* padre);

/**
 * Devuelve el reemplazante del nodo. En este caso, el reemplazante que se devuelve es el nodo
 * más a la izquierda del hijo derecho del nodo (o sea, el mayor que le sigue a nodo en todo el árbol). Además,
 * se le debe pasar un nodo_t** donde se guardará un puntero al padre del reemplazante. Al llamarse, padre_reemplazante
 * debe apuntar a nodo. 
 * */
nodo_t* obtener_reemplazante(nodo_t* nodo, nodo_t** padre_reemplazante);

/**
 * Apila los nodos izquierdos recursivamente.
 * */
void apilar_nodos(pila_t* pila, nodo_t* nodo);

/*****************
    Primitivas ABB.
******************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) 
{
    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol) return NULL;

    arbol->raiz = NULL;
    arbol->cantidad = 0;
    arbol->comparar_dato = cmp;
    arbol->destruir_dato = destruir_dato;

    return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato)
{   
    nodo_t* padre = NULL; 
    nodo_t* nodo = buscar_nodo(arbol, clave, arbol->raiz, &padre);

    if(!nodo){ // Si la clave no estaba en el árbol
        nodo_t* nodo_nuevo = crear_nodo((char*)clave, dato); 
        if(!nodo_nuevo) return false;

        if(!padre)
        { // Si el árbol está vacío
            arbol->raiz = nodo_nuevo;
        } 
        else if(arbol->comparar_dato(clave, padre->clave) < 0)
        {
            padre->nodo_izq = nodo_nuevo;
        }
        else
        {
            padre->nodo_der = nodo_nuevo;
        }  

        arbol->cantidad++;
        return true;
    }

    //Reemplazamos el dato, pues la clave ya estaba
    if(arbol->destruir_dato)
        arbol->destruir_dato(nodo->dato);

    nodo->dato = dato;
    return true;
}

void *_abb_borrar(abb_t *arbol, const char *clave, nodo_t* nodo_a_borrar_previo, nodo_t* padre_de_nodo_a_borrar_previo)
{   
    void* dato_a_devolver;
    nodo_t* padre = padre_de_nodo_a_borrar_previo;
    nodo_t* nodo_a_borrar;

    if(!nodo_a_borrar_previo)
    {
        nodo_a_borrar = buscar_nodo(arbol, clave, arbol->raiz, &padre);
    }   
    else
    {
        nodo_a_borrar = nodo_a_borrar_previo;
    } 
    
    if(!nodo_a_borrar) return NULL;

    if(!(nodo_a_borrar->nodo_izq || nodo_a_borrar->nodo_der)) // Si no tiene ningun hijo
    {
        if(!padre)
        { // Si es la raíz
            arbol->raiz = NULL;
        }  
        else if(es_hijo_izq(nodo_a_borrar, padre))
        {
            padre->nodo_izq = NULL;
        }  
        else
        {
            padre->nodo_der = NULL;
        }     
    }
    else if(nodo_a_borrar->nodo_izq && nodo_a_borrar->nodo_der) // Si tiene los dos hijos
    { 
        nodo_t* padre_remplazante = nodo_a_borrar;
        nodo_t* reemplazante = obtener_reemplazante(nodo_a_borrar, &padre_remplazante);
        
        free(nodo_a_borrar->clave);
        dato_a_devolver = nodo_a_borrar->dato;

        nodo_a_borrar->clave = strdup(reemplazante->clave);
        nodo_a_borrar->dato = reemplazante->dato;

        reemplazante->dato = dato_a_devolver; 
    
        return _abb_borrar(arbol, reemplazante->clave, reemplazante, padre_remplazante); 
    }
    else // Si tiene solamente un hijo
    { 
        nodo_t* nieto;
        if(nodo_a_borrar->nodo_izq)
            nieto = nodo_a_borrar->nodo_izq;
        else 
            nieto = nodo_a_borrar->nodo_der;

        if(!padre) // Si el nodo a eliminar es la raíz
            arbol->raiz = nieto;
        else if(es_hijo_izq(nodo_a_borrar, padre)) // Acá el "padre" sería el abuelo del nieto
            padre->nodo_izq = nieto;  
        else
            padre->nodo_der = nieto;
    }
    
    dato_a_devolver = nodo_a_borrar->dato;
    destruir_nodo(nodo_a_borrar);
    arbol->cantidad--;
    return dato_a_devolver;
}

void *abb_borrar(abb_t *arbol, const char *clave){ // Wrap de _abb_borrar
    return _abb_borrar(arbol, clave, NULL, NULL);
}

void *abb_obtener(const abb_t *arbol, const char *clave)
{
    nodo_t* nodo = buscar_nodo(arbol, clave, arbol->raiz, NULL);
    return nodo ? nodo->dato : NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave)
{   
    return buscar_nodo(arbol, clave, arbol->raiz, NULL);
}

size_t abb_cantidad(abb_t *arbol)
{
    return arbol->cantidad;
}

void _abb_destruir(abb_t *arbol, nodo_t* actual) 
{
    if(!actual) return;
    
    // Recorrido Post-order
    _abb_destruir(arbol, actual->nodo_izq);
    _abb_destruir(arbol, actual->nodo_der);

    void* dato_del_borrado = abb_borrar(arbol, actual->clave);
    if(arbol->destruir_dato)
        arbol->destruir_dato(dato_del_borrado);
}

void abb_destruir(abb_t *arbol) // Wrap de _abb_destruir
{   
    _abb_destruir(arbol, arbol->raiz);
    free(arbol);
}

/*******************************
    Iterador interno.
********************************/

void _abb_in_order(bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, bool *cortar)
{   
    if(! actual || *cortar) return;
    
    _abb_in_order(visitar, extra, actual->nodo_izq, cortar);

    if(! *cortar && ! visitar(actual->clave, actual->dato, extra))
        *cortar = true;

    _abb_in_order(visitar, extra, actual->nodo_der, cortar);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra)
{   
    bool cortar = false;
    _abb_in_order(visitar, extra, arbol->raiz, &cortar);
}

void _abb_por_rangos(bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, const char* inicio, const char* fin, bool *cortar)
{   
    if(!actual || *cortar) return;
    
    if(inicio[0] == '\0' || strcmp(inicio, actual->clave) <= 0) {
        _abb_por_rangos(visitar, extra, actual->nodo_izq, inicio, fin, cortar);
    }
    
    if((inicio[0] == '\0' || strcmp(inicio, actual->clave) <= 0) && (fin[0] == '\0' || strcmp(actual->clave, fin) <= 0))
    {
        if(! *cortar && ! visitar(actual->clave, actual->dato, extra))
        {
            *cortar = true;
        }  
    } 
    
    if(fin[0] == '\0' || strcmp(actual->clave, fin) <= 0) {
        _abb_por_rangos(visitar, extra, actual->nodo_der, inicio, fin, cortar);
    }
}

void abb_por_rangos(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, const char* inicio, const char* fin)
{   
    bool cortar = false;
    _abb_por_rangos(visitar, extra, arbol->raiz, inicio, fin, &cortar);
}

/*******************************
    Primitivas Iterador externo.
********************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;

    pila_t* pila = pila_crear();
    if(!pila) return NULL;

    iter->pila = pila;
    iter->arbol = arbol;
    apilar_nodos(pila, arbol->raiz);

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if(abb_iter_in_al_final(iter)) return false;
    
    nodo_t* nodo_desapilado = pila_desapilar(iter->pila);
    apilar_nodos(iter->pila, nodo_desapilado->nodo_der);

    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    nodo_t* nodo = pila_ver_tope(iter->pila);
    return nodo ? nodo->clave : NULL;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    //return pila_esta_vacia(iter->pila);
    return pila_ver_tope(iter->pila) == NULL;
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}

/************************
    Funciones auxiliares.
*************************/

nodo_t* crear_nodo(char* clave, void* dato) 
{
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;

    nodo->clave = strdup(clave);
    nodo->dato = dato;
    nodo->nodo_izq = NULL;
    nodo->nodo_der = NULL;

    return nodo;
}

void destruir_nodo(nodo_t* nodo) 
{
    free(nodo->clave);
    free(nodo);
}

nodo_t* buscar_nodo(const abb_t* arbol, const char* clave, nodo_t* actual, nodo_t** padre) 
{   
    if(!actual) return NULL; // Si llega a un árbol nulo, no existe la clave
    
    int comparativa = arbol->comparar_dato(clave, actual->clave); 

    if(comparativa == 0)
        return actual;

    if(padre) *padre = actual; 

    if(comparativa < 0)
    {
        return buscar_nodo(arbol, clave, actual->nodo_izq, padre);
    }
    if(comparativa > 0)
    {
        return buscar_nodo(arbol, clave, actual->nodo_der, padre);
    }
    return NULL;
}

bool es_hijo_izq(nodo_t* hijo, nodo_t* padre){
    return padre->nodo_izq == hijo;
}

nodo_t* obtener_reemplazante(nodo_t* nodo, nodo_t** padre_reemplazante){
    nodo_t* actual = nodo->nodo_der;

    while(actual && actual->nodo_izq)
    {
        *padre_reemplazante = actual;
        actual = actual->nodo_izq;
    }
    return actual;
}   

void apilar_nodos(pila_t* pila, nodo_t* nodo) {
    if(!nodo || !pila_apilar(pila, nodo)) return;

    apilar_nodos(pila, nodo->nodo_izq);
}