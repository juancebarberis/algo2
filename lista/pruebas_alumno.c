#include "lista.h"
#include "testing.h"
#include <stdio.h>

void prueba_generica_null()
{
    lista_t* lista = lista_crear();
    print_test("Lista inicializada", true);
    print_test("Lista está vacía", lista_esta_vacia(lista));
    print_test("Lista no es posible borrar primero", !lista_borrar_primero(lista));
    print_test("Lista no es posible ver primero", !lista_ver_primero(lista));
    print_test("Lista no es posible ver último", !lista_ver_ultimo(lista));
    print_test("Lista largo = 0", lista_largo(lista) == 0);
    print_test("Es posible insertar el elemento NULL", lista_insertar_primero(lista, NULL));
    print_test("Lista largo = 1", lista_largo(lista) == 1);
    print_test("El último elemento es igual al primero", lista_ver_primero(lista) == lista_ver_ultimo(lista));
    print_test("Es posible remover el elemento NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista puede ser destruida", true);
    lista_destruir(lista, NULL);
}

void prueba_generica_valores()
{
    lista_t* lista = lista_crear();
    print_test("Lista inicializada", true);
    int valores[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_test("Agregar cinco elementos al principio", true);
    for(int i = 0; i < 5; i++)
    {
        if(!lista_insertar_primero(lista, &valores[4 - i]))
            print_test("Error al insertar al principio de la lista", false);
    }
    print_test("Lista no está vacía", !lista_esta_vacia(lista));
    print_test("Lista largo = 5", lista_largo(lista) == 5);
    print_test("El primer elemento (ptr) de la lista == valores[0]", lista_ver_primero(lista) == &valores[0]);
    print_test("El último elemento (ptr) de la lista == valores[4]", lista_ver_ultimo(lista) == &valores[4]);
    int* primero_aux = lista_ver_primero(lista);
    int* ultimo_aux = lista_ver_ultimo(lista);
    print_test("El primer elemento (valor) de la lista == valores[0] (0)", *primero_aux == valores[0]);
    print_test("El último elemento (valor) de la lista == valores[4] (4)", *ultimo_aux == valores[4]);
    print_test("Agregar cinco elementos al final", true);
    for(int j = 5; j < 10; j++)
    {
        if(!lista_insertar_ultimo(lista, &valores[j]))
            print_test("Error al insertar al final de la lista", false);
    }
    print_test("Lista largo = 10", lista_largo(lista) == 10);
    print_test("El último elemento (ptr) de la lista es ahora == valores[9]", lista_ver_ultimo(lista) == &valores[9]);
    print_test("Borrar el primer elemento (ptr) de la lista == valores[0]", lista_borrar_primero(lista) == &valores[0]);
    print_test("Ahora el primer elemento (ptr) es == valores[1]", lista_ver_primero(lista) == &valores[1]);
    print_test("Borrar el primer elemento (ptr) de la lista == valores[1]", lista_borrar_primero(lista) == &valores[1]);
    print_test("Ahora el primer elemento (ptr) es == valores[2]", lista_ver_primero(lista) == &valores[2]);
    print_test("Lista largo = 8", lista_largo(lista) == 8);
    print_test("Agregar el elemento valores[0] al principio", lista_insertar_primero(lista, &valores[0]));
    print_test("Lista largo = 9", lista_largo(lista) == 9);
    print_test("Borrar el primer elemento (ptr) de la lista == valores[0]", lista_borrar_primero(lista) == &valores[0]);
    lista_destruir(lista, NULL);
    print_test("Lista destruida", true);
}

void prueba_volumen()
{
    lista_t* lista = lista_crear();
    print_test("Lista inicializada", true);
    print_test("Insertar 1000 elementos", true);
    int* valores = malloc(1000 * sizeof(int)); 
    for(int i = 0; i < 1000; i++) 
    {        
        if(!lista_insertar_ultimo(lista, &valores[i])) 
            print_test("Error al intentar insertar en la lista", false);
    }
    print_test("1000 elementos insertados en la lista", true);
    print_test("Lista no está vacía", !lista_esta_vacia(lista));
    print_test("Borrar todos los elementos comparandolos con el puntero correspondiente", true);
    int j = 0;
    while(!lista_esta_vacia(lista))
    {
        if(lista_borrar_primero(lista) != &valores[j]){
            print_test("Error al comparar punteros", false);
            break;
        }
        j++;
    }
    print_test("La lista está vacía y es destruida", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    free(valores);
}

//Función exclusiva para uso en prueba_destruir_dato()
void lista_destruir_prueba(void* lista)
{
    lista_destruir(lista, NULL);
}

void prueba_destruir_dato()
{
    lista_t* lista = lista_crear();
    print_test("Lista inicializada", true);
    print_test("Se insertan tres listas dentro de la lista", true);
    print_test("Lista 1 insertada", lista_insertar_primero(lista, lista_crear()));
    print_test("Lista 2 insertada", lista_insertar_ultimo(lista, lista_crear()));
    print_test("Lista 3 insertada", lista_insertar_primero(lista, lista_crear()));
    print_test("Lista no está vacía", !lista_esta_vacia(lista));
    print_test("Destruir lista principal, y las sublistas contenidas en ella", true);
    lista_destruir(lista, lista_destruir_prueba);
}

//Función exclusiva de prueba_iterador_interno()
bool visitar(void* dato, void* contador)
{
    int* dato_int = dato;
    int* contador_int = contador;
    if(*dato_int == 100) 
    {
        printf("¡En la posición: valores[%d], ", *contador_int);
        print_test("elemento encontrado!", true);
        return false;
    }
    else 
    {
        print_test("Elemento aún no coincide", dato_int != 0);
        (*contador_int)++;
        return true;
    }
}

void prueba_iterador_interno()
{
    lista_t* lista = lista_crear();
    print_test("Lista inicializada", true);
    print_test("Llenar la lista con elementos para comenzar a iterar", true);
    int valores[] = {1, 6, 8, 23, 77, 43, 89, 100, 0, 45};
    int contador = 0;
    for(int i = 0; i < 10; i++)
    {
        if(!lista_insertar_ultimo(lista, &valores[i]))
            print_test("Error al insertar valores", false);
    }
    print_test("Arreglo {1, 6, 8, 23, 77, 43, 89, 100, 0, 45} cargado en la lista", true);
    print_test("Iterar hasta encontrar el valor == 0", true);
    lista_iterar(lista, visitar, &contador);
    print_test("Destruir lista", true);
    lista_destruir(lista, NULL);
}

/**
 * PRUEBAS
 * */

void pruebas_lista_alumno(void)
{
    printf("\nPRUEBAS GENÉRICAS CON LISTA VACÍA Y VALOR NULL\n");
    prueba_generica_null();
    
    printf("\nPRUEBAS DE LA LISTA CON VALORES\n");
    prueba_generica_valores();

    printf("\nPRUEBAS DE VOLUMEN\n");
    prueba_volumen();

    printf("\nPRUEBAS DE DESTRUIR DATO (PUNTERO A FUNCION)\n");
    prueba_destruir_dato();

    printf("\nPRUEBAS DE ITERADOR INTERNO\n");
    prueba_iterador_interno();
    
    /*
    printf("\nEJEMPLO ITERADOR EXTERNO");
    ejemplo_iteradores();
    */
}