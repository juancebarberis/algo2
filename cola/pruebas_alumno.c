#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Consiste en una prueba inicial muy sencilla.
 * Se realizan unas comprobaciones triviales.
 * Se encolan y desencolan 10 elementos de tipo int.
 * Se comprueba que los punteros (ptr) almacenados sean distintos entre si.
 * */
void prueba_generica()
{
    cola_t* cola_1 = cola_crear();
    int valores1[] = {2, 3, 6, 32, 76, 12, 11, 0, 3, 56};
    print_test("Cola inicializada", cola_1);
    print_test("Cola está vacía", cola_esta_vacia(cola_1));
    print_test("No es posible desencolar aún", cola_desencolar(cola_1) == NULL);
    print_test("No es posible ver el primero aún", cola_ver_primero(cola_1) == NULL);
    print_test("Es posible encolar el elemento NULL", cola_encolar(cola_1, NULL));
    print_test("Es posible desencolar el elemento NULL", cola_desencolar(cola_1) == NULL);
    print_test("Cola está vacía como al principio", cola_esta_vacia(cola_1));
    print_test("Encolar 10 elementos", true);
    for(int i = 0; i < 10; i++)
    {
        if(!cola_encolar(cola_1, &valores1[i]))
            print_test("Error al encolar", false);
    }
    print_test("Cola ya no está vacía", !cola_esta_vacia(cola_1));
    print_test("El primer elemento (ptr) es igual a valores[0]", cola_ver_primero(cola_1) == &valores1[0]);
    print_test("Ver nuevamente el primer elemento (ptr), sigue igual a valores[0]", cola_ver_primero(cola_1) == &valores1[0]);
    print_test("Desencolar y obtener el elemento (ptr) igual a valores[0]", cola_desencolar(cola_1) == &valores1[0]);
    print_test("El primer elemento (ptr) ahora es igual a valores[1]", cola_ver_primero(cola_1) == &valores1[1]);
    print_test("Desencolar todos los elementos restantes", true);
    while(!cola_esta_vacia(cola_1))
    {
        cola_desencolar(cola_1);
    }
    print_test("Todos los elementos fueron desencolados", cola_esta_vacia(cola_1));
    print_test("Destruir Cola", true); cola_destruir(cola_1, NULL);
}

/**
 * Se encolan y desencolan 10 elementos de tipo double.
 * Se comprueba que los valores (val) almacenados sean distintos entre si.
 * */
void prueba_valores()
{
    cola_t* cola_2 = cola_crear();
    double valores2[] = {3.14, 1.41, 2.71, 6.67, 7.29};
    print_test("Cola inicializada", cola_2);
    print_test("Encolar 10 elementos", true);
    for(int j = 0; j < 5; j++)
    {
        if(!cola_encolar(cola_2, &valores2[j]))
            print_test("Error al encolar", false);
    }
    print_test("Encolar finalizado", true);
    double* aux_valores_1 = cola_desencolar(cola_2);
    print_test("Desencolar el primer elemento (val) de la Cola == 3.14", *aux_valores_1 == 3.14);
    double* aux_valores_2 = cola_desencolar(cola_2);
    print_test("Desencolar el siguiente elemento (val) de la Cola == 1.41", *aux_valores_2 == 1.41);
    double* aux_valores_3 = cola_desencolar(cola_2);
    print_test("Desencolar el siguiente elemento (val) de la Cola == 2.71", *aux_valores_3 == 2.71);
    double* aux_valores_4 = cola_desencolar(cola_2);
    print_test("Desencolar el siguiente elemento (val) de la Cola == 6.67", *aux_valores_4 == 6.67);
    double* aux_valores_5 = cola_desencolar(cola_2);
    print_test("Desencolar el siguiente elemento (val) de la Cola == 7.29", *aux_valores_5 == 7.29);

    print_test("Cola ahora está vacía", cola_esta_vacia(cola_2));
    
    print_test("Cola destruir", true); cola_destruir(cola_2, NULL);
}

/**
 * Prueba con un arreglo alojado en memoria dinámica.
 * Se le pasa free() como referencia a cola_destruir para que también libere la memoria del arreglo
 * */
void prueba_arreglo_dinamico()
{
    cola_t* cola_3 = cola_crear();
    int* valores3 = malloc(100 * sizeof(int));
    if(valores3 == NULL) 
    {
        print_test("malloc()", false);
    }
    else
    {
        print_test("Encolar arreglo", cola_encolar(cola_3, valores3));
        print_test("Cola no está vacía", !cola_esta_vacia(cola_3));

        cola_destruir(cola_3, free);
        print_test("Cola destruir con free()", true);
    }
}

/**
 * Prueba de volumen. Se encolan 1000 elementos y luego de los desencolan dando
 * finalizada la prueba una vez que se destruye la cola estando vacía
 * */
void prueba_volumen()
{
    cola_t* cola_4 = cola_crear();
    print_test("Se encolan 1000 elementos", true);
    int* valores4 = malloc(1000 * sizeof(int)); 
    for(int i = 0; i < 1000; i++) 
    {        
        if(!cola_encolar(cola_4, &valores4[i])) 
            print_test("Error al intentar encolar", false);
    }
    print_test("1000 elementos encolados", true);
    print_test("Cola no está vacía", !cola_esta_vacia(cola_4));
    print_test("Desencolar todos los elementos comparandolos con el puntero correspondiente", true);
    int j = 0;
    while(!cola_esta_vacia(cola_4))
    {
        if(cola_desencolar(cola_4) != &valores4[j]){
            print_test("Error al comparar punteros", false);
            break;
        }
        j++;
    }
    print_test("La cola está vacía y es destruida", cola_esta_vacia(cola_4));
    cola_destruir(cola_4, NULL);
    free(valores4);
}

/**
 * En esta prueba se intenta encolar colas, para luego ser destruidas mediante el puntero a función de cola_destruir
 * */
void cola_secundaria_destruir(void* cola_secundaria)
{
    cola_destruir(cola_secundaria, NULL);
}
void prueba_coca_cola()
{
    cola_t* cola_principal = cola_crear();
    print_test("Cola principal inicializada", true);
    for(int i = 0; i < 5; i++)
    {
        if(!cola_encolar(cola_principal, cola_crear()))
            print_test("Error al encolar cola secundaria", false);
    }
    print_test("5 Colas encoladas en cola principal", true);
    print_test("Cola principal no está vacía", !cola_esta_vacia(cola_principal));
    print_test("Destruimos la cola_principal, también destruyendo cada cola_secundaria encolada", true);
    cola_destruir(cola_principal, cola_secundaria_destruir);
}


void pruebas_cola_alumno()
{
    printf("\nPRUEBAS GENÉRICAS...\n");
    prueba_generica();
    
    printf("\nPRUEBAS DE VALORES...\n");
    prueba_valores();
    
    printf("\nPRUEBAS DE ARREGLO EN MEMORIA DINÁMICA...\n");
    prueba_arreglo_dinamico();

    printf("\nPRUEBAS DE VOLUMEN...\n");
    prueba_volumen();

    printf("\nPRUEBAS ENCOLANDO COLAS...\n");
    prueba_coca_cola();
}