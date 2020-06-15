#define _POSIX_C_SOURCE 200809L
#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include "strutil.h"

int es_operando(char* cadena)
{
  if(
    strcmp(cadena, "+") != 0 
    && strcmp(cadena, "-") != 0 
    && strcmp(cadena, "/") != 0 
    && strcmp(cadena, "*") != 0 
    && strcmp(cadena, "sqrt") != 0 
    && strcmp(cadena, "^") != 0 
    && strcmp(cadena, "log") != 0 
    && strcmp(cadena, "?") != 0
    )
    return 1;
  else
    return 0;
}

long* dynatol(const char *str)
{
  long* value = malloc(sizeof(long));

  if(!value) 
    return NULL;

  value[0] = atol(str);

  return value; 
}

long *dynlong(long val)
{
  long* value = malloc(sizeof(long));

  if(!value) 
    return NULL;

  value[0] = val;

  return value;   
}

size_t operador_necesita(char* operador)
{
  if(strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0 || strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0 || strcmp(operador, "^") == 0 || strcmp(operador, "log") == 0)
    return 2;
  else if(strcmp(operador, "sqrt") == 0)
    return 1;
  else if(strcmp(operador, "?") == 0)
    return 3;
  
  return 0;
}

int precedencia(char operador)
{
  if(operador == '^')
    return 3;
  else if(operador == '*' || operador == '/')
    return 2;
  else if(operador == '+' || operador == '-')
    return 1;
  
  return 0;
}

int in_string(char* cadena, char* permitidos) 
{
  size_t equals;
  for(int i = 0; i < strlen(cadena); i++)
  {
    equals = 0;
    for(int j = 0; j < strlen(permitidos); j++)
    { 
      if(cadena[i] == permitidos[j]) {
        equals++;
        break;  
      }
    }
    if(equals == 0) return 0;
  }
  return 1;
}

char** parse_linea(char* linea)
{
  size_t len = strlen(linea);
  char** resultado = calloc(len + 1, sizeof(char*));
  size_t k = 0;
  size_t aux = 0;

  if(!resultado) return NULL;
  
  char actual;

  for(int i = 0; i < len; i++)
  {
    actual = linea[i];
    if (actual == '\n')
      break;
    else if(actual == ' ')
      continue;
    else if(actual == '(')
      resultado[k] = strdup("(");
    else if(actual == ')')
      resultado[k] = strdup(")");
    else if(actual == '+')
      resultado[k] = strdup("+");
    else if(actual == '-')
      resultado[k] = strdup("-");
    else if(actual == '/')
      resultado[k] = strdup("/");
    else if(actual == '*')
      resultado[k] = strdup("*");
    else if(actual == '^')
      resultado[k] = strdup("^");
    else {  //Entonces tiene que ser un numero
      aux = 0;
      while (actual == '0' || actual == '1' || actual == '2' || actual == '3' || actual == '4' || actual == '5' || actual == '6' || actual == '7' || actual == '8' || actual == '9')
      {
        aux++;
        actual = linea[i + aux];
      }
      resultado[k] = substr(linea + i, aux);
      i += aux - 1;
    }
    k++;
  }
  resultado[k] = NULL;
  return resultado;
}