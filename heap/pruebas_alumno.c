#include "testing.h"
#include "heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int funcion_cmp_str(const void *a, const void *b){
  return strcmp((const char*)a, (const char*)b);
}

int funcion_cmp_int(const void *a, const void *b){
  return *(int*)a >= *(int*)b ? 1 : -1;
}

int funcion_cmp_int_inversa(const void *a, const void *b){
  return *(int*)a < *(int*)b ? 1 : -1;
}

void prueba_crear_heap_vacio()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_str);

  print_test("Prueba heap crear heap vacio", heap);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver_max es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
}

void prueba_heap_encolar()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_int);
  print_test("Prueba heap encolar", heap);

  int dato1 = 1;
  int dato2 = 2; 
  int dato3 = 3; 

  // Se encola un dato y luego se lo borra
  print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato1));
  print_test("Prueba heap la cantidad de datos es 1", heap_cantidad(heap) == 1);
  print_test("Prueba heap ver max es el dato1", heap_ver_max(heap) == &dato1);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));
  print_test("Prueba heap desencolar, se obtiene dato1", heap_desencolar(heap) == &dato1);
  print_test("Prueba heap crear heap vacio", heap);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver_max es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));

  // Se encolan otros dos datos y no se borran, se destruyen con el heap
  print_test("Prueba heap encolar dato2", heap_encolar(heap, &dato2));
  print_test("Prueba heap la cantidad de datos es 1", heap_cantidad(heap) == 1);
  print_test("Prueba heap ver max es el dato2", heap_ver_max(heap) == &dato2);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap encolar dato3", heap_encolar(heap, &dato3));
  print_test("Prueba heap la cantidad de datos es 2", heap_cantidad(heap) == 2);
  print_test("Prueba heap ver max es el dato3", heap_ver_max(heap) == &dato3);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  heap_destruir(heap, NULL);
}

void prueba_heap_desencolar()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_int);
  print_test("Prueba heap desencolar", heap);

  int *dato1 = malloc(sizeof(int));
  int *dato2 = malloc(sizeof(int)); 
  int *dato3 = malloc(sizeof(int)); 
  *dato1 = 1;
  *dato2 = 2;
  *dato3 = 3;

  // Se encolan tres datos dinámicos y se los desencolan uno a uno
  print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));
  print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));
  print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));
  
  print_test("Prueba heap ver max es el dato3", heap_ver_max(heap) == dato3);
  print_test("Prueba heap desencolar, se obtiene el mayor, o sea dato3", heap_desencolar(heap) == dato3);
  print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap ver max es el dato2", heap_ver_max(heap) == dato2);
  print_test("Prueba heap desencolar, se obtiene el mayor, o sea dato1", heap_desencolar(heap) == dato2);
  print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap ver max es el dato1, el único", heap_ver_max(heap) == dato1);
  print_test("Prueba heap desencolar, se obtiene dato1", heap_desencolar(heap) == dato1);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap no está vacío", heap_esta_vacio(heap));

  free(dato1);
  free(dato2);
  free(dato3);
  heap_destruir(heap, NULL);
}

void prueba_destruir_heap_con_datos()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_str);
  print_test("Prueba heap destruir con datos dinámicos", heap);

  int *dato1 = malloc(sizeof(int));
  int *dato2 = malloc(sizeof(int)); 
  int *dato3 = malloc(sizeof(int)); 
  *dato1 = 1;
  *dato2 = 2;
  *dato3 = 3;

  // Se encolan los tres datos dinámicos nuevamente y no se los borra, esperando a que los libere heap_destruir
  print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));
  print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));
  print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));

  heap_destruir(heap, free);
}

void prueba_heap_otra_funcion()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_int_inversa);
  print_test("Prueba heap otra función", heap);

  int *dato1 = malloc(sizeof(int));
  int *dato2 = malloc(sizeof(int)); 
  int *dato3 = malloc(sizeof(int)); 
  int *dato4 = malloc(sizeof(int)); 
  *dato1 = 1;
  *dato2 = 2;
  *dato3 = 3;
  *dato4 = 4;

  // Se encolan cuatro datos dinámicos en distinto orden y se los borra uno a uno
  print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));
  print_test("Prueba heap encolar dato4", heap_encolar(heap, dato4));
  print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));
  print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));
  
  print_test("Prueba heap ver max es el dato1", heap_ver_max(heap) == dato1);
  print_test("Prueba heap desencolar, se obtiene el mayor, o sea dato1", heap_desencolar(heap) == dato1);
  print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap ver max es el dato2", heap_ver_max(heap) == dato2);
  print_test("Prueba heap desencolar, se obtiene el mayor, o sea dato2", heap_desencolar(heap) == dato2);
  print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap ver max es el dato3", heap_ver_max(heap) == dato3);
  print_test("Prueba heap desencolar, se obtiene dato3", heap_desencolar(heap) == dato3);
  print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("Prueba heap no está vacío", !heap_esta_vacio(heap));

  print_test("Prueba heap ver max es el dato4, el único", heap_ver_max(heap) == dato4);
  print_test("Prueba heap desencolar, se obtiene dato4", heap_desencolar(heap) == dato4);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap no está vacío", heap_esta_vacio(heap));

  // Se encolan los tres datos dinámicos nuevamente y no se los borra, esperando a que los libere heap_destruir
  print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));
  print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));
  print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));
  print_test("Prueba heap encolar dato4", heap_encolar(heap, dato4));

  heap_destruir(heap, free);
}

