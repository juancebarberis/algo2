#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include "strutil.h"
#include <stdio.h>

char *substr(const char *str, size_t n){
    char *primeros_n = calloc(sizeof(char), n+1);
    if(!primeros_n) return NULL;

    for(size_t i=0; i<n && str[i]; i++){
        primeros_n[i] = str[i];
    }
    return primeros_n;
}

char **split(const char *str, char sep){
    size_t largo_str = strlen(str);
    size_t contador_sep = 0;
    char separador[2] = {sep, '\0'};
    char *puntero_a_sep = strstr(str, separador);
    while(puntero_a_sep && sep){ //cuento los separadores
        puntero_a_sep = strstr(puntero_a_sep + 1, separador);
        contador_sep++;
    } 

    char **posiciones_sep = malloc(sizeof(char*) * (contador_sep+1));
    if(!posiciones_sep) return NULL;

    puntero_a_sep = strstr(str, separador); 
    contador_sep = 0;
    while(puntero_a_sep && sep){ //armamos el arreglo con las pos de los sep
        posiciones_sep[contador_sep] = puntero_a_sep;
        puntero_a_sep = strstr(puntero_a_sep + 1, separador);
        contador_sep++;
    }
    posiciones_sep[contador_sep] = (char*) str + largo_str;
    char **resultado = malloc(sizeof(char*) * (contador_sep+1+1)); //otro +1 por el NULL del final
    if(!resultado) return NULL;

    char *ini = (char*) str;
    char *fin;
    for(size_t i = 0; ini <= str + largo_str; i++){
        fin = posiciones_sep[i];
        resultado[i] = substr(ini, (fin-ini)/sizeof(char));
        ini = fin + 1;
    }
    resultado[sizeof(char) * (contador_sep+1)] = NULL;

    free(posiciones_sep);
    return resultado;
}

char *join(char **strv, char sep){
    size_t largo_str_final = 0;
    size_t cant_sep = 0;
    for(size_t i = 0; strv[i]; i++){ 
        largo_str_final += strlen(strv[i]);
        cant_sep++;
    }
    char *resultado = malloc(sizeof(char) * (largo_str_final + cant_sep +1)); 
    if(!resultado) return NULL;

    if(!strv[0]){ //Caso borde: strv == {NULL}
        resultado[0] = '\0';
        return resultado;
    }

    char *final = stpcpy(resultado, strv[0]); 
    for(size_t i = 1; strv[i]; i++){
        if(sep) *final++ = sep; //Caso borde: sep == \0
        final = stpcpy(final, strv[i]); 
    }

    return resultado;
}

void free_strv(char *strv[]){
    for(size_t i = 0; strv[i]; i++) free(strv[i]);
    free(strv);
}