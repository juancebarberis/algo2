#include <stdbool.h>
#include <stdio.h>


int bytelandes_to_pesos(int bytelandeses)
{
    if(bytelandeses == 0)
        return 0;

    int dos = bytelandes_to_pesos(bytelandeses / 2);
    int tres = bytelandes_to_pesos(bytelandeses / 3);
    int cuatro = bytelandes_to_pesos(bytelandeses / 4);
    
    return dos + tres + cuatro > bytelandeses ? dos + tres + cuatro : bytelandeses;
}


int main()
{
    printf("12 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(12));
    printf("24 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(24));
    printf("5 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(5));
    printf("10 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(10));
    printf("45 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(45));
    printf("100 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(100));
    printf("21 bytelandeses -> %d pesos Argentinos. \n", bytelandes_to_pesos(21));
    return 0;
}