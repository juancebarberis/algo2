#define _POSIX_C_SOURCE 200809L
#define CAPACIDAD_INICIAL 64
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char *substr(const char *str, size_t n)
{
  size_t len = strlen(str);

  char* resultado = malloc((len + 1) * sizeof(char));
  
  if(len == 0) 
    resultado[0] = str[0];

  if(!resultado) return NULL;

  if(n > len) n = len;

  for(int i = 0; i < n; i++)
  {
    resultado[i] = str[i];
  }
  resultado[n] = '\0';

  return resultado;
}

char **split(const char *str, char sep)
{
  size_t len = strlen(str);
  char** resultado = malloc( sizeof(char*) * (len + 2) );

  if(!resultado) return NULL;

  char* vacio = "";
  
  int k = 0; // Indice del resultado
  int pos_separador = 0; // Indice del separador

  for(int i = 0; i < len + 1; i++)
  {
    //printf("%d actual -> %c (%d) \n", i, str[i], pos_separador);

    if(len == 0) {
      resultado[k] = strdup(vacio);
      k++;
      break;
    }

    if(str[i] == sep)
    {
      if(len == 1) {
        resultado[k] = strdup(vacio);
        resultado[k + 1] = strdup(vacio);
        k += 2;
        break;
      }

      if(i == 0) {  // Si el separador está al principio o al final
        resultado[k] = strdup(vacio);
        pos_separador++;
        k++;
        continue;
      }

      if(i == len - 1) {  // Está al final
        pos_separador++;
      }
      
      if(pos_separador != 0 && str[pos_separador] == sep)
        pos_separador++;
      
      resultado[k] = substr(str + pos_separador, i - pos_separador);
      pos_separador = i;
      k++;

      if(str[i + 1] == sep) {
        resultado[k] = strdup(vacio);
        pos_separador++;
        k++;
        i++;
      }

    }
    else if(str[i] == '\0') {
      if(pos_separador != 0 && str[pos_separador] == sep)
        pos_separador++; 
      resultado[k] = substr(str + pos_separador, i - pos_separador);
      k++;
    }
  }
  resultado[k] = NULL;  

  return resultado;
}


char *join(char **strv, char sep)
{

  char* resultado = calloc(CAPACIDAD_INICIAL, sizeof(char));
  char* final_actual;

  if(!strv) return resultado;
  
  if(!resultado) return NULL;

  char* separador = malloc(sizeof(char) * 2);
  separador[0] = sep;
  separador[1] = '\0';

  size_t len = 0;
  size_t capacidad = CAPACIDAD_INICIAL;
  
  for(int i = 0; strv[i]; i++)
  {
    len += strlen(strv[i]);

    if(len == 0 && strv[i+1])  {
      final_actual = stpcpy(i == 0 ? resultado : final_actual, separador);
      continue;
    }

    if(len >= capacidad - 1) {
      char* resultado = realloc(resultado, capacidad * 2);
      capacidad *= 2;
    }
    //printf("%d -> %s |", i, strv[i]);

    final_actual = stpcpy(i == 0 ? resultado : final_actual, strv[i]);
    if(strv[i + 1]) {
      final_actual = stpcpy(final_actual, separador);
    } 
    
  }
  free(separador);

  return resultado;
}


void free_strv(char *strv[])
{
  for(int i = 0; strv[i]; i++)
  {
    free(strv[i]);
  }
 free(strv);
}