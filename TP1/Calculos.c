#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Calculos.h"

float sumar(float n1, float n2)
{
    float resultado = n1 + n2;
    return resultado;
}

float restar(float n1, float n2)
{
    float resultado = n1 - n2;
    return resultado;
}

float multiplicar(float n1, float n2)
{
    float resultado = n1 * n2;
    return resultado;
}

float dividir(float n1, float n2)
{
    float resultado = n1 / n2;
    return resultado;
}

unsigned long int sacarFactorial(int n)
{
    if(n == 0 || n == 1){
        return 1;
    }
    return n * sacarFactorial(n - 1);
}
