#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Inputs.h"
#include "Utilities.h"
#include "stringFormat.h"

int getInt(char message[])
{   //Pido entero.
    int number;
    printf("Ingrese %s: ", message);
    scanf("%d", &number);
    return number;
}

float getFloat(char message[])
{   //Pido numero decimal.
    float number;
    printf("Ingrese %s: ", message);
    scanf("%f", &number);
    return number;
}

void getChar(char* pChar, char* message)
{   //Pido un caracter.
    printf("Ingrese %s: ", message);
    fflush(stdin);
    scanf("%c", pChar);
}

void getString(char* message, char* pString)
{   //Pido un string.
    printf("Ingrese %s: ", message);
    fflush(stdin);
    scanf("%256[^\n]", pString);
}
/*
char* getValidString(char* message, int ssize, int format)
{   //Realizo las validaciones correspondientes utilizando un auxiliar.
    char* pString = (char*) malloc(sizeof(char)*256);
    getString(message, pString);
    if(format == 0) //Valido tamaño y si tiene solo letras.
    {
        while(strlen(pString) > ssize || validateString(pString) == 0)
        {
            printf("\nError: Solo se permiten letras.\n");
            getString(message, pString);
        }
    }
    else{
        while(strlen(pString) > ssize) //Valido solo tamaño.
        {
            printf("\nError: Se supero la cantidad de caracteres disponibles.\n");
            getString(message, pString);
        }
    }
    int len = strlen(pString);
    pString = (char*) realloc(pString, sizeof(char)*(len+1));
    return pString;
}
*/

void getValidString(char* message, char* str, int ssize, int format)
{   //Realizo las validaciones correspondientes utilizando un auxiliar.
    char auxStr[256];
    getString(message, auxStr);
    if(format == 0) //Valido tamaño y si tiene solo letras.
    {
        while(strlen(auxStr) > ssize || validateString(auxStr) == 0)
        {
            printf("\nError: Solo se permiten letras.\n");
            getString(message, auxStr);
        }
    }
    else{
        while(strlen(auxStr) > ssize) //Valido solo tamaño.
        {
            printf("\nError: Se supero la cantidad de caracteres disponibles.\n");
            getString(message, auxStr);
        }
    }
    strcpy(str, auxStr);
}

void getValidInt(int* pInt, char* message, int low, int high, int format)
{   //Realizo las validaciones correspondientes utilizando auxiliares.
    char auxStr[256];
    int auxInt, finalInt;
    getString(message, auxStr);
    auxInt = atoi(auxStr); //atoi() toma una cadena y convierte a entero si solo hay numeros, caso contrario devuelve 0.
    if(format == 0)
    {   //Si trabajo con formato 0, estoy usando rangos.
        while((auxInt < low || auxInt > high) || (strlen(auxStr) > 51) || (validateIntNumber(auxStr) == 0) || (validateString(auxStr) == 1))
        {
            printf("\nError: Solo se permiten numeros (%d-%d).\n", low, high);
            getString(message, auxStr);
            auxInt = atoi(auxStr);
        }
    }
    finalInt = auxInt;
    *pInt = finalInt;
}

float getPositiveFloat(char* message, float low, float high)
{   //Realizo las validaciones correspondientes utilizando auxiliares.
    char auxStr[256];
    double auxFloat;
    float finalFloat;
    getString(message, auxStr);
    auxFloat = atof(auxStr); //atof() hace lo mismo que atoi() pero con flotantes, la diferencia es que lo devuelve como double.
    while(auxFloat < low || auxFloat > high)
    {   //Si no respeta rango, tiro error.
        printf("\nError: Solo se permiten numeros (low-high).\n");
        getString(message, auxStr);
        auxFloat = atof(auxStr);
    }
    finalFloat = (float)auxFloat; //Por ultimo, paso de double a float.
    return finalFloat;
}
