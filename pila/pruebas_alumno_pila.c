#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    /**
     * Pila 1
     */
    pila_t* pila_1 = pila_crear();
    print_test("Pila 1 inicializada", pila_1);
    print_test("Pila 1 está vacía", pila_esta_vacia(pila_1));
    print_test("Pila 1 ver el tope (no tiene nada apilado aún)", pila_ver_tope(pila_1) == NULL);
    print_test("Pila 1 desapilar (no tiene nada apilado aún)", pila_desapilar(pila_1) == NULL);
    print_test("Pila 1 apilar elemento NULL es válido", pila_apilar(pila_1, NULL));
    print_test("Pila 1 ya no está vacía", !pila_esta_vacia(pila_1));
    
    print_test("Prueba de apilar un set de 10 elementos.", true);
    int valores1[] = {5, 64, 2, 1, 9, 0, 1, 223, 54, 69};
    for(int i = 0; i < 10; i++)
    {
        print_test("Pila 1 apilar set 1 de valores", pila_apilar(pila_1, &valores1[i]));
        print_test("Lo apilado ahora es tope", pila_ver_tope(pila_1) == &valores1[i]);
        print_test("Y es posible desapilarlo", pila_desapilar(pila_1) == &valores1[i]);
    }
    print_test("Pila 1 aún no está vacía, el elemento NULL del principio sigue ahí", !pila_esta_vacia(pila_1));
    print_test("Pila 1 lo desapilamos", pila_desapilar(pila_1) == NULL);
    print_test("Pila 1 está vacía", pila_esta_vacia(pila_1));
    pila_destruir(pila_1);
    print_test("Pila 1 Destruir", true);

    /**
     * Pila 2
     */ 
    pila_t* pila_2 = pila_crear();
    print_test("Pila 2 inicializada", pila_2);
    print_test("Pila 2 está vacía", pila_esta_vacia(pila_2));
    double valores2[] = {1.5, 6.7, 0.0, 1.2, 6.0};
    for(int i = 0; i < 5; i++)
    {
        print_test("Pila 2 apilar set 2 de valores", pila_apilar(pila_2, &valores2[i]));
        print_test("Lo apilado ahora es tope", pila_ver_tope(pila_2) == &valores2[i]);
    }
    print_test("Pila 2 no está vacía", !pila_esta_vacia(pila_2));
    double* aux = pila_desapilar(pila_2);
    print_test("Pila 2 valor desapilado que era tope == 6.0", *aux == 6.0);
    double* aux2 = pila_ver_tope(pila_2);
    print_test("Pila 2 valor del tope == 1.2", *aux2 == 1.2);
    print_test("Pila 2 desapilar todos los elementos restantes", true);
    for(int i = 3; i >= 0; i--)
    {
        print_test("Pila 2 desapilar set 2 de valores", pila_desapilar(pila_2) == &valores2[i]);
    }
    print_test("Pila 2 está vacía", pila_esta_vacia(pila_2));
    print_test("Pila 2 destruir", true);
    pila_destruir(pila_2);
    /**
     * Pila 3
     */ 
    pila_t* pila_3 = pila_crear();
    print_test("Pila 3 inicializada", pila_3);
    print_test("Pila 3 está vacía", pila_esta_vacia(pila_3));
    print_test("Prueba de volumen: apilar 1.000 datos", true);
    int* valores3 = malloc(1000 * sizeof(int)); 
    for(int i = 0; i < 1000; i++) 
    {        
        if(!pila_apilar(pila_3, &valores3[i]) || pila_ver_tope(pila_3) != &valores3[i]) 
            print_test("Problema intentando apilar", false);
    }
    print_test("Pila no está vacía", !pila_esta_vacia(pila_3));
    print_test("1.000 elementos apilados correctamente.", true);
    print_test("Prueba de volumen: desapilar 1.000 datos", true);
    int j = 999;
    while(!pila_esta_vacia(pila_3))
    {
        void* aux = pila_desapilar(pila_3);

        if(aux != &valores3[j])
            print_test("Error al desapilar", false);
        j--;
    }
    print_test("1.000 elementos desapilados correctamente.", true);
    print_test("Pila 3 ahora está vacía", pila_esta_vacia(pila_3));
    pila_destruir(pila_3);
    free(valores3);
    print_test("Pila 3 Destruir", true);
}
