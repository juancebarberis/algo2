#define _POSIX_C_SOURCE 200809L
#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include "strutil.h"
#include "calcutil.h"

int es_operador(char* cadena)
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
    return 0;
  else
    return 1;
}

long* dynatol(const char *str)
{
  char* resto;
  long r = strtol(str, &resto, 10);

  if(resto == str || *resto != '\0') return NULL;

  long* value = malloc(sizeof(long));

  if(!value) return NULL;

  value[0] = r;

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

