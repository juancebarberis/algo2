#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool redimensionar(pila_t* pila);

#define CAPACIDAD_INICIAL 4

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void) 
{
    pila_t* pila = malloc(sizeof(pila_t));

    if(!pila) 
        return NULL;
    
    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = 0;
    pila->datos = malloc(pila->capacidad);

    return pila;
}

void pila_destruir(pila_t *pila)
{
    free(pila->datos);
    free(pila);
}

void* pila_desapilar(pila_t *pila) 
{
    if(pila_esta_vacia(pila)) 
        return NULL;
    
    pila->cantidad -= 1;

    if(pila->cantidad * pila->cantidad >= pila->capacidad / 4) 
    {
        pila->capacidad /= 2;
        if(!redimensionar(pila)) 
            return NULL;
    }
    void* dato_desapilado = pila->datos[pila->cantidad];
    pila->datos[pila->cantidad] = NULL;
    
    return dato_desapilado;
}

void* pila_ver_tope(const pila_t *pila)
{
    return pila_esta_vacia(pila) ? NULL : pila->datos[pila->cantidad - 1];
}

bool pila_esta_vacia(const pila_t *pila)
{
    return pila->cantidad == 0 ? true : false;
}

bool pila_apilar(pila_t *pila, void* valor)
{ 
    pila->cantidad += 1;
    
    if(pila->cantidad * pila->cantidad >= pila->capacidad / 4)
    {
        pila->capacidad *= 4;
        if(!redimensionar(pila))
            return false;
    }

    pila->datos[pila->cantidad - 1] = valor;

    return true;
}

bool redimensionar(pila_t* pila)
{
    void** aux = realloc(pila->datos, pila->capacidad);

    if(aux == NULL || aux == 0)
        return false;

    pila->datos = aux;
    return true;
}