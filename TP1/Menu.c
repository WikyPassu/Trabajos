#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Menu.h"
#include "Calculos.h"

/** Voy a ir evaluando el comportamiento del estado de A y B para asi tener actualizado
el valor de las variables y mostrar en pantalla el menu adecuado **/
void mostrarMenu(int est_x, int est_y, float x, float y)
{
        system("cls");
        if(est_x == 0 && est_y == 0){
            printf("-------------------Calculadora--------------------\n");
            printf("\n 1. Ingresar 1er operando.");
            printf("\n 2. Ingresar 2do operando.");
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("--------------------------------------------------\n");
        }
        else if(est_x == 1 && est_y == 1){
            printf("-------------------Calculadora--------------------\n");
            printf("\n 1. Ingresar 1er operando. Actualmente: A = %.2f",x);
            printf("\n 2. Ingresar 2do operando. Actualmente: B = %.2f",y);
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("--------------------------------------------------\n");
        }
        else if(est_x == 1 && est_y == 0){
            printf("-------------------Calculadora--------------------\n");
            printf("\n 1. Ingresar 1er operando. Actualmente: A = %.2f",x);
            printf("\n 2. Ingresar 2do operando.");
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("--------------------------------------------------\n");
        }
        else if(est_x == 0 && est_y == 1){
            printf("-------------------Calculadora--------------------\n");
            printf("\n 1. Ingresar 1er operando.");
            printf("\n 2. Ingresar 2do operando. Actualmente: B = %.2f",y);
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("--------------------------------------------------\n");
        }
}

