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
    print_test("Y es posible desencolar el elemento NULL", cola_desencolar(cola_1) == NULL);
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
 * Se encolan y desencolan 10 elementos de tipo double.
 * Se comprueba que los valores (val) almacenados sean distintos entre si.
 * */

//Función auxiliar para pasar a cola_destruir
void destruir_dato_de_prueba(void* dato)
{
    free(dato);
}

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
        //for(int k = 0; k < 100; k++)
        //{
        //    if(!cola_encolar(cola_3, &valores3[k]))
        //        print_test("Error al encolar", false);
        //}
        print_test("Encolar arreglo", cola_encolar(cola_3, valores3));
        print_test("Cola no está vacía", !cola_esta_vacia(cola_3));
        //print_test("Primer elemento (ptr) es igual a valores[0]", cola_ver_primero(cola_3) == &valores3[0]);
        //print_test("Primer elemento (ptr) no se repite por lo que es != valores[1]", cola_ver_primero(cola_3) != &valores3[1]);

        cola_destruir(cola_3, destruir_dato_de_prueba);
        print_test("Cola destruir", true);
    }
}


void pruebas_cola_alumno()
{
    printf("\nPRUEBAS GENÉRICAS...\n");
    prueba_generica();
    
    printf("\nPRUEBAS DE VALORES...\n");
    prueba_valores();
    
    printf("\nPRUEBAS DE ARREGLO EN MEMORIA DINÁMICA...\n");
    prueba_arreglo_dinamico();
}