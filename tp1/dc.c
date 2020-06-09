#define _POSIX_C_SOURCE 200809L
#define CANTIDAD_INICIAL 100
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "strutil.h"
#include "pila.h"

bool es_operando(char* cadena)
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
    return true;
  else
    return false;
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

int calcular(char* linea)
{
  char** elementos = split(linea, ' ');

  if(!elementos) return 1;

  char* elemento;
  long *aux;
  long *aux2;
  long *aux3;
  size_t operandos = 0;
  pila_t* pila = pila_crear();

  for(int i = 0; elementos[i]; i++)
  {
    elemento = elementos[i];

    if(strlen(elemento) == 0) continue;

    printf("Elemento -> %s (%ld) OPERANDOS: %ld \n", elemento, strlen(elemento), operandos);

    if(es_operando(elemento)) {
      pila_apilar(pila, dynatol(elemento));
      operandos++;
    }
    else {
      if(operador_necesita(elemento) > operandos) {
        fprintf(stdout, "ERROR\n");
        pila_destruir(pila);
        free_strv(elementos);
        return 0;
      }
      else {
        //Comparación del elemento con el operador. Si conincide, opera.
        if(strcmp(elemento, "+") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux = dynlong(*aux + *aux2);
        }
        else if(strcmp(elemento, "-") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux = dynlong(*aux2 - *aux);
        }
        else if(strcmp(elemento, "*") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux = dynlong(*aux2 * *aux);
        }
        else if(strcmp(elemento, "/") == 0) {
          aux = pila_desapilar(pila);
          if(*aux == 0) {
            free(aux);
            break;
          }
          aux2 = pila_desapilar(pila);
          aux = dynlong(*aux2 / *aux);
        }
        else if(strcmp(elemento, "^") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux = dynlong((long) powl((long double) *aux2, (long double) *aux));
        }
        else if(strcmp(elemento, "sqrt") == 0) {
          aux = pila_desapilar(pila);
          aux2 = NULL;
          aux = dynlong( (long) sqrt((double) *aux));
        }
        else if(strcmp(elemento, "log") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux = dynlong( (long) (log((double) *aux2) / log((double) *aux)) );
        }
        else if(strcmp(elemento, "?") == 0) {
          aux = pila_desapilar(pila);
          aux2 = pila_desapilar(pila);
          aux3 = pila_desapilar(pila);
          aux = dynlong(*aux3 ? *aux2 : *aux);
          free(aux3);
        }
        else {
          fprintf(stdout, "ERROR de else \n");
          pila_destruir(pila);
          free_strv(elementos);
          return 0;
        }
        // Fin de la tortuosa comparación
        pila_apilar(pila, aux);
        free(aux2);
        operandos -= operador_necesita(elemento) - 1;
      }
    }
  }

  if(pila_esta_vacia(pila))
    return 1;

  aux = pila_ver_tope(pila);
  if(operandos > 1)
    fprintf(stdout, "ERROR\n");
  else
    fprintf(stdout, "%ld\n", *aux);

  pila_destruir(pila);
  free_strv(elementos);
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
  char* linea;
  
  while(fgets(buffer, 100, stdin))
  {
    linea = substr(buffer, strlen(buffer) - 1);
    error_count += calcular(linea);
    free(linea);
  }
  if(error_count > 0)
    fprintf(stderr, "Errores durante la ejecución -> %d\n", error_count);

  free(buffer);
  return error_count;
}
