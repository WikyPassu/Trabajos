#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Inputs.h"
#include "stringFormat.h"
#include "Utilities.h"
#include "Employee.h"
#include "Controller.h"

int employee_showMenu(int* pOption, char* message, int low, int high)
{
    int state = 0;
    if(pOption != NULL)
    {
        state = 1;
        system("cls");
        printf("--------------------------------------------------------------\n");
        printf("%s", message);
        printf("\n--------------------------------------------------------------\n\n");
        getValidInt(pOption, "una opcion", low, high, 0); //Pido un entero valido con rango.
        printf("\n");
    }
    return state;
}

Employee* employee_new()
{
    Employee* oneEmployee;
    oneEmployee = (Employee*) malloc(sizeof(Employee));
    return oneEmployee;
}

Employee* employee_newParameters(int id, char* nameStr, int hoursWorked, int salary)
{
    Employee* oneEmployee;
    oneEmployee = employee_new();
    if(oneEmployee != NULL)
    {
        employee_setId(oneEmployee, id);
        employee_setName(oneEmployee, nameStr);
        employee_setHoursWorked(oneEmployee, hoursWorked);
        employee_setSalary(oneEmployee, salary);
    }
    else
    {
        printf("\nError.\n");
    }
    return oneEmployee;
}

void employee_delete(Employee* this)
{
    if(this != NULL)
    {
        free(this);
        this = NULL;
    }
}

int employee_setId(Employee* this, int id)
{
    int valid = 0;
    if(this != NULL)
    {
        this->id = id;
        valid = 1;
    }
    else
    {
        printf("\nError.\n");
    }
    return valid;
}