void prueba_heap_volumen(int largo){
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_int);
  print_test("Prueba heap volumen", heap);

  char* arreglo_bits = calloc(sizeof(char), largo); // Inicializamos el mapa de bits con 0

  size_t errores_encolar = 0; 
  int entero_random;
  for(size_t i = 0; i < largo; i++)
  {
    entero_random = rand() % largo; 

    if(! arreglo_bits[entero_random]) // Encolamos aquellos que no hayamos encolado (los ints en cuya pos haya 0)
    {
      int *entero_a_encolar = malloc(sizeof(int));
      *entero_a_encolar = entero_random;
      if(!heap_encolar(heap, entero_a_encolar)) errores_encolar++;
      arreglo_bits[entero_random] = 1; // Guardamos 1 avisando que ya lo encolamos en el heap
    } 
  }

  for(size_t j = 0; j < largo; j++){ // Metemos todos aquellos que no fueron agarrados por el random
    if(! arreglo_bits[j]){
      int *entero_a_encolar = malloc(sizeof(int));
      *entero_a_encolar = (int) j;
      if(!heap_encolar(heap, entero_a_encolar)) errores_encolar++;
      arreglo_bits[j] = 1;
    }
  }

  print_test("Se encolaron todos los elementos", !errores_encolar);

  size_t errores_desencolar = 0;
  for(size_t k = 1; k <= largo; k++)
  {   
    int *desencolado = heap_desencolar(heap);
    if(! desencolado) errores_desencolar++;

    if(! (*desencolado == largo - k)) errores_desencolar++;
    free(desencolado);
  }
  print_test("Se borraron todos los elementos", !errores_desencolar);
  print_test("Finalizó la prueba de volumen", !(errores_encolar + errores_desencolar));

  free(arreglo_bits);
  heap_destruir(heap, NULL);
}

void prueba_heap_encolar_null()
{
  printf("\n");
  heap_t* heap = heap_crear(funcion_cmp_str);

  print_test("Prueba heap encolar null", heap);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver_max es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));
  print_test("Prueba heap encolar null es false", !heap_encolar(heap, NULL));
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver_max es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
}

void prueba_heap_crear_arr()
{
  printf("\n");

  int *numeros[10];
  int num1 = 1;
  int num2 = 2;
  int num3 = 3;
  int num4 = 4;
  int num5 = 5;
  int num6 = 6;
  int num7 = 7;
  int num8 = 8;
  int num9 = 9;
  int num10 = 10;

  numeros[0] = &num4;
  numeros[1] = &num2;
  numeros[2] = &num7;
  numeros[3] = &num9;
  numeros[4] = &num1;
  numeros[5] = &num3;
  numeros[6] = &num8;
  numeros[7] = &num10;
  numeros[8] = &num5;
  numeros[9] = &num6;

  heap_t* heap = heap_crear_arr((void*)numeros, 10, funcion_cmp_int);
  print_test("Prueba heap crear arr", heap);

  print_test("Prueba heap la cantidad de elementos es 10", heap_cantidad(heap) == num10);
  print_test("Prueba heap ver_max es 10", 10 == *(int*)heap_ver_max(heap));
  
  int errores = 0;
  for(int i = 10; i > 0; i--){
    if(! (*(int*)heap_desencolar(heap) == i)) errores++;
  }

  print_test("Prueba heap se desencolaron los elementos", !errores);

  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver_max es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));
  print_test("Prueba heap encolar null es false", !heap_encolar(heap, NULL));

  heap_destruir(heap, NULL);
}

void prueba_heapsort(){
  printf("\n");

  int *numeros[10];
  int num1 = 1;
  int num2 = 2;
  int num3 = 3;
  int num4 = 4;
  int num5 = 5;
  int num6 = 6;
  int num7 = 7;
  int num8 = 8;
  int num9 = 9;
  int num10 = 10;

  numeros[0] = &num4;
  numeros[1] = &num2;
  numeros[2] = &num7;
  numeros[3] = &num9;
  numeros[4] = &num1;
  numeros[5] = &num3;
  numeros[6] = &num8;
  numeros[7] = &num10;
  numeros[8] = &num5;
  numeros[9] = &num6;

  heap_sort((void**)numeros, 10, funcion_cmp_int);
}

void pruebas_heap_alumno(void) 
{
  prueba_crear_heap_vacio();
  prueba_heap_encolar();
  prueba_heap_desencolar();
  prueba_destruir_heap_con_datos();
  prueba_heap_otra_funcion();
  prueba_heap_volumen(1000);
  prueba_heap_encolar_null();
  prueba_heap_crear_arr();
  prueba_heapsort();  
}