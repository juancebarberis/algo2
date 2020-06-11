#define CANTIDAD_INICIAL 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strutil.h"
#include "calcutil.h"
#include "pila.h"
#include "cola.h"

void convertir(char* linea);

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

void convertir(char* linea)
{
  char** elementos = split(linea, ' ');

  if(!elementos) return;

  char* elemento;
  char* aux;
  cola_t* output = cola_crear();
  pila_t* operadores = pila_crear();

  for(int i = 0; elementos[i]; i++)
  {
    elemento = elementos[i];

    if(strlen(elemento) == 0) continue;

    if(es_operando(elemento) && strcmp(elemento, "(") != 0 && strcmp(elemento, ")") != 0) {
      cola_encolar(output, elemento);
      continue;
    }
    else if(strcmp(elemento, "(") == 0) {
      pila_apilar(operadores, elemento);
    }
    else if(strcmp(elemento, ")") == 0) {
      aux = pila_desapilar(operadores);
      while(strcmp(aux, "(") != 0) {
        cola_encolar(output, aux);
        aux = pila_desapilar(operadores);
      }
    }
    else if(!es_operando(elemento)) {
      if(!pila_esta_vacia(operadores)) {
        aux = pila_ver_tope(operadores);
        while(!pila_esta_vacia(operadores) && ( precedencia(aux) > precedencia(elemento) || (precedencia(aux) == precedencia(elemento) && strcmp(elemento, "^") != 0)  ) && strcmp(aux, "(") )
        {
          cola_encolar(output, pila_desapilar(operadores));
        }
      }
      pila_apilar(operadores, elemento);
    }
    else {
      fprintf(stdout, "Algo salió mal. Llegamos al else :( \n");
      return;
    }
  }

  if(cola_esta_vacia(output))
    fprintf(stdout, "ERROR");

  while(!pila_esta_vacia(operadores))
  {
    cola_encolar(output, pila_desapilar(operadores));
  }

  while(!cola_esta_vacia(output))
  {
    aux = cola_desencolar(output);
    if(strcmp(aux, "(") == 0 || strcmp(aux, ")") == 0) continue;
    fprintf(stdout, "%s ", aux);
  }
  fprintf(stdout, "\n");

  cola_destruir(output, free);
  pila_destruir(operadores);
  free_strv(elementos);
  return;
}