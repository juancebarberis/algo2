#define _POSIX_C_SOURCE 200809L
#define CANTIDAD_INICIAL 100
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "strutil.h"
#include "cola.h"
#include<math.h>

bool es_numerico(char* cadena)
{
  return atoi(cadena) ? true : false;
}

int calcular(char* linea)
{
  char** strv = split(linea, ' ');

  if(!strv) return 1;

  cola_t* numeros = cola_crear();
  cola_t* operadores = cola_crear();
  size_t _numeros = 0;
  size_t _operadores = 0;

  for(int i = 0; strv[i]; i++)
  {
    if(es_numerico(strv[i])) {
      if(!cola_encolar(numeros, &strv[i])) return -1;
      _numeros++;
    }
    else {
      if(!cola_encolar(operadores, &strv[i])) return -1;
      _operadores++;
    }
  }

  if(_numeros == _operadores)

  free_strv(strv);
  return 0;
}


int main(int argc, char* argv[])
{
  char* buffer = malloc(sizeof(char) * 100);

  if(!buffer) {
    fprintf(stderr, "No es posible alojar memoria inicial...\n");
    return -1;
  }

  int error_count = 0;
  
  while(fgets(buffer, 100, stdin))
  {
    error_count += calcular(buffer);
  }
  if(error_count > 0)
    fprintf(stderr, "Errores durante la ejecución -> %d\n", error_count);

  free(buffer);
  return error_count;
}
