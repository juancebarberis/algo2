#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>

void pruebas_substr()
{
  printf("Prueba con varias cadenas de substr...\n");
  
  const char* ejemplo = "Ejemplo";
  char* prueba0 = substr("Hola mundo", 6);
  char* prueba1 = substr("Algoritmos", 30);
  char* prueba2 = substr("juancebarberis", 3);
  char* prueba3 = substr("", 2);
  char* prueba4 = substr(ejemplo, 2);
  char* prueba5 = substr(ejemplo + 4, 2);

  printf("Prueba de substr 0: %s \n", prueba0);
  printf("Prueba de substr 1: %s \n", prueba1);
  printf("Prueba de substr 2: %s \n", prueba2);
  printf("Prueba de substr 3: %s \n", prueba3);
  printf("Prueba de substr 4: %s \n", prueba4);
  printf("Prueba de substr 5: %s \n", prueba5);

  free(prueba0);
  free(prueba1);
  free(prueba2);
  free(prueba3);
  free(prueba4);
  free(prueba5);
}

void pruebas_split()
{
  printf("\nPrueba con varias cadenas de split...\n");
  
  char** prueba0 = split("abc,,def", ',');
  printf("Prueba de split 0 -> [%s - %s - %s] \n", prueba0[0], prueba0[1], prueba0[2]);
  char** prueba1 = split("abc,def,", ',');
  printf("Prueba de split 1 -> [%s - %s - %s] \n", prueba1[0], prueba1[1], prueba1[2]);
  char** prueba2 = split(",abc,def", ',');
  printf("Prueba de split 2 -> [%s - %s - %s] \n", prueba2[0], prueba2[1], prueba2[2]);
  char** prueba3 = split("juancebarberis", '\0')    ;
  printf("Prueba de split 3 -> [%s] \n", prueba3[0]);
  char** prueba4 = split("", ',');
  printf("Prueba de split 4 -> [%s] \n", prueba4[0]);
  char** prueba5 = split(",", ',');
  printf("Prueba de split 5 -> [%s - %s] \n", prueba5[0], prueba5[1]);
  char** prueba6 = split("abc,def,ghi,zzz", ',');
  printf("Prueba de split 6 -> [%s - %s - %s - %s] \n", prueba6[0], prueba6[1], prueba6[2], prueba6[3]);
  char** prueba7 = split("a,b,c,,e,f,g,h,i,j", ',');
  printf("Prueba de split 7 (Solo separadores) -> [%s - %s - %s - %s - %s - %s - %s - %s - %s - %s] \n", prueba7[0], prueba7[1], prueba7[2], prueba7[3], prueba7[4], prueba7[5], prueba7[6], prueba7[7], prueba7[8], prueba7[9]);
  char** prueba8 = split(",,,,,", ',');
  printf("Prueba de split 8 (Solo separadores) -> [%s - %s - %s - %s - %s - %s - %s] \n", prueba8[0], prueba8[1], prueba8[2], prueba8[3], prueba8[4], prueba8[5], prueba8[6]);
  char **prueba9 = split("abc,", ',');
  printf("Prueba de split 9 (Sep. extra al final) -> [%s - %s - %s] \n", prueba9[0], prueba9[1], prueba9[2]);
  char **prueba10 = split(",abc", ',');
  printf("Prueba de split 10 (Sep. extra al principio) -> [%s - %s - %s] \n", prueba10[0], prueba10[1], prueba10[2]);

  free_strv(prueba0);
  free_strv(prueba1);
  free_strv(prueba2);
  free_strv(prueba3);
  free_strv(prueba4);
  free_strv(prueba5);
  free_strv(prueba6);
  free_strv(prueba7);
  free_strv(prueba8);
  free_strv(prueba9);
  free_strv(prueba10);
}

void pruebas_join()
{
  printf("\nPrueba para join... \n");
  
  char **strv = split("abc,def,ghi", ',');
  char *resultado = join(strv, ';');  // "abc;def;ghi"
  printf("Prueba cátedra 1 -> %s | [%s] [%s] [%s] \n", resultado, strv[0], strv[1], strv[2]);
  
  char **palabras = split("Hola mundo", ' ');
  char *otro_resultado = join(palabras, ',');  // "Hola,mundo"
  printf("Prueba cátedra 2 -> %s | [%s] [%s] \n", otro_resultado, palabras[0], palabras[1]);
  
  free_strv(strv);
  free_strv(palabras);
  free(resultado);
  free(otro_resultado);
  
  printf("\nPrueba casos bordes para join... \n");

  char** prueba0 = split("", ',');
  char* pruebares0 = join(prueba0, ',');
  printf("Prueba 0 join: %s \n", pruebares0);
  free_strv(prueba0);
  free(pruebares0);

  char** prueba1 = split("abc", ',');
  char* pruebares1 = join(prueba1, ',');
  printf("Prueba 1 join: %s \n", pruebares1);
  free_strv(prueba1);
  free(pruebares1);

  char** prueba2 = split(",", ',');
  char* pruebares2 = join(prueba2, ',');
  printf("Prueba 2 join: %s \n", pruebares2);
  free_strv(prueba2);
  free(pruebares2);

  char* pruebares3 = join(NULL, ',');
  printf("Prueba 3 join: %s \n", pruebares3);
  free(pruebares3);

  char** prueba4 = split("juancebarberis", ',');
  char* pruebares4 = join(prueba4, '\0');
  printf("Prueba 4 join: %s \n", pruebares4);
  free_strv(prueba4);
  free(pruebares4);
}


int main()
{
  pruebas_substr();
  pruebas_split();
  pruebas_join();
  return 0;
}