#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool redimensionar(pila_t* pila, size_t nueva_capacidad);

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
    pila->datos = malloc(pila->capacidad * sizeof(void*));

    if(pila->datos == NULL)
    {
        free(pila);
        return NULL;
    }

    return pila;
}

void pila_destruir(pila_t *pila)
{
    while(!pila_esta_vacia(pila))
    {
        free(pila_desapilar(pila));
    }
    free(pila->datos);
    free(pila);
}

void* pila_desapilar(pila_t *pila) 
{
    if(pila_esta_vacia(pila)) 
        return NULL;
    
    if(pila->cantidad <= pila->capacidad / 4 && pila->cantidad > CAPACIDAD_INICIAL) 
    {
        if(!redimensionar(pila, pila->capacidad / 2)) 
            return NULL;
    }

    pila->cantidad -= 1;
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
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void* valor)
{ 
    
    if(pila->cantidad == pila->capacidad)
    {
        if(!redimensionar(pila, pila->capacidad * 2))
            return false;
    }

    pila->datos[pila->cantidad] = valor;
    pila->cantidad += 1;

    return true;
}

bool redimensionar(pila_t* pila, size_t nueva_capacidad)
{
    void** aux = realloc(pila->datos, nueva_capacidad * sizeof(void*));

    if(aux == NULL || aux == 0)
        return false;

    pila->datos = aux;
    pila->capacidad = nueva_capacidad;
    return true;
}