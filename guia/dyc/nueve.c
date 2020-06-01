#include<stdio.h>

int _esta_ordenado(int arreglo[], size_t inicio, size_t fin)
{
    int medio = (inicio + fin) / 2;

    if(inicio == fin) 
        return 1;
    else if(inicio == fin - 1 && arreglo[inicio] > arreglo[inicio + 1])
        return 0;

    int izq = _esta_ordenado(arreglo, inicio, medio);
    int der = _esta_ordenado(arreglo, medio + 1, fin);

    return izq == 1 && der == 1 ? 1 : 0;
}

int esta_ordenado(int arreglo[], size_t largo)
{
    return _esta_ordenado(arreglo, 0, largo - 1);
}

int main()
{
    int arreglo1[] = {3, 5, -1, 0, 6, 8, -43, 6, 12, -6}; // No ordenado
    int arreglo2[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};    // No ordenado
    int arreglo3[] = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30}; //Ordenado
    size_t largo1 = 10;
    size_t largo2 = 11;
    size_t largo3 = 10;
    printf("0 = no ordenado, 1 = ordenado \n");
    printf("Arreglo 1: %d.\n", esta_ordenado(arreglo1, largo1));
    printf("Arreglo 2: %d.\n", esta_ordenado(arreglo2, largo2));
    printf("Arreglo 3: %d.\n", esta_ordenado(arreglo3, largo3));
    return 0;
}