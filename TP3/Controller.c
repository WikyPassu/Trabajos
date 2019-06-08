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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
    else
    {
        printf("\nError.\n");
    }

    return state;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
    else
    {
        printf("\nError.\n");
    }

    return state;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int state = 0, id, hoursWorked, salary;
    char name[128];

    if(pArrayListEmployee != NULL)
    {
        id = getRandomNumber(1001, 5000, 1);
        getValidString("nombre", name, 128, 0);
        getValidInt(&hoursWorked, "horas trabajadas", 1, 400, 0);
        getValidInt(&salary, "salario", 1, 200000, 0);

        Employee* newEmployee = employee_newParameters(id, name, hoursWorked, salary);
        employee_printOneEmployee(newEmployee);

        if(employee_verifyCompliance("'s' si desea dar de alta al empleado"))
        {
            ll_add(pArrayListEmployee, newEmployee);
            state = 1;
            printf("\nSe dio de alta al empleado exitosamente.\n\n");
        }
        else
        {
            employee_delete(newEmployee);
            printf("\nSe cancelo la carga del empleado al sistema.\n\n");
        }
    }
    else
    {
        printf("\nError.\n");
    }

    return state;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
                    currentEmployee = employee_get(pArrayListEmployee);
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
                    break;
            }
        }while(option != 5);
    }
    else
    {
        printf("\nError.\n\n");
    }

    return state;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    Employee* oneEmployee;
    int i, state = 0, auxId, auxHoursWorked, auxSalary;
    char auxName[128];
    if(pArrayListEmployee != NULL)
    {
        printf("Mostrando lista de empleados...\n\n");
        Sleep(800);
        printf("--------------------------------------\n");
        printf("%3s %16s %6s %9s", "ID", "Nombre", "Hs.", "Salario");
        printf("\n--------------------------------------\n");
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            /*if(i%250 == 0)
            {
                system("pause");
            }*/
            oneEmployee = ll_get(pArrayListEmployee, i);
            employee_getId(oneEmployee, &auxId);
            employee_getName(oneEmployee, auxName);
            employee_getHoursWorked(oneEmployee, &auxHoursWorked);
            employee_getSalary(oneEmployee, &auxSalary);
            printf("%4d %15s %6d %8d\n", auxId, auxName, auxHoursWorked, auxSalary);
        }
        printf("--------------------------------------\n\n");
        state = 1;
    }
    else
    {
        printf("\nError.\n");
    }
    return state;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int state = 0, toRemove, index;
    Employee* employeeToRemove;

    if(pArrayListEmployee != NULL)
    {
        controller_ListEmployee(pArrayListEmployee);
        getValidInt(&toRemove, "ID del empleado a eliminar del sistema", 1, 5000, 0);

        index = employee_verifyIfIsInList(pArrayListEmployee, toRemove);

        if(index != -1)
        {
            employeeToRemove = ll_get(pArrayListEmployee, index);
            employee_printOneEmployee(employeeToRemove);

            if(employee_verifyCompliance("'s' si desea eliminar al empleado del sistema"))
            {
                ll_remove(pArrayListEmployee, index);
                printf("\nEmpleado eliminado del sistema con exito.\n\n");
                state = 1;
            }
            else
            {
                employee_delete(employeeToRemove);
                printf("\nSe cancelo la baja del empleado.\n\n");
            }
        }
        else
        {
            printf("\nError: Empleado no encontrado en el sistema.\n\n");
        }
    }
    else
    {
        printf("\nError.\n");
    }

    return state;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int option, state = 0;

    if(pArrayListEmployee != NULL)
    {
        do
        {
            employee_showMenu(&option, " 1. Ordenar por legajo.\n 2. Ordenar por nombre.\n 3. Ordenar por horas trabajadas.\n 4. Ordenar por salario.\n 5. Atras.", 1, 5);
            switch(option)
            {
                case 1:
                    printf("Ordenando empleados por ID, aguarde un momento...\n\n");
                    ll_sort(pArrayListEmployee, employee_compareById, 1);
                    printf("Empleados ordenados por ID exitosamente.\n\n");
                    system("pause");
                    break;
                case 2:
                    printf("Ordenando empleados por nombre, aguarde un momento...\n\n");
                    ll_sort(pArrayListEmployee, employee_compareByName, 1);
                    printf("Empleados ordenados por nombre exitosamente.\n\n");
                    system("pause");
                    break;
                case 3:
                    printf("Ordenando empleados por horas trabajadas, aguarde un momento...\n\n");
                    ll_sort(pArrayListEmployee, employee_compareByHW, 1);
                    printf("Empleados ordenados por horas trabajadas exitosamente.\n\n");
                    system("pause");
                    break;
                case 4:
                    printf("Ordenando empleados por salario, aguarde un momento...\n\n");
                    ll_sort(pArrayListEmployee, employee_compareBySalary, 1);
                    printf("Empleados ordenados por salario exitosamente.\n\n");
                    system("pause");
                    break;
                case 5:
                    break;
            }
        }while(option != 5);
    }
    else
    {
        printf("\nError.\n\n");
    }

    return state;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int i, state = 1;
    FILE* pFile = fopen(path, "w");
    Employee* oneEmployee;

    if(pFile != NULL)
    {
        printf("Creando y escribiendo archivo (modo texto)...\n\n");
        Sleep(800);
        fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            oneEmployee = ll_get(pArrayListEmployee, i);
            fprintf(pFile, "%d,%s,%d,%d\n", oneEmployee->id, oneEmployee->name, oneEmployee->hoursWorked, oneEmployee->salary);

        }
        fclose(pFile);
        state = 1;
        printf("Archivo guardado en formato texto con exito en %s\n\n", path);
    }
    else
    {
        printf("\nError.\n\n");
    }

    return state;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int i, state = 0;
    FILE* pFile = fopen(path, "wb");
    Employee* oneEmployee;

    if(pFile != NULL)
    {
        printf("Creando y escribiendo archivo (modo binario)...\n\n");
        Sleep(800);
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            oneEmployee = ll_get(pArrayListEmployee, i);
            fwrite(oneEmployee, sizeof(Employee), 1, pFile);
        }
        fclose(pFile);
        state = 1;
        printf("Archivo guardado en formato binario con exito en %s\n\n", path);
    }
    else
    {
        printf("\nError.\n\n");
    }

    return state;
}

