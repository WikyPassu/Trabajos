#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int state = 0, counter = 0;
    char id[10], name[51], hoursWorked[10], salary[20]; ///Cadenas auxiliares para ir guardando los datos de un empleado

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        printf("Leyendo archivo (modo texto)...\n\n");
        Sleep(500);
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, hoursWorked, salary); ///Quito las descripciones de la primer linea
        while(!feof(pFile))
        {   ///Mientras no sea el final del archivo,
            fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, hoursWorked, salary); ///Como los voy separando y leyendo
            Employee* oneEmployee = employee_newParameters(atoi(id), name, atoi(hoursWorked), atoi(salary)); ///Creo un nuevo empleado
            employee_verifyAndAddToList(pArrayListEmployee, oneEmployee, &counter); ///Verifico que no exista en la lista y lo agrego
        }
        fclose(pFile);
        state = 1;
        printf("Empleados cargados al sistema con exito: %d\n\n", counter);
    }

    return state;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo dataB.csv (modo binario).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListEmployee LinkedList* Lista de empleados
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
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
        {   ///Mientras no sea el final del archivo
            Employee* oneEmployee = employee_new();
            fread(oneEmployee, sizeof(Employee), 1, pFile);
            if(feof(pFile)) ///Para que no haya inconsistencias
            {
                break;
            }
            employee_verifyAndAddToList(pArrayListEmployee, oneEmployee, &counter); ///Verifico que no exista en la lista y lo agrego
        }
        fclose(pFile);
        state = 1;
        printf("Empleados cargados al sistema con exito: %d\n\n", counter);
    }

    return state;
}
