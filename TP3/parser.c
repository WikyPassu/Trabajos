#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int state = 0, counter = 0;
    char id[10], name[51], hoursWorked[10], salary[20];

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        printf("Leyendo archivo (modo texto)...\n\n");
        Sleep(500);
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, hoursWorked, salary);
        while(!feof(pFile))
        {
            fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, hoursWorked, salary);
            Employee* oneEmployee = employee_newParameters(atoi(id), name, atoi(hoursWorked), atoi(salary));
            employee_verifyAndAddToList(pArrayListEmployee, oneEmployee, &counter);
        }
        fclose(pFile);
        state = 1;
        printf("Empleados cargados al sistema con exito: %d\n\n", counter);
    }

    return state;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int state = 0, counter = 0;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        printf("Leyendo archivo (modo binario)...\n\n");
        Sleep(500);

        while(!feof(pFile))
        {
            Employee* oneEmployee = employee_new();
            fread(oneEmployee, sizeof(Employee), 1, pFile);
            if(feof(pFile))
            {
                break;
            }
            employee_verifyAndAddToList(pArrayListEmployee, oneEmployee, &counter);
        }
        fclose(pFile);
        state = 1;
        printf("Empleados cargados al sistema con exito: %d\n\n", counter);
    }

    return state;
}
