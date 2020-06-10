#include<stdlib.h>
#include<string.h>

int es_operando(char* cadena)
{
  if(strcmp(cadena, "+") != 0 
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
