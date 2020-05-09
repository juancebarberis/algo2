#include "pila.h"
#include "testing.h"
#include <stddef.h>

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
        int valor = valores1[i];
        print_test("Pila 1 apilar set 1 de valores", pila_apilar(pila_1, &valor));
        print_test("Lo apilado ahora es tope", pila_ver_tope(pila_1) == &valor);
        print_test("Y es posible desapilarlo", pila_desapilar(pila_1) == &valor);
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
        double valor = valores2[i];
        print_test("Pila 2 apilar set 2 de valores", pila_apilar(pila_2, &valor));
        print_test("Lo apilado ahora es tope", pila_ver_tope(pila_2) == &valor);
        print_test("Y es posible desapilarlo", pila_desapilar(pila_2) == &valor);
    }
    print_test("Pila 2 está vacía", pila_esta_vacia(pila_2));
    print_test("Prueba de volumen: 1.0000 datos", true);
    for(int i=0;i<10000;i++) 
    {
        int valor = i;
        bool result = pila_apilar(pila_2, &valor);
        if(!result || pila_ver_tope(pila_2) != &valor || pila_desapilar(pila_2) != &valor)
            print_test("Problema intentando apilar", false);
    }
    print_test("1.0000 elementos apilados correctamente.", true);
    pila_destruir(pila_2);
    print_test("Pila 2 Destruir", true);
}