void elegirOpcion()
{
    int estadoVariables, opcion, entValidA, entValidB, enteroA, enteroB;
    int estadoA = 0, estadoB = 0, flag = 0, indeterminacion = 0;
    unsigned long int factA, factB;
    float a, b, suma, resta, multi, div;
    char seguir = 's', sOpcion[2];
    do{
        mostrarMenu(estadoA,estadoB,a,b);
        printf("\nElija una opcion: ");
        /** Guardo lo ingresado como char, luego utilizo atoi() para transformarlo en numero
        (si lo ingresado es un numero, la funcion lo devolvera como entero, si es letra/simbolo devuelve 0 **/
        scanf("%s",sOpcion);
        opcion = atoi(sOpcion);
        switch(opcion){
            case 1:
                a = ingresarNumero();
                /** A fue ingresado, por lo tanto su estado pasa a 1 **/
                estadoA = 1;
                mostrarMenu(estadoA,estadoB,a,b);
                flag = 0;
                break;
            case 2:
                b = ingresarNumero();
                /** B fue ingresado, por lo tanto su estado pasa a 1 **/
                estadoB = 1;
                mostrarMenu(estadoA,estadoB,a,b);
                flag = 0;
                break;
            case 3:
                /** Compruebo el estado de ambas variables. Si fueron ingresadas, realizo todas las operaciones, sino tiro error **/
                estadoVariables = comprobarEstados(estadoA, estadoB);
                if(estadoVariables == 1){
                    printf("\nCalculando operaciones...");
                    suma = sumar(a,b);
                    resta = restar(a,b);
                    multi = multiplicar(a,b);
                    /** Verifico si el dividendo es 0 para realizar o no la division **/
                    if(b == 0){
                        indeterminacion = 1;
                    }
                    else{
                        div = dividir(a,b);
                    }
                    /** Evaluo por separado si A y B son enteros **/
                    entValidA = validarEntero(a);
                    entValidB = validarEntero(b);
                    /** La condicion para calcular el factorial de un numero sera que dicho numero sea entero,
                    mayor o igual a cero y menor o igual a 12 (maximo calculo posible de factorial en esta calculadora) **/
                    if(entValidA == 1 && a >= 0 && a <= 12){ //Arroja warning si usaba unsigned long long int con mascara %llu, por eso opte por esto.
                        /** Parseo a A como entero en una nueva variable int **/
                        enteroA = (int)a;
                        factA = sacarFactorial(enteroA);
                    }
                    else{
                        factA = 0;
                    }
                    if(entValidB == 1 && b >= 0 && b <= 12){
                        /** Parseo a B como entero en una nueva variable int **/
                        enteroB = (int)b;
                        factB = sacarFactorial(enteroB);
                    }
                    else{
                        factB = 0;
                    }
                    printf("\nTodas las operaciones han sido calculadas con exito!\n\n");
                    /** Este flag me indica que se realizaron todas las operaciones, si se ingresan nuevamente A o B
                    se cambiara a cero para evitar errores a la hora de mostrar los resultados de las operaciones **/
                    flag = 1;
                }
                else{
                    printf("\nError: Primero deben ingresarse A y B para realizar todas las operaciones.\n\n");
                }
                system("pause");
                break;
            case 4:
                /** Compruebo el estado de ambas variables. Luego las evaluo junto al flag. Si fueron ingresadas y
                se calcularon operaciones, muestro resultados, sino tiro error **/
                estadoVariables = comprobarEstados(estadoA, estadoB);
                if(estadoVariables == 1 && flag == 1){
                    printf("\n--------------------Resultados--------------------\n");
                    printf("\n %.2f + %.2f = %.2f",a,b,suma);
                    printf("\n %.2f - %.2f = %.2f",a,b,resta);
                    printf("\n %.2f * %.2f = %.2f",a,b,multi);
                    /** Si existe una indeterminacion, tiro error **/
                    if(indeterminacion == 1){
                        printf("\n Error: No es posible dividir por cero.");
                    }
                    else{
                        printf("\n %.2f / %.2f = %.2f",a,b,div);
                    }
                    /** Evaluo por separado si A y B son enteros y si su factorial es diferente de cero **/
                    if(entValidA == 1 && factA != 0){
                        printf("\n %d! = %lu",enteroA,factA);
                    }
                    /** En caso de que la condicion no de verdadero, tiro error **/
                    else{
                        printf("\n Error: No es posible calcular el %.2f! porque\n es un numero negativo, con coma o su factorial\n da un resultado muy grande.",a);
                    }
                    if(entValidB == 1 && factB != 0){
                        printf("\n %d! = %lu",enteroB,factB);
                    }
                    else{
                        printf("\n Error: No es posible calcular el %.2f! porque\n es un numero negativo, con coma o su factorial\n da un resultado muy grande.",b);
                    }
                    printf("\n\n--------------------------------------------------\n\n");
                }
                else{
                    printf("\nError: Primero deben ingresarse A y B o calcular todas las operaciones para mostrar los resultados.\n\n");
                }
                system("pause");
                break;
            case 5:
                /** Si la opcion salir es elegida, basta con cambiar la variable "seguir" para terminar el programa **/
                printf("\nSaliendo...\nGracias por utilizar esta Calculadora!!!\n\n");
                seguir = 'n';
                system("pause");
                break;
            default:
                printf("\nError: Opcion invalida.\n\n");
                system("pause");
                break;
        }
    }while(seguir == 's');
}

/** A diferencia de antes, esta vez utilizo atof(), cuya funcion es la misma que atoi() pero transforma la cadena de caracteres
ingresada en tipo de dato double. Por lo tanto, luego debo guardar el double parseado a una variable float. De esta manera, si
se ingresa una letra/caracter, atof() devolvera 0 y la variable pasara a valer eso. **/
float ingresarNumero()
{
    char sNum[10];
    double dNum;
    float numero;
    printf("\nIngrese un numero: ");
    scanf("%s",sNum);
    dNum = atof(sNum);
    numero = (float)dNum;
    return numero;
}

int comprobarEstados(int est_a, int est_b)
{
    int estados = 0;
    if(est_a == 1 && est_b == 1){
        estados = 1;
    }
    return estados;
}

/** Al evaluar la diferencia entre el float ingresado y el int declarado, puedo decir si ese numero es o no un entero.
Si el resultado es 0, significa que el numero que entro a la funcion es un entero, caso contrario tiene decimales **/
int validarEntero(float n)
{
    int numero = (int)n, esEntero = 0;
    if(n - numero == 0){
        esEntero = 1;
    }
    return esEntero;
}
