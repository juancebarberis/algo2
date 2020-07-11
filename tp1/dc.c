#define CANTIDAD_INICIAL 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "strutil.h"
#include "calcutil.h"
#include "pila.h"

/**
 * Realiza el cálculo en notación polaca inversa.
 * Imprime por salida stdout el resultado, o ERROR en caso de que la operación no se lleve a cabo.
 * */
void calcular(char* linea);


int main(int argc, char* argv[])
{
  char* buffer = malloc(sizeof(char) * CANTIDAD_INICIAL);

  if(!buffer) {
    fprintf(stderr, "No es posible alojar memoria inicial...\n");
    return -1;
  }

  size_t linea_len;
  
  while(fgets(buffer, CANTIDAD_INICIAL, stdin))
  {
    linea_len = strlen(buffer);

    if(buffer[linea_len - 1] == '\n') {
      buffer[linea_len - 1] = '\0';
    }
    
    calcular(buffer);
  }
  free(buffer);
  return 0;
}

void calcular(char* linea)
{
  char** elementos = split(linea, ' ');

  if(!elementos) return;

  char* elemento;
  long *aux;
  long *aux2;
  long *aux3;
  long res;
  int err_count = 0;
  size_t operandos = 0;
  pila_t* pila = pila_crear();

  for(int i = 0; elementos[i]; i++)
  {
    elemento = elementos[i];

    if(strlen(elemento) == 0) continue;

    if(!es_operador(elemento)) {
      if ((aux = dynatol(elemento)) != NULL) {
        pila_apilar(pila, aux);
        operandos++;
        continue;
      } else if (!es_operador(elemento) || operador_necesita(elemento) > operandos) {
        err_count++;
        break;
      }
    }
    else {
      if(operador_necesita(elemento) > operandos) {
        err_count++;
        break;
      }
      else {
        //Comparación del elemento con el operador. Si conincide, opera.
        aux = pila_desapilar(pila);
        aux2 = NULL;
        res = 0;
        if(strcmp(elemento, "+") == 0) {
          aux2 = pila_desapilar(pila);
          res = *aux + *aux2;
        }
        else if(strcmp(elemento, "-") == 0) {
          aux2 = pila_desapilar(pila);
          res = *aux2 - *aux;
        }
        else if(strcmp(elemento, "*") == 0) {
          aux2 = pila_desapilar(pila);
          res = *aux2 * *aux;
        }
        else if(strcmp(elemento, "/") == 0) {
          if(*aux == 0) {
            free(aux);
            err_count++;
            break;
          }
          aux2 = pila_desapilar(pila);
          res = *aux2 / *aux;
        }
        else if(strcmp(elemento, "^") == 0) {
          if(*aux < 0) {
            free(aux);
            err_count++;
            break;
          }
          aux2 = pila_desapilar(pila);
          res = pow(*aux2, *aux);
        }
        else if(strcmp(elemento, "sqrt") == 0) {
          if(*aux < 0) {
            free(aux);
            err_count++;
            break;
          }
          res = sqrt(*aux);
        }
        else if(strcmp(elemento, "log") == 0) {
          if(*aux < 2) {
            free(aux);
            err_count++;
            break;
          }
          aux2 = pila_desapilar(pila);
          res = log(*aux2) / log(*aux);
        }
        else if(strcmp(elemento, "?") == 0) {
          aux2 = pila_desapilar(pila);
          aux3 = pila_desapilar(pila);
          res = *aux3 ? *aux2 : *aux;
          free(aux3);
        }
        // Fin de la tortuosa comparación
        free(aux);
        free(aux2);
        aux = dynlong(res);
        pila_apilar(pila, aux);
        operandos -= operador_necesita(elemento) - 1;
      }
    }
  }

  if(operandos > 1 || err_count > 0)
      fprintf(stdout, "ERROR\n");
  else if(!pila_esta_vacia(pila)) {
    aux = pila_ver_tope(pila);
    fprintf(stdout, "%ld\n", *aux);
  }
  
  pila_destruir(pila);
  free_strv(elementos);
}
