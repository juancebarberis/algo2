/*
Implementar una función (que utilice división y conquista) de orden O(nlogn) que dado un arreglo de nn números enteros devuelva true o false según si existe algún elemento que aparezca más de la mitad de las veces. Justificar el orden de la solución. Ejemplos:
[1, 2, 1, 2, 3] -> false
[1, 1, 2, 3] -> false
[1, 2, 3, 1, 1, 1] -> true
[1] -> true
*/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

int max(int arreglo[], int n)
{
  int max = arreglo[0];
  for(int i = 1; i < n; i++)
  {
    if(arreglo[i] > max)
      max = arreglo[i];
  }
  return max;
}

void _se_repite(int* arreglo, int inicio, int fin)
{
  if(inicio == fin) {
    arreglo[inicio]++;
    return;
  }
  int medio = (inicio + fin) / 2;
  _se_repite(arreglo, inicio, medio - 1);
  _se_repite(arreglo, medio, fin);
}

bool se_repite(int arreglo[], int n)
{
  if(n == 1) return true;

  int max_arreglo = max(arreglo, n);
  int* arreglo_contador = malloc(sizeof(int) * max_arreglo);
  for(int i = 0; i < max_arreglo; i++)
  {
    arreglo_contador[i] = 0;
  }
  _se_repite(arreglo_contador, 0, n);
  int max_contador = max(arreglo_contador, max_arreglo);
  return max_contador > n / 2 ? true : false;
}

int main()
{
  int arreglo[] = {1, 2, 1, 2, 3};
  printf("[1, 2, 1, 2, 3] -> %d\n", se_repite(arreglo, 5));
  //printf("MAX[1, 2, 1, 2, 3] -> %d\n", max(arreglo, 5));
  //int arreglo2[] = {1, 1, 2, 3};
  //printf("[1, 1, 2, 3] -> %d\n", se_repite(arreglo2, 4));
  //int arreglo3[] = {1, 2, 3, 1, 1, 1};
  //printf("[1, 2, 3, 1, 1, 1] -> %d\n", se_repite(arreglo3, 6));
  //int arreglo4[] = {1};
  //printf("[1] -> %d\n", se_repite(arreglo4, 1));
  return 0;
}