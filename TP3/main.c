#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/***********************************************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
***********************************************************************************/

///Falta revisar todo, intentar separar librerias y comentar todo el codigo.
///Falta hacer ID incremental. Contador de ID pasado al controller de addEmployee.

int main()
{
    int option, employeesCounter = 0, flag = 0;
    LinkedList* employeesList = ll_newLinkedList();
    do
    {
        employee_showMenu(&option, "  1. Cargar datos de empleados desde data.csv (modo texto).\n  2. Cargar datos de empleados desde dataB.csv (modo binario).\n  3. Alta de empleado.\n  4. Modificar datos de empleado.\n  5. Baja de empleado.\n  6. Listar empleados.\n  7. Ordenar empleados.\n  8. Guardar datos de empleados en data.csv (modo texto).\n  9. Guardar datos de empleados en dataB.csv (modo binario).\n 10. Salir.", 1, 10);
        switch(option)
        {
            case 1:
                if(controller_loadFromText("data.csv", employeesList) == 0)
                {
                    printf("Error: No se pudo abrir/leer el archivo en formato texto.\n\n");
                }
                else
                {
                    flag = 1;
                }
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 2:
                if(controller_loadFromBinary("dataB.csv", employeesList) == 0)
                {
                    printf("Error: No se pudo abrir/leer el archivo en formato binario.\n\n");
                }
                else
                {
                    flag = 1;
                }
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 3:
                if(flag == 1)
                {
                    if(controller_addEmployee(employeesList) == 0)
                    {
                        printf("Error: No se pudo realizar la carga de un empleado al sistema.\n\n");
                    }
                    employeesCounter = ll_len(employeesList);
                }
                else
                {
                    printf("Error: Antes de ingresar empleados se debe cargar un archivo.\n\n");
                }
                system("pause");
                break;
            case 4:
                if(employeesCounter > 0)
                {
                    if(controller_editEmployee(employeesList) == 0)
                    {
                        printf("Error: No se pudo ingresar al menu de modificaciones.\n\n");
                    }
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                    system("pause");
                }
                break;
            case 5:
                if(employeesCounter > 0)
                {
                    if(controller_removeEmployee(employeesList) == 0)
                    {
                        printf("Error: No se pudo ingresar al menu de eliminacion.\n\n");
                    }
                    employeesCounter = ll_len(employeesList);
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                }
                system("pause");
                break;
            case 6:
                if(employeesCounter > 0)
                {
                    printf("Empleados en el sistema: %d\n\n", employeesCounter);
                    controller_ListEmployee(employeesList);
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                }
                system("pause");
                break;
            case 7:
                if(employeesCounter > 0)
                {
                    if(controller_sortEmployee(employeesList) == 0)
                    {
                        printf("Error: No se puedo ingresar al menu de ordenamiento.\n\n");
                    }
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                    system("pause");
                }
                break;
            case 8:
                if(employeesCounter > 0)
                {
                    if(controller_saveAsText("data.csv", employeesList) == 0)
                    {
                        printf("Error: No se pudo crear el archivo en formato texto.\n\n");
                    }
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                }
                system("pause");
                break;
            case 9:
                if(employeesCounter > 0)
                {
                    if(controller_saveAsBinary("dataB.csv", employeesList) == 0)
                    {
                        printf("Error: No se pudo crear el archivo en formato texto.\n\n");
                    }
                }
                else
                {
                    printf("Error: No hay empleados cargados en el sistema.\n\n");
                }
                system("pause");
                break;
            case 10:
                printf("Saliendo...\n\n");
                Sleep(500);
                ll_deleteLinkedList(employeesList);
                printf("Programa terminado.\n\n");
                system("pause");
                break;
        }
    }while(option != 10);
    return 0;
}
