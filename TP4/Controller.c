#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Inputs.h"
#include "stringFormat.h"
#include "Utilities.h"
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int state = 0;
    FILE* pFile;
    pFile = fopen(path, "r");

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        state = parser_EmployeeFromText(pFile, pArrayListEmployee);
    }

    return state;
}

/** \brief Carga los datos de los empleados desde el archivo dataB.csv (modo binario).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int state = 0;
    FILE* pFile;
    pFile = fopen(path, "rb");

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        state = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
    }

    return state;
}

/** \brief Alta de empleados
 *
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \param lastId int* Ultimo id
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien, 2 si se cancelo la carga del empleado
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int* lastId)
{
    int state = 0, hoursWorked, salary;
    char name[51];

    if(pArrayListEmployee != NULL)
    {   ///Obtengo datos del empleado
        printf("Ingresando datos del empleado...\n\n");
        getValidString("nombre", name, 51, 0);
        getValidInt(&hoursWorked, "horas trabajadas", 1, 400, 0);
        getValidInt(&salary, "salario", 1, 200000, 0);

        Employee* newEmployee = employee_newParameters(*lastId, name, hoursWorked, salary);
        employee_printOneEmployee(newEmployee, 1);

        if(employee_verifyCompliance("'s' si desea dar de alta al empleado")) ///Verifico si el usuario esta de acuerdo con el alta
        {
            ll_add(pArrayListEmployee, newEmployee);
            state = 1;
            printf("\nSe dio de alta al empleado exitosamente.\n\n");
        }
        else
        {
            employee_delete(newEmployee);
            state = 2;
            printf("\nSe cancelo la carga del empleado al sistema.\n\n");
        }
    }

    return state;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int option, state = 0;
    Employee* currentEmployee = NULL;

    if(pArrayListEmployee != NULL)
    {
        do
        {
            employee_showMenu(&option, " 1. Seleccionar empleado.\n 2. Modificar nombre.\n 3. Modificar horas trabajadas.\n 4. Modificar salario.\n 5. Atras.", 1, 5);
            switch(option)
            {
                case 1:
                    currentEmployee = employee_get(pArrayListEmployee); ///Para poder modificar datos primero se tiene que elegir a un empleado
                    system("pause");
                    break;
                case 2:
                    employee_modifyName(currentEmployee);
                    system("pause");
                    break;
                case 3:
                    employee_modifyHW(currentEmployee);
                    system("pause");
                    break;
                case 4:
                    employee_modifySalary(currentEmployee);
                    system("pause");
                    break;
                case 5:
                    state = 1;
                    break;
            }
        }while(option != 5);
    }

    return state;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    Employee* oneEmployee;
    int i, state = 0;

    if(pArrayListEmployee != NULL)
    {
        printf("Empleados en el sistema: %d\n\n", ll_len(pArrayListEmployee));
        printf("Mostrando lista de empleados...\n\n");
        Sleep(800);
        printf("--------------------------------------\n");
        printf("%3s %16s %6s %9s", "ID", "Nombre", "Hs.", "Salario");
        printf("\n--------------------------------------\n");
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            if(i%250 == 0) ///Los voy mostrando de a 250. Comentar este if si se desea que se impriman todos sin tener que presionar tecla para continuar
            {
                system("pause");
            }
            oneEmployee = ll_get(pArrayListEmployee, i);
            employee_printOneEmployee(oneEmployee, 0);
        }
        printf("--------------------------------------\n\n");
        state = 1;
    }

    return state;
}

/** \brief Baja de empleado
 *
* \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien, 2 si se cancelo la baja del empleado
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int state = 0, toRemove, index; ///toRemove guarda el id del empleado a eliminar
    Employee* employeeToRemove;

    if(pArrayListEmployee != NULL)
    {
        controller_ListEmployee(pArrayListEmployee);
        getValidInt(&toRemove, "ID del empleado a eliminar del sistema", 1, 5000, 0);

        index = employee_verifyIfIsInList(pArrayListEmployee, toRemove); ///Verifico que exista el empleado con ese id y retorno su index

        if(index != -1) ///Si existe
        {
            employeeToRemove = ll_get(pArrayListEmployee, index);
            employee_printOneEmployee(employeeToRemove, 1);

            if(employee_verifyCompliance("'s' si desea eliminar al empleado del sistema")) ///Pregunto si el usuario quiere eliminar al empleado
            {
                ll_remove(pArrayListEmployee, index);
                printf("\nEmpleado eliminado del sistema con exito.\n\n");
                state = 1;
            }
            else
            {
                employee_delete(employeeToRemove);
                state = 2;
                printf("\nSe cancelo la baja del empleado.\n\n");
            }
        }
        else
        {
            printf("\nError: Empleado no encontrado en el sistema.\n\n");
        }
    }

    return state;
}

/** \brief Ordenar empleados
 *
* \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int option, state = 0;

    if(pArrayListEmployee != NULL)
    {
        do
        {
            employee_showMenu(&option, " 1. Ordenar por legajo (ascendente).\n 2. Ordenar por legajo (descendente).\n 3. Ordenar por nombre (ascendente).\n 4. Ordenar por nombre (descendente).\n 5. Ordenar por horas trabajadas (ascendente).\n 6. Ordenar por horas trabajadas (descendente).\n 7. Ordenar por salario (ascendente).\n 8. Ordenar por salario (descendente).\n 9. Atras.", 1, 9);
            switch(option)
            {
                case 1:
                    printf("Ordenando empleados por legajo (ascendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareById, 1) == 0)
                    {
                        printf("Empleados ordenados por legajo exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 2:
                    printf("Ordenando empleados por legajo (descendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareById, 0) == 0)
                    {
                        printf("Empleados ordenados por legajo exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 3:
                    printf("Ordenando empleados por nombre (ascendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareByName, 1) == 1)
                    {
                        printf("Empleados ordenados por nombre exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 4:
                    printf("Ordenando empleados por nombre (descendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareByName, 0) == 0)
                    {
                        printf("Empleados ordenados por nombre exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 5:
                    printf("Ordenando empleados por horas trabajadas (ascendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareByHW, 1) == 0)
                    {
                        printf("Empleados ordenados por horas trabajadas exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 6:
                    printf("Ordenando empleados por horas trabajadas (descendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareByHW, 0) == 0)
                    {
                        printf("Empleados ordenados por horas trabajadas exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 7:
                    printf("Ordenando empleados por salario (ascendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareBySalary, 1) == 0)
                    {
                        printf("Empleados ordenados por salario exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 8:
                    printf("Ordenando empleados por salario (descendente), aguarde un momento...\n\n");
                    if(ll_sort(pArrayListEmployee, employee_compareBySalary, 0) == 0)
                    {
                        printf("Empleados ordenados por salario exitosamente.\n\n");
                    }
                    else
                    {
                        printf("Error: No se pudo realizar el ordenamiento.\n\n");
                    }
                    system("pause");
                    break;
                case 9:
                    state = 1;
                    break;
            }
        }while(option != 9);
    }

    return state;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int i, state = 0;
    FILE* pFile = fopen(path, "w");
    Employee* oneEmployee;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        printf("Creando y escribiendo archivo (modo texto)...\n\n");
        Sleep(800);
        fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n"); ///Escribo las descripciones
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {   ///Recorro la lista, voy obteniendo los empleados, los voy escribiendo en el archivo
            oneEmployee = ll_get(pArrayListEmployee, i);
            fprintf(pFile, "%d,%s,%d,%d\n", oneEmployee->id, oneEmployee->name, oneEmployee->hoursWorked, oneEmployee->salary);

        }
        fclose(pFile);
        state = 1;
        printf("Archivo guardado en formato texto con exito en %s\n\n", path);
    }

    return state;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
  * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int i, state = 0;
    FILE* pFile = fopen(path, "wb");
    Employee* oneEmployee;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        printf("Creando y escribiendo archivo (modo binario)...\n\n");
        Sleep(800);
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {   ///Recorro la lista, voy obteniendo los empleados, los voy escribiendo en el archivo
            oneEmployee = ll_get(pArrayListEmployee, i);
            fwrite(oneEmployee, sizeof(Employee), 1, pFile);
        }
        fclose(pFile);
        state = 1;
        printf("Archivo guardado en formato binario con exito en %s\n\n", path);
    }

    return state;
}

