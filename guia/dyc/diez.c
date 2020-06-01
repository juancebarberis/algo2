#include<stdio.h>

int _oveja_negra(int arreglo[], size_t inicio, size_t fin)
{
    int medio = (inicio + fin) / 2;

    if(inicio == fin - 1)
        return arreglo[inicio] > arreglo[fin] ? arreglo[fin] : 0;

    if(inicio == fin)
        return 0;

    if(arreglo[medio] > arreglo[medio + 1])
        return arreglo[medio + 1];


    int izq = _oveja_negra(arreglo, inicio, medio);
    int der = _oveja_negra(arreglo, medio + 1, fin);

    return izq + der;
}

int oveja_negra(int arreglo[], size_t largo)
{
    return _oveja_negra(arreglo, 0, largo - 1);
}

int main()
{
    int arreglo1[] = {3, 5, 6, 8, -43, 9, 10}; 
    int arreglo2[] = {1, 2, 3, 4, 5, 6, 7, 5, 8, 10};    
    int arreglo3[] = {3, 6, 9, 12, 15, 8, 21, 24, 27, 30};     
    size_t largo1 = 7;
    size_t largo2 = 10;
    size_t largo3 = 10;
    printf("Oveja negra del arreglo. \n");
    printf("Arreglo 1: %d.\n", oveja_negra(arreglo1, largo1));
    printf("Arreglo 2: %d.\n", oveja_negra(arreglo2, largo2));
    printf("Arreglo 3: %d.\n", oveja_negra(arreglo3, largo3));
    return 0;
}