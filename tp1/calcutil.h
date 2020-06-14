#ifndef _CALCUTIL
#define _CALCUTIL

#include<stdlib.h>

/**
 * Recibe una cadena y comprueba si es una operando válido.
 * Devuelve 1 en caso de que sea un operando, o 0 si no lo es.
 * */
int es_operando(char* cadena);

/**
 * Recibe una cadena y la convierte a long, alojandola en memoria dinámica.
 * Pre: la cadena puede ser convertida porque es un operando válido. 
 * 
 * Devuelve NULL si no se logró alojar memoria suficiente.
 * */
long* dynatol(const char *str);

/**
 * Recibe un valor de tipo long y lo almacena en memoria dinámica.
 * 
 * Devuelve NULL si no se logró alojar memoria suficiente.
 * */
long *dynlong(long val);

/**
 * Recibe un operador en formato char*.
 * Devuelve la cantidad de operandos que necesita para operar.
 * */
size_t operador_necesita(char* operador);

/**
 * Otorga un valor numerico a la precedencia de un operador
 * */
int precedencia(char* operador);

/**
 * Determina si cada elemento de cadena pertenece a uno en permitidos.
 * Devuelve 1 en caso de que lo sea, o 0 de lo contrario.
 * */
int in_string(char* cadena, char* permitidos);

/**
 * Recibe una cadena que representa una entrada en notación infija y devuelve un arreglo de cadenas separando elementos y numeros de manera correcta. 
 * Limpia la cadena de ENF, espacios y cosas que no son comparables.
 * */
char** parse_linea(char* linea);

#endif