#define _POSIX_C_SOURCE 200809L
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
  char* linea = NULL;
  size_t capacidad = 0;
  
  while(getline(&linea, &capacidad, stdin) > 0)
  {
    if(strlen(linea) == 1) continue;
    convertir(linea);
  }
  free(linea);
  return 0;
}

void convertir(char* linea)
{
  size_t len = strlen(linea);
  char* aux;
  char e;
  int j;
  cola_t* output = cola_crear();
  pila_t* operadores = pila_crear();

  for(int i = 0; i < len; i++)
  {
    e = linea[i];

    if(e == ' ') 
      continue;
    else if (e == '0' || e == '1' || e == '2' || e == '3' || e == '4' || e == '5' || e == '6' || e == '7' || e == '8' || e == '9') {
      j = 0;
      while (e == '0' || e == '1' || e == '2' || e == '3' || e == '4' || e == '5' || e == '6' || e == '7' || e == '8' || e == '9')
      {
        j++;
        e = linea[i + j];
      }
      cola_encolar(output, substr(linea + i, j));
      i += j - 1;
      continue;
    }
    else if (e == '+' || e == '-' || e == '*' || e == '/' || e == '^') {
      // Calculo de precedencia y asociatividad 
      aux = pila_ver_tope(operadores);
      while (aux && (precedencia(aux[0]) > precedencia(e) || (precedencia(aux[0]) == precedencia(e) && e != '^')) && aux[0] != '(')
      {
        cola_encolar(output, pila_desapilar(operadores));
        aux = pila_ver_tope(operadores);
      }
      if (e == '+')
        pila_apilar(operadores, strdup("+"));
      else if (e == '-')
        pila_apilar(operadores, strdup("-"));
      else if (e == '*')
        pila_apilar(operadores, strdup("*"));
      else if (e == '/')
        pila_apilar(operadores, strdup("/"));
      else if (e == '^')
        pila_apilar(operadores, strdup("^"));
    }
    else if (e == '(')
    {
      pila_apilar(operadores, strdup("("));
    }
    else if (e == ')')
    {
      aux = pila_ver_tope(operadores);
      while (aux && aux[0] != '(')
      {
          cola_encolar(output, pila_desapilar(operadores));
          aux = pila_ver_tope(operadores);
      }
      aux = pila_desapilar(operadores);
      free(aux);
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
    if(aux[0] != '(' && aux[0] != ')')
      fprintf(stdout, "%s ", aux);
    free(aux);
  }
  fprintf(stdout, "\n");

  cola_destruir(output, free);
  pila_destruir(operadores);
  return;
}