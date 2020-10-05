#define CAPACIDAD_INICIAL 16
#define FACTOR_REDIMENSION 2
#include "heap.h"
#include <stdlib.h>

struct heap
{
  void **arreglo;
  cmp_func_t cmp;
  size_t cantidad;
  size_t capacidad;
};

/************************************
  Declaración funciones auxiliares.
*************************************/

/**
 * Redimensiona el arreglo del heap a la nueva_capacidad
*/
bool heap_redimensionar(heap_t *heap, size_t nueva_capacidad)
{
  void **nuevo_arreglo = realloc(heap->arreglo, nueva_capacidad * sizeof(void *));
  if (!nuevo_arreglo)
    return false;

  heap->arreglo = nuevo_arreglo;
  heap->capacidad = nueva_capacidad;

  return true;
}

/**
 * Intercambia en el arreglo el elemento de la posición a con el de la posición b. Como precondición, 
 * ambas posiciones deben ser válidas. 
*/
void swap(void **arreglo, size_t a, size_t b)
{
  void *aux = arreglo[a];
  arreglo[a] = arreglo[b];
  arreglo[b] = aux;
}

/**
 * Dada una posición del hijo izq, analiza el hijo izq e hijo derecho: 
 * en caso de ser ambas posiciones válidas devuelve la posición del que tenga 
 * el dato de mayor prioridad según cmp. Si solamente la posición del hijo izq es válida, devuelve esta. Como precondición,
 * la posición del hijo izq debe ser válida. 
*/
size_t pos_hijo_maximo(heap_t *heap, size_t pos_izq) // HACER QUE RECIBA SOLAMENTE POS_IZQ PUES pos_der == pos_izq+1
{
  if (heap->cantidad - 1 == pos_izq) // Si la posición derecha es inválida
    return pos_izq;

  void *izq = heap->arreglo[pos_izq];
  void *der = heap->arreglo[pos_izq + 1];

  if (heap->cmp(izq, der) >= 0)
    return pos_izq;

  return pos_izq + 1;
}

void upheap(heap_t *heap, int posicion)
{
  if (posicion <= 0)
    return;

  int pos_padre = (posicion - 1) / 2;

  if (heap->cmp(heap->arreglo[pos_padre], heap->arreglo[posicion]) >= 0)
    return;

  swap(heap->arreglo, pos_padre, posicion);
  upheap(heap, pos_padre);
}

void downheap(heap_t *heap, size_t pos_padre)
{
  size_t pos_h_izq = (2 * pos_padre) + 1;

  if (heap->cantidad <= pos_h_izq)
    return; // Caso base: si no tiene hijos

  size_t pos_hijo_max = pos_hijo_maximo(heap, pos_h_izq);

  if (heap->cmp(heap->arreglo[pos_padre], heap->arreglo[pos_hijo_max]) >= 0)
  {
    return;
  }
  else
  {
    swap(heap->arreglo, pos_padre, pos_hijo_max);
    downheap(heap, pos_hijo_max);
  }
}

void heapify(heap_t *heap)
{
  for (size_t i = 1; i < heap->cantidad + 1; i++)
  {
    downheap(heap, heap->cantidad - i);
  }
}

/*******************
    Primitivas Heap.
********************/

heap_t *heap_crear(cmp_func_t cmp)
{
  heap_t *heap = malloc(sizeof(heap_t));

  if (!heap)
    return NULL;

  heap->cantidad = 0;
  heap->capacidad = CAPACIDAD_INICIAL;
  heap->cmp = cmp;

  void **arreglo = malloc(sizeof(void *) * heap->capacidad);

  if (!arreglo)
  {
    free(heap);
    return NULL;
  }

  heap->arreglo = arreglo;

  return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp)
{
  heap_t *heap = heap_crear(cmp);

  if (!heap)
    return NULL;

  if (n * 2 >= heap->capacidad && !heap_redimensionar(heap, n * FACTOR_REDIMENSION))
    return NULL;

  for (size_t i = 0; i < n; i++)
  {
    heap->arreglo[i] = arreglo[i];
  }

  heap->cantidad = n;

  heapify(heap);

  return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e))
{
  void *actual = heap_desencolar(heap);
  while (actual)
  {
    if (!destruir_elemento)
      break;

    destruir_elemento(actual);
    actual = heap_desencolar(heap);
  }
  free(heap->arreglo);
  free(heap);
}

size_t heap_cantidad(const heap_t *heap)
{
  return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap)
{
  return heap->cantidad == 0;
}

bool heap_encolar(heap_t *heap, void *elem)
{
  if (!elem)
    return false;

  if (heap->cantidad == heap->capacidad && !heap_redimensionar(heap, heap->capacidad * FACTOR_REDIMENSION))
    return false;

  heap->arreglo[heap->cantidad] = elem;

  heap->cantidad++;
  upheap(heap, (int) heap->cantidad - 1);

  return true;
}

void *heap_ver_max(const heap_t *heap)
{
  if (heap_esta_vacio(heap))
    return NULL;

  return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap)
{
  if (heap_esta_vacio(heap))
    return NULL;

  if (FACTOR_REDIMENSION * FACTOR_REDIMENSION * heap->cantidad <= heap->capacidad && heap->capacidad > CAPACIDAD_INICIAL)
  {
    if (!heap_redimensionar(heap, heap->capacidad / FACTOR_REDIMENSION))
      return false;
  }

  void *saliente = heap->arreglo[0];

  swap(heap->arreglo, 0, heap->cantidad - 1);
  heap->cantidad--;
  downheap(heap, 0);

  return saliente;
}

/*************************
 * Heap Sort implementación
 * ***********************/

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{
  heap_t *heap = heap_crear(cmp);

  if (!heap)
    return;

  free(heap->arreglo);

  heap->arreglo = elementos;
  heap->cantidad = cant;

  heapify(heap);

  for (size_t i = 1; i < cant; i++)
  {
    swap(heap->arreglo, 0, cant - i);
    heap->cantidad--;
    downheap(heap, 0);
  }

  free(heap);
}