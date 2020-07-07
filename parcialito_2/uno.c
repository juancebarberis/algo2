#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

bool _es_heap(int arr[], size_t n, size_t i)
{
  if(i >= n) return true;

  int actual = arr[i];
  int padre = i == 0 ? 0 : (i - 1) / 2;
  int izq = (i * 2) + 1; 
  int der = (i * 2) + 2;

  if(actual > arr[izq] || actual > arr[der] || actual < arr[padre])
    return false;
  else
    return _es_heap(arr, n, i + 1); 
}

bool es_heap(int arr[], size_t n)
{
  return _es_heap(arr, n, 0);
}

int main()
{
  int arr[] = {1, 7, 2, 8, 7, 6, 3, 3, 9, 10};
  printf("%d\n", es_heap(arr, 10));
  return 0;
}