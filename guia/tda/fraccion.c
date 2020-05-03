#include<stdio.h>
#include<stdlib.h>
#include "fraccion.h"

typedef struct fraccion {
    int numerador;
    int denominador;
} fraccion_t;

fraccion_t* fraccion_crear(int numerador, int denominador)
{
    if(denominador == 0) return NULL;
    
    fraccion_t* fraccion = malloc(sizeof(fraccion_t)); 

    if(!fraccion) {
        return NULL;
    }
    else {
        int max_cd = mcd(numerador, denominador);
        if(numerador == 0) max_cd = 1;

        fraccion->numerador = numerador / max_cd;
        fraccion->denominador = denominador / max_cd;
    }
    return fraccion;
}

void fraccion_destruir(fraccion_t* fraccion)
{
    free(fraccion);
}

int fraccion_parte_entera(fraccion_t* fraccion)
{
    return fraccion->numerador / fraccion->denominador;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2)
{
    int numerador = f1->numerador * f2->numerador;
    int denominador = f1->denominador * f2->denominador;
    fraccion_t* resultado = fraccion_crear(numerador, denominador);
    
    if(resultado != NULL) {
        fraccion_destruir(f1);
        fraccion_destruir(f2);
        return resultado;
    }
    else {
        return NULL;
    }
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2)
{
    int numerador = (f1->denominador * f2->numerador) + (f1->numerador * f2->denominador);
    int denominador = f1->denominador * f2->denominador;
    fraccion_t* resultado = fraccion_crear(numerador, denominador);
    
    if(resultado != NULL) {
        fraccion_destruir(f1);
        fraccion_destruir(f2);
        return resultado;
    }
    else {
        return NULL;
    }
}

char* fraccion_representacion(fraccion_t* fraccion)
{
    size_t num_largo = calcular_largo(fraccion->numerador);
    size_t den_largo = calcular_largo(fraccion->denominador);
    int multiplicity = 0;
    int es_negativo = 0;
    if(fraccion->numerador < 0 || fraccion->denominador < 0) {
        es_negativo++;
    }
    multiplicity += num_largo + den_largo + es_negativo + 2;
    char* resultado = malloc(multiplicity * sizeof(char*));

    if(!resultado) {
        return NULL;
    }
    sprintf(resultado, "%d/%d", fraccion->numerador, fraccion->denominador);
    return resultado;
}

// Función auxiliar para hallar el máximo común divisor de una fracción
// a -> numerador, b-> denominador.
// Más info en: https://en.wikipedia.org/wiki/Euclidean_algorithm
int mcd(int a, int b)
{
    if(b == 0) 
        return a;
    else 
        return mcd(b, a % b);
}

// Función auxiliar para contar el largo de un número
size_t calcular_largo(int numero)
{
    if(numero == 0) return 1;

    size_t largo = 0;
    while(numero > 0) {
        largo++;
        numero /= 10;
    }
    return largo;
}

//Ejecución
int main()
{
    pruebas();
    return 0;
}

void pruebas()
{
    printf("Iniciando pruebas...\n");
    printf("Crear fracciones\n");
    fraccion_t* f1 = fraccion_crear(1, 2); 
    fraccion_t* f2 = fraccion_crear(1, 76); 
    fraccion_t* f3 = fraccion_crear(-4, 8); 
    fraccion_t* f4 = fraccion_crear(0, -5); 
    fraccion_t* f5 = fraccion_crear(9, -2); 
    fraccion_t* f6 = fraccion_crear(10, 100); 
    fraccion_t* f7 = fraccion_crear(140, 45); 
    fraccion_t* f8 = fraccion_crear(67, 9); 
    
    printf("Fracciones creadas. Ahora vamos a obtener la parte entera de cada una: \n");
        printf("Fraccion 1: %d\n", fraccion_parte_entera(f1));
        printf("Fraccion 2: %d\n", fraccion_parte_entera(f2));
        printf("Fraccion 3: %d\n", fraccion_parte_entera(f3));
        printf("Fraccion 4: %d\n", fraccion_parte_entera(f4));
        printf("Fraccion 5: %d\n", fraccion_parte_entera(f5));
        printf("Fraccion 6: %d\n", fraccion_parte_entera(f6));
        printf("Fraccion 7: %d\n", fraccion_parte_entera(f7));
        printf("Fraccion 8: %d\n", fraccion_parte_entera(f8));
    
    printf("\n Bien, ahora, vamos a ver una representación simplificada: \n");
        char* repr = fraccion_representacion(f1);
        printf("Fracción repr 1 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f2);
        printf("Fracción repr 2 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f3);
        printf("Fracción repr 3 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f4);
        printf("Fracción repr 4 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f5);
        printf("Fracción repr 5 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f6);
        printf("Fracción repr 6 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f7);
        printf("Fracción repr 7 -> %s\n",repr);
        free(repr);
        repr = fraccion_representacion(f8);
        printf("Fracción repr 8 -> %s\n",repr);
        free(repr);

    printf("Bien. Nada de lo que hicimos alteró las structuras. Ahora vamos a:\n");
        printf("Multiplicar la fraccion 1 y 2:"); 
            fraccion_t* res_mul_1 = fraccion_mul(f1, f2);
            repr = fraccion_representacion(res_mul_1);
            printf("Resultado de mul 1 y 2 -> %s\n",repr);
            free(repr);
        printf("Multiplicar la fraccion 3 y 4 -> "); 
            fraccion_t* res_mul_2 = fraccion_mul(f3, f4);
            repr = fraccion_representacion(res_mul_2);
            printf("Resultado de mul 3 y 4 -> %s\n",repr);
            free(repr);
        printf("Sumar la fraccion 5 y 6:"); 
            fraccion_t* res_sum_1 = fraccion_sumar(f5, f6);
            repr = fraccion_representacion(res_sum_1);
            printf("Resultado de sum 5 y 6 -> %s\n",repr);
            free(repr);
        printf("Sumar la fraccion :"); 
            fraccion_t* res_sum_2 = fraccion_sumar(f7, f8);
            repr = fraccion_representacion(res_sum_2);
            printf("Resultado de sum 7 y 8 -> %s\n",repr);
            free(repr);

    printf("Destruir fracciones\n");
        fraccion_destruir(res_mul_1);
        fraccion_destruir(res_mul_2);
        fraccion_destruir(res_sum_1);
        fraccion_destruir(res_sum_2);
    //printf("Iniciando pruebas\n");

}