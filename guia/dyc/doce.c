/*
 Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada de un número nn, en tiempo O(logn). Por ejemplo, para n=10 debe devolver 3, y para n=25 debe devolver 5.
*/
#include<stdio.h>

int raiz_cuadrada(int n, int inicio, int fin)
{
  int medio = (inicio + fin) / 2;
  
  if(medio * medio == n || medio * medio == n - 1 || inicio == fin) 
    return medio;

  if(medio*medio < n)
    return raiz_cuadrada(n, medio + 1, fin);
  
  return raiz_cuadrada(n, inicio, medio);
}

int raiz(int n)
{
  return raiz_cuadrada(n, 0, n);
}

int main()
{
  printf("%d\n", raiz(10));
  printf("%d\n", raiz(25));
  printf("%d\n", raiz(64));
  printf("%d\n", raiz(61));
  return 0;
}
