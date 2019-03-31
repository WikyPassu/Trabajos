#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

// Programa terminado, todos los posibles errores han sido solucionados.
// Faltaria documentar los prototipos de funciones, todo el Menu.c y todo el Calculos.c

void mostrarMenu(int est_x, int est_y, int x, int y)
{
        system("cls");
        if(est_x == 0 && est_y == 0){
            printf("------------------Calculadora------------------\n");
            printf("\n 1. Ingresar 1er operando.");
            printf("\n 2. Ingresar 2do operando.");
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("-----------------------------------------------\n");
        }
        else if(est_x == 1 && est_y == 1){
            printf("------------------Calculadora------------------\n");
            printf("\n 1. Ingresar 1er operando. Actualmente: A = %d",x);
            printf("\n 2. Ingresar 2do operando. Actualmente: B = %d",y);
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("-----------------------------------------------\n");
        }
        else if(est_x == 1 && est_y == 0){
            printf("------------------Calculadora------------------\n");
            printf("\n 1. Ingresar 1er operando. Actualmente: A = %d",x);
            printf("\n 2. Ingresar 2do operando.");
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("-----------------------------------------------\n");
        }
        else if(est_x == 0 && est_y == 1){
            printf("------------------Calculadora------------------\n");
            printf("\n 1. Ingresar 1er operando.");
            printf("\n 2. Ingresar 2do operando. Actualmente: B = %d",y);
            printf("\n 3. Calcular todas las operaciones (+ - * / !)");
            printf("\n 4. Informar resultados.");
            printf("\n 5. Salir.\n\n");
            printf("-----------------------------------------------\n");
        }
}

void elegirOpcion()
{
    int estadoA = 0, estadoB = 0, flag = 0, estadoVariables, opcion, a, b;
    int suma, resta, multi, factA, factB, indeterminacion = 0;
    float div;
    char seguir = 's', sOpcion[1];
    do{
        mostrarMenu(estadoA,estadoB,a,b);
        printf("\nElija una opcion: ");
        scanf("%s",sOpcion);
        opcion = atoi(sOpcion);
        if(opcion != 0){
            switch(opcion){
                case 1:
                    a = ingresarNumero();
                    estadoA = 1;
                    mostrarMenu(estadoA,estadoB,a,b);
                    flag = 0;
                    break;
                case 2:
                    b = ingresarNumero();
                    estadoB = 1;
                    mostrarMenu(estadoA,estadoB,a,b);
                    flag = 0;
                    break;
                case 3:
                    estadoVariables = comprobarEstados(estadoA, estadoB);
                    if(estadoVariables == 1){
                        printf("\nCalculando operaciones...");
                        suma = sumar(a,b);
                        resta = restar(a,b);
                        multi = multiplicar(a,b);
                        if(b == 0){
                            indeterminacion = 1;
                        }
                        else{
                            div = dividir(a,b);
                        }
                        factA = sacarFactorial(a);
                        factB = sacarFactorial(b);
                        printf("\nTodas las operaciones han sido calculadas con exito!\n\n");
                        flag = 1;
                    }
                    else{
                        printf("\nError: Primero deben ingresarse A y B para realizar todas las operaciones.\n\n");
                    }
                    system("pause");
                    break;
                case 4:
                    estadoVariables = comprobarEstados(estadoA, estadoB);
                    if(estadoVariables == 1 && flag == 1){
                        printf("\n---------------Resultados---------------\n");
                        printf("\n %d + %d = %d",a,b,suma);
                        printf("\n %d - %d = %d",a,b,resta);
                        printf("\n %d * %d = %d",a,b,multi);
                        if(indeterminacion != 0){
                            printf("\nError: No es posible dividir por cero.");
                        }
                        else{
                            printf("\n %d / %d = %.2f",a,b,div);
                        }
                        if(factA != 0){
                            printf("\n %d! = %d",a,factA);
                        }
                        else{
                            printf("\nError: No es posible sacar el %d! porque\nes un numero negativo.",a);
                        }
                        if(factB != 0){
                            printf("\n %d! = %d",b,factB);
                        }
                        else{
                            printf("\nError: No es posible sacar el %d! porque\nes un numero negativo.",b);
                        }
                        printf("\n\n----------------------------------------\n\n");
                    }
                    else{
                        printf("\nError: Primero deben ingresarse A y B o calcular todas las operaciones para mostrar los resultados.\n\n");
                    }
                    system("pause");
                    break;
                case 5:
                    printf("\nSaliendo...\nGracias por utilizar esta Calculadora!!!\n\n");
                    seguir = 'n';
                    system("pause");
                    break;
                default:
                    printf("\nError: Opcion invalida.\n\n");
                    system("pause");
                    break;
            }
        }
        else{
            printf("\nError: Opcion invalida.\n\n");
            system("pause");
        }
    }while(seguir == 's');
}

int ingresarNumero()
{
    int numero;
    char sNum[10];
    printf("\nIngrese un numero: ");
    scanf("%s",sNum);
    numero = atoi(sNum);
    return numero;
}

int comprobarEstados(int est_a, int est_b)
{
    if(est_a == 1 && est_b == 1){
        return 1;
    }
    return 0;
}
