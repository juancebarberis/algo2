#include<stdio.h>

int _posicion_cero(int arreglo[], size_t inicio, size_t fin)
{   
    int medio = (inicio + fin) / 2;

    if(medio == 0)
    {   
        if(arreglo[inicio] == 0)
            return inicio;
        else if(arreglo[fin] == 0)
            return fin;
        else
            return -1;
    }

    int izq = _posicion_cero(arreglo, inicio, medio);
    int der = _posicion_cero(arreglo, medio + 1, fin);

    return izq >= der ? der : izq;
}

int posicion_cero(int arreglo[], size_t largo)
{
    return _posicion_cero(arreglo, 0, largo - 1);
}

int main()
{
    int arreglo1[] = {1, 1, 1, 0, 0}; 
    int arreglo2[] = {1, 0, 1, 1, 1, 0};    
    int arreglo3[] = {1, 1, 1};     
    size_t largo1 = 5;
    size_t largo2 = 6;
    size_t largo3 = 3;
    printf("Arreglo 1: %d.\n", posicion_cero(arreglo1, largo1));
    printf("Arreglo 2: %d.\n", posicion_cero(arreglo2, largo2));
    printf("Arreglo 3: %d.\n", posicion_cero(arreglo3, largo3));
    return 0;
}