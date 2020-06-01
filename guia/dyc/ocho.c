#include<stdio.h>

int _minimo(int arreglo[], size_t inicio, size_t fin)
{
    if(inicio == fin) 
        return arreglo[inicio];
    
    int medio = (inicio + fin) / 2;

    int izquiero = _minimo(arreglo, inicio, medio); 
    int derecho  = _minimo(arreglo, medio + 1, fin); 

    return izquiero < derecho ? izquiero : derecho;
}

int minimo(int arreglo[], size_t largo)
{
    return _minimo(arreglo, 0, largo - 1);
}

int main()
{
    int arreglo[] = {3, 5, -1, 0, 6, 8, -43, 6, 12, -6};
    size_t largo = 10;
    printf("%d\n", minimo(arreglo, largo));
    return 0;
}