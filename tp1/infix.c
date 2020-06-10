#define CANTIDAD_INICIAL 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strutil.h"
#include "calcutil.h"
#include "pila.h"
/*
int main()
{
  char* buffer = malloc(sizeof(char) * CANTIDAD_INICIAL);

  if(!buffer) {
    fprintf(stderr, "No es posible alojar memoria inicial...\n");
    return -1;
  }

  char* linea;
  size_t linea_len;
  
  while(fgets(buffer, CANTIDAD_INICIAL, stdin))
  {
    linea_len = strlen(buffer);

    if(strcmp(buffer + linea_len - 1, "\n") == 0) {
      linea = substr(buffer, linea_len - 1);
      convertir(linea);
      free(linea);
    }
    else
      convertir(buffer);
  }
  free(buffer);
  return 0;
}
*/