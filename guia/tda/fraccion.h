#ifndef __FRAC_H_
#define __FRAC_H_

typedef struct fraccion fraccion_t;

/**
Crea una fraccion con el numerador y denominador indicados. 
Si el denominador es 0, o hubo algÃºn error, devuelve NULL.
**/
fraccion_t* fraccion_crear(int numerador, int denominador);

/**
- Crea una nueva fraccion, con el resultante de hacer la suma de las fracciones originales
- Las fracciones originales son destruidas
En caso de algÃºn error, la funciÃ³n devuelve NULL y las fracciones originales no serÃ¡n destruidas
**/
fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2);

/**
- Crea una nueva fraccion, con el resultante de multiplicar ambas fracciones originales
- Las fracciones originales son destruidas
En caso de algÃºn error, la funciÃ³n devuelve NULL y las fracciones originales no serÃ¡n destruidas
**/
fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2);

/**
Devuelve la parte entera del numero representado por la fracciÃ³n. Por ejemplo, para "7/2" = 3.5 debe
devolver 3. 
**/
int fraccion_parte_entera(fraccion_t* fraccion);

/**
Devuelve una representaciÃ³n en cadena de la fraccion simplificada (por ejemplo, no puede devolverse
"10/8" sino que debe ser "5/4"). Considerar que si se trata de un nÃºmero entero, debe mostrarse como tal.
Considerar tambien el caso que se trate de un nÃºmero negativo. 
La cadena devuelta provendrÃ¡ de memoria dinÃ¡mica por lo que el usuario debe liberarla usando free. 
**/
char* fraccion_representacion(fraccion_t* fraccion);

/**
Destruye una fracciÃ³n, liberando toda la memoria asociada. 
**/
void fraccion_destruir(fraccion_t* fraccion);

int mcd(int a, int b);
size_t calcular_largo(int numero);
void pruebas();

#endif