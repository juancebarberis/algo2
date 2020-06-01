#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Función visitar para ejercicio 14
 * */
bool sumar_pares(void* _dato, void* _acumulado)
{
    int* dato = _dato;
    int* acumulado = _acumulado; 
    if(*dato % 2 == 0)
        *acumulado += *dato;
    return true;
}

void ejercicio_seis()
{
    lista_t* lista = lista_crear();
    int valores[] = {1, 54, 65, 32, 21, 11};
    lista_insertar_ultimo(lista, &valores[0]);
    lista_insertar_ultimo(lista, &valores[1]);
    lista_insertar_ultimo(lista, &valores[2]);
    lista_insertar_ultimo(lista, &valores[3]);
    lista_insertar_ultimo(lista, &valores[4]);
    lista_insertar_ultimo(lista, &valores[5]);
    //print_test("Valor es", &valores[2] ==  devolver_a_k_posiciones(lista, 3));
    int suma_acumulada = 0;
    lista_iterar(lista, sumar_pares, &suma_acumulada);
    printf("Suma acumulada %d\n", suma_acumulada);
    lista_destruir(lista, NULL);
}


/**
 * PRUEBAS
 * */

void pruebas_lista_alumno(void)
{
    ejercicio_seis();
}