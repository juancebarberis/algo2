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

  if(sep == '\0') {
    resultado[0] = strdup(str);
    resultado[1] = NULL;
    return resultado;
  }

  char* vacio = "";
  
  int k = 0; // Indice del resultado
  int pos_separador = 0; // Indice del separador

  for(int i = 0; i < len + 1; i++)
  {
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

      if(i == 0) {
        resultado[k] = strdup(vacio);
      }
      else {
        if(k > 0) pos_separador++;
        resultado[k] = substr(str + pos_separador, i - pos_separador);
      }
      k++;
      pos_separador = i;
    }
    else if(str[i] == '\0') {
      if(k > 0) pos_separador++;
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
  if(!strv) return strdup("");

  size_t cantidad = 2;
  for(int j = 0; strv[j]; j++)
  {
    cantidad += strlen(strv[j]) + 2;
  }
  char* resultado = calloc(cantidad, sizeof(char));
  
  if(!resultado) return NULL;
  
  if(!strv) return resultado;
  
  char* final_actual;
  
  char* separador = malloc(sizeof(char) * 2);
  separador[0] = sep;
  separador[1] = '\0';

  size_t len = 0;
  
  for(int i = 0; strv[i]; i++)
  {
    len += strlen(strv[i]);

    if(len == 0 && strv[i+1])  {
      final_actual = stpcpy(i == 0 ? resultado : final_actual, separador);
      continue;
    }

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