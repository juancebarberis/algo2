#include "tp0.h"

void swap (int *x, int *y) 
{
    int aux_x = *x, aux_y = *y;
    
    *x = aux_y;
    *y = aux_x;
}


int maximo(int vector[], int n) 
{
    if(n == 0) return -1;

    int resultado = 0;
    
    for (int i = 0; i < n; i++) 
    {
        if(vector[i] > vector[resultado])
            resultado = i;
    }

    return resultado;
}


int comparar(int vector1[], int n1, int vector2[], int n2) 
{
    if(n1 == 0 && n2 > 0) return -1;
    if(n2 == 0 && n1 > 0) return 1;

    int i = 0;
    while(i < n1 || i < n2) 
    {
        if(vector1[i] > vector2[i]) return 1;
        if(vector1[i] < vector2[i]) return -1;
        
        i++; 
        //Si alguno de los vectores llegó a su fin, sin elementos distintos, es necesario concluir que el otro es mayor.
        if(i == n1 && i != n2) return -1;
        if(i == n2 && i != n1) return 1;
    }   
    return 0;
}

void seleccion(int vector[], int n) 
{
    for(int i = 0; i < n; i++)
    {
        int i_max = maximo(vector, n - i);
        swap(&vector[i_max], &vector[n - 1 - i]);
    }
}
