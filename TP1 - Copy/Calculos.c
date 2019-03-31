#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

int sumar(int n1, int n2)
{
    int resultado = n1 + n2;
    return resultado;
}

int restar(int n1, int n2)
{
    int resultado = n1 - n2;
    return resultado;
}

int multiplicar(int n1, int n2)
{
    int resultado = n1 * n2;
    return resultado;
}

float dividir(int n1, int n2)
{
    float resultado = n1 / (float)n2;
    return resultado;
}

int sacarFactorial(int n)
{
    if(n >= 0){
        if(n == 0 || n == 1){
            return 1;
        }
        return n * sacarFactorial(n - 1);
    }
    return 0;
}