int employee_getId(Employee* this, int* id)
{
    int state = 0;
    if(this != NULL)
    {
        *id = this->id;
        state = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return state;
}

int employee_setName(Employee* this, char* name)
{
    int valid = 0;
    if(this != NULL)
    {
        strcpy(this->name, name);
        valid = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return valid;
}

int employee_getName(Employee* this, char* name)
{
    int state = 0;
    if(this != NULL)
    {
        strcpy(name, this->name);
        state = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return state;
}

int employee_setHoursWorked(Employee* this, int hoursWorked)
{
    int valid = 0;
    if(this != NULL)
    {
        this->hoursWorked = hoursWorked;
        valid = 1;
    }
    else
    {
        printf("\nError.\n");
    }
    return valid;
}

int employee_getHoursWorked(Employee* this, int* hoursWorked)
{
    int state = 0;
    if(this != NULL)
    {
        *hoursWorked = this->hoursWorked;
        state = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return state;
}

int employee_setSalary(Employee* this, int salary)
{
    int valid = 0;
    if(this != NULL)
    {
        this->salary = salary;
        valid = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return valid;
}

int employee_getSalary(Employee* this, int* salary)
{
    int state = 0;
    if(this != NULL)
    {
        *salary = this->salary;
        state = 1;
    }
    else
    {
        printf("Error.\n");
    }
    return state;
}

int employee_verifyCompliance(char* message)
{
    int isSatisfied = 0;
    char answer; //Repuesta del usuario.
    getChar(&answer, message); //Le pido al usuario que ingrese una respuesta.
    if(answer == 's' || answer == 'S')
    {   //Si responde 's' o 'S', esta satisfecho.
        isSatisfied = 1;
    }
    return isSatisfied;
}

int employee_printOneEmployee(Employee* this)
{
    int state = 0, id, hoursWorked, salary;
    char name[128];

    if(this != NULL)
    {
        employee_getId(this, &id);
        employee_getName(this, name);
        employee_getHoursWorked(this, &hoursWorked);
        employee_getSalary(this, &salary);
        printf("\nID: %d | Nombre: %s | Horas trabajadas: %d | Salario: $%d\n\n", id, name, hoursWorked, salary);
        state = 1;
    }
    else
    {
        printf("\nError.\n");
    }

    return state;
}

void employee_verifyAndAddToList(LinkedList* this, Employee* oneEmployee, int* counter)
{
    Employee* auxEmployee;
    int i, flag = 0;
    for(i=0; i<ll_len(this); i++)
    {
        auxEmployee = ll_get(this, i);
        if(auxEmployee->id == oneEmployee->id)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        ll_add(this, oneEmployee);
        *counter = *counter + 1;
    }
}

int employee_verifyIfIsInList(LinkedList* this, int id)
{
    Employee* auxEmployee;
    int i, index = -1;
    for(i=0; i<ll_len(this); i++)
    {
        auxEmployee = ll_get(this, i);
        if(auxEmployee->id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

int employee_compareById(void* employeeOne, void* employeeTwo)
{
    int flag = -1;
    Employee* e1 = (Employee*)employeeOne;
    Employee* e2 = (Employee*)employeeTwo;

    if(e1->id > e2->id)
    {
        flag = 1;
    }
    return flag;
}

int employee_compareByName(void* employeeOne, void* employeeTwo)
{
    Employee* e1 = (Employee*)employeeOne;
    Employee* e2 = (Employee*)employeeTwo;
    return strcmp(e1->name, e2->name);
}

int employee_compareByHW(void* employeeOne, void* employeeTwo)
{
    int flag = -1;
    Employee* e1 = (Employee*)employeeOne;
    Employee* e2 = (Employee*)employeeTwo;

    if(e1->hoursWorked > e2->hoursWorked)
    {
        flag = 1;
    }
    else if(e1->hoursWorked == e2->hoursWorked)
    {
        flag = 0;
    }

    return flag;
}

int employee_compareBySalary(void* employeeOne, void* employeeTwo)
{
    int flag = -1;
    Employee* e1 = (Employee*)employeeOne;
    Employee* e2 = (Employee*)employeeTwo;

    if(e1->salary > e2->salary)
    {
        flag = 1;
    }
    else if(e1->salary == e2->salary)
    {
        flag = 0;
    }

    return flag;
}

Employee* employee_get(LinkedList* this)
{
    Employee* rEmployee = NULL;
    int idToFind, index;

    controller_ListEmployee(this);
    getValidInt(&idToFind, "ID del empleado a modificar datos", 1, 5000, 0);

    index = employee_verifyIfIsInList(this, idToFind);
    if(index != -1)
    {
        rEmployee = ll_get(this, index);
        employee_printOneEmployee(rEmployee);
        if(employee_verifyCompliance("'s' si desea seleccionar al empleado para realizar modificaciones"))
        {
            printf("\nSe ha seleccionado como objetivo de edicion al empleado.\n\n");
        }
        else
        {
            rEmployee = NULL;
            printf("\nSe cancelo la seleccion del empleado para edicion.\n\n");
        }
    }
    else
    {
        printf("\nError: Empleado no encontrado en el sistema.\n\n");
    }
    return rEmployee;
}

void employee_modifyName(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        char newName[128];

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee);

        getValidString("nuevo nombre", newName, 128, 0);
        printf("\n");
        if(employee_verifyCompliance("'s' si desea aplicar la modificacion"))
        {
            employee_setName(oneEmployee, newName);
            printf("\nSe modifico el nombre del empleado con exito.\n\n");
        }
        else
        {
            printf("\nSe cancelo la modificacion.\n\n");
        }
    }
    else
    {
        printf("Error: Primero debe seleccionar un empleado.\n\n");
    }
}

void employee_modifyHW(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        int newHW;

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee);

        getValidInt(&newHW, "nueva cantidad de horas trabajadas", 1, 400, 0);
        printf("\n");
        if(employee_verifyCompliance("'s' si desea aplicar la modificacion"))
        {
            employee_setHoursWorked(oneEmployee, newHW);
            printf("\nSe modifico la cantidad de horas trabajadas del empleado con exito.\n\n");
        }
        else
        {
            printf("\nSe cancelo la modificacion.\n\n");
        }
    }
    else
    {
        printf("Error: Primero debe seleccionar un empleado.\n\n");
    }
}

void employee_modifySalary(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        int newSalary;

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee);

        getValidInt(&newSalary, "nuevo salario", 1, 200000, 0);
        printf("\n");
        if(employee_verifyCompliance("'s' si desea aplicar la modificacion"))
        {
            employee_setSalary(oneEmployee, newSalary);
            printf("\nSe modifico el salario del empleado con exito.\n\n");
        }
        else
        {
            printf("\nSe cancelo la modificacion.\n\n");
        }
    }
    else
    {
        printf("Error: Primero debe seleccionar un empleado.\n\n");
    }
}
