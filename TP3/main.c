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

///Estructura terminada, faltan validaciones en main.
///Falta revisar todo y comentar.

int main()
{
    int option, employeesCounter = 0;
    LinkedList* employeesList = ll_newLinkedList();
    do
    {
        employee_showMenu(&option, "  1. Cargar datos de empleados desde data.csv (modo texto).\n  2. Cargar datos de empleados desde dataB.csv (modo binario).\n  3. Alta de empleado.\n  4. Modificar datos de empleado.\n  5. Baja de empleado.\n  6. Listar empleados.\n  7. Ordenar empleados.\n  8. Guardar datos de empleados en data.csv (modo texto).\n  9. Guardar datos de empleados en dataB.csv (modo binario).\n 10. Salir.", 1, 10);
        switch(option)
        {
            case 1:
                controller_loadFromText("data.csv", employeesList);
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 2:
                controller_loadFromBinary("dataB.csv", employeesList);
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 3:
                controller_addEmployee(employeesList);
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 4:
                controller_editEmployee(employeesList);
                break;
            case 5:
                controller_removeEmployee(employeesList);
                employeesCounter = ll_len(employeesList);
                system("pause");
                break;
            case 6:
                printf("Empleados en el sistema: %d\n\n", employeesCounter);
                controller_ListEmployee(employeesList);
                system("pause");
                break;
            case 7:
                controller_sortEmployee(employeesList);
                break;
            case 8:
                controller_saveAsText("data.csv", employeesList);
                system("pause");
                break;
            case 9:
                controller_saveAsBinary("dataB.csv", employeesList);
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
