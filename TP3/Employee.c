#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Inputs.h"
#include "stringFormat.h"
#include "Utilities.h"
#include "Employee.h"
#include "Controller.h"

/** \brief Crea y muestra un menu de opciones
 *
 * \param pOption int* Direccion de memoria de la opcion
 * \param message char* Menu
 * \param low int Opcion minima
 * \param high int Opcion maxima
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
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
        getValidInt(pOption, "una opcion", low, high, 0); ///Pido un entero valido con rango.
        printf("\n");
    }
    return state;
}

/** \brief Reserva espacio en memoria para un empleado
 *
 * \return Employee* Devuelve un puntero a ese empleado
 *
 */
Employee* employee_new()
{
    Employee* oneEmployee;
    oneEmployee = (Employee*) malloc(sizeof(Employee));
    return oneEmployee;
}

/** \brief Carga datos a un empleado
 *
 * \param id int Legajo
 * \param nameStr char* Nombre
 * \param hoursWorked int Horas trabajadas
 * \param salary int Salario
 * \return Employee* Devuelve un puntero al empleado
 *
 */
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

    return oneEmployee;
}

/** \brief Hace free de un empleado
 *
 * \param this Employee* Direccion de un empleado
 * \return void
 *
 */
void employee_delete(Employee* this)
{
    if(this != NULL)
    {
        free(this);
        this = NULL;
    }
}

/** \brief Setea el legajo a un empleado
 *
 * \param this Employee* Direccion de un empleado
 * \param id int Legajo
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_setId(Employee* this, int id)
{
    int valid = 0;

    if(this != NULL)
    {
        this->id = id;
        valid = 1;
    }

    return valid;
}

/** \brief Obtiene el legajo de un empleado
 *
 * \param this Employee* Direccion de un empleado
 * \param id int* Direccion de la variable donde se guardara el legajo
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_getId(Employee* this, int* id)
{
    int state = 0;

    if(this != NULL)
    {
        *id = this->id;
        state = 1;
    }

    return state;
}

/** \brief Setea el nombre a un empleado
 *
 * \param this Employee* Direccion de un empleado
 * \param name char* Direccion del nombre
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_setName(Employee* this, char* name)
{
    int valid = 0;

    if(this != NULL)
    {
        strcpy(this->name, name);
        valid = 1;
    }

    return valid;
}

/** \brief Obtiene el nombre de un empleado
 *
 * \param this Employee* La direccion de un empleado
 * \param name char* La direccion de la bvariable donde se guardara el nombre
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_getName(Employee* this, char* name)
{
    int state = 0;

    if(this != NULL)
    {
        strcpy(name, this->name);
        state = 1;
    }

    return state;
}

/** \brief Setea las horas trabajadas a un empleado
 *
 * \param this Employee* La direccion de un empleado
 * \param hoursWorked int Las horas trabajadas
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_setHoursWorked(Employee* this, int hoursWorked)
{
    int valid = 0;

    if(this != NULL)
    {
        this->hoursWorked = hoursWorked;
        valid = 1;
    }

    return valid;
}

/** \brief Obtiene las horas trabajadas de un empleado
 *
 * \param this Employee* La direccion de un empleado
 * \param hoursWorked int* La direccion donde se guardaran las horas trabajadas
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_getHoursWorked(Employee* this, int* hoursWorked)
{
    int state = 0;

    if(this != NULL)
    {
        *hoursWorked = this->hoursWorked;
        state = 1;
    }

    return state;
}

/** \brief Setea el salario a un empleado
 *
 * \param this Employee* La direccion del empleado
 * \param salary int El salario
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_setSalary(Employee* this, int salary)
{
    int valid = 0;

    if(this != NULL)
    {
        this->salary = salary;
        valid = 1;
    }

    return valid;
}

/** \brief Obtiene el salario de un empleado
 *
 * \param this Employee* La direccion del empleado
 * \param salary int* La direccion donde se guardara el salario
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_getSalary(Employee* this, int* salary)
{
    int state = 0;

    if(this != NULL)
    {
        *salary = this->salary;
        state = 1;
    }

    return state;
}

/** \brief Verifica si el usuario esta satisfecho con lo que hizo
 *
 * \param message char* Pregunta
 * \return int Devuelve un estado: 0 si esta insatisfecho, 1 si esta satisfecho
 *
 */
int employee_verifyCompliance(char* message)
{
    int isSatisfied = 0;
    char answer; ///Repuesta del usuario.

    getChar(&answer, message); ///Le pido al usuario que ingrese una respuesta.
    if(answer == 's' || answer == 'S')
    {   ///Si responde 's' o 'S', esta satisfecho.
        isSatisfied = 1;
    }

    return isSatisfied;
}

/** \brief Imprime un empleado en pantalla
 *
 * \param this Employee* Direccion de un empleado
 * \param format int El formato de muestra: 0 para tabla, 1 para seleccion
 * \return int Devuelve un estado: 0 si hubo error, 1 si esta todo bien
 *
 */
int employee_printOneEmployee(Employee* this, int format)
{
    int state = 0, id, hoursWorked, salary;
    char name[51];

    if(this != NULL)
    {
        employee_getId(this, &id);
        employee_getName(this, name);
        employee_getHoursWorked(this, &hoursWorked);
        employee_getSalary(this, &salary);

        if(format == 1)
        {
            printf("\nID: %d | Nombre: %s | Horas trabajadas: %d | Salario: $%d\n\n", id, name, hoursWorked, salary);
        }
        else
        {
            printf("%4d %15s %6d %8d\n", id, name, hoursWorked, salary);
        }

        state = 1;
    }

    return state;
}

/** \brief Verifica si existe un empleado en la lista y lo agrega a la misma si no es asi
 *
 * \param this LinkedList* La lista
 * \param oneEmployee Employee* Direccion de un empleado
 * \param counter int* Direccion a un contador de empleados
 * \return void
 *
 */
void employee_verifyAndAddToList(LinkedList* this, Employee* oneEmployee, int* counter)
{
    Employee* auxEmployee;
    int i, flag = 0;
    for(i=0; i<ll_len(this); i++)
    {   ///Recorro lista, obtengo empleado, verifico, agrego o no a la lista
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

/** \brief Verifica si existe un empleado en la lista usando su id y devuelve el index en la lista si lo encuentra
 *
 * \param this LinkedList* La lista
 * \param id int El legajo
 * \return int Devuelve -1 si no existe el empleado, el index en la lista si existe
 *
 */
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

/** \brief Compara por legajos
 *
 * \param employeeOne void* Direccion de un empleado
 * \param employeeTwo void* Direccion de otro empleado
 * \return int Devuelve 1 o -1 de acuerdo al resultado de la comparacion
 *
 */
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

/** \brief Compara por nombres
 *
 * \param employeeOne void* Direccion de un empleado
 * \param employeeTwo void* Direccion de otro empleado
 * \return int Devuelve -1, 0 o 1 de acuerdo al resultado de la comparacion
 *
 */
int employee_compareByName(void* employeeOne, void* employeeTwo)
{
    Employee* e1 = (Employee*)employeeOne;
    Employee* e2 = (Employee*)employeeTwo;
    return strcmp(e1->name, e2->name);
}

/** \brief Compara por horas trabajadas
 *
 * \param employeeOne void* Direccion de un empleado
 * \param employeeTwo void* Direccion de otro empleado
 * \return int Devuelve -1, 0 o 1 de acuerdo al resultado de la comparacion
 *
 */
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

/** \brief Compara por salario
 *
 * \param employeeOne void* Direccion de un empleado
 * \param employeeTwo void* Direccion de otro empleado
 * \return int Devuelve -1, 0 o 1 de acuerdo al resultado de la comparacion
 *
 */
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

/** \brief Obtiene y selecciona a un empleado de la lista como objetivo para realizar alguna accion
 *
 * \param this LinkedList* La lista
 * \return Employee* Devuelve NULL si no se encontro al empleado, caso contrario la direccion del empleado
 *
 */
Employee* employee_get(LinkedList* this)
{
    Employee* rEmployee = NULL;
    int idToFind, index;

    controller_ListEmployee(this);
    getValidInt(&idToFind, "ID del empleado a modificar datos", 1, 5000, 0);

    index = employee_verifyIfIsInList(this, idToFind); ///Verifico si existe dicho empleado
    if(index != -1)
    {
        rEmployee = ll_get(this, index);
        employee_printOneEmployee(rEmployee, 1);
        if(employee_verifyCompliance("'s' si desea seleccionar al empleado para realizar modificaciones"))
        {
            printf("\nSe ha seleccionado al empleado como objetivo de edicion.\n\n");
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

/** \brief Modifica el nombre de un empleado
 *
 * \param oneEmployee Employee* La direccion de un empleado
 * \return void
 *
 */
void employee_modifyName(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        char newName[51];

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee, 1);

        getValidString("nuevo nombre", newName, 51, 0);
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

/** \brief Modifica las horas trabajadas de un empleado
 *
 * \param oneEmployee Employee* La direccion de un empleado
 * \return void
 *
 */
void employee_modifyHW(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        int newHW;

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee, 1);

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

/** \brief Modifica el salario de un empleado
 *
 * \param oneEmployee Employee* La direccion de un empleado
 * \return void
 *
 */
void employee_modifySalary(Employee* oneEmployee)
{
    if(oneEmployee != NULL)
    {
        int newSalary;

        printf("Empleado seleccionado actualmente:\n");
        employee_printOneEmployee(oneEmployee, 1);

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

/** \brief Carga el ultimo id desde un archivo binario
 *
 * \param lastId int* La direccion donde se guardara el dato
 * \return void
 *
 */
void employee_loadLastId(int* lastId)
{
    FILE* pFile = NULL;

    pFile = fopen("lastId.csv", "rb");

    if(pFile != NULL)
    {
        fread(lastId, sizeof(int), 1, pFile);
        fclose(pFile);
    }
}

/** \brief Carga el ultimo id desde un archivo binario
 *
 * \param lastId int* La direccion donde se guardara el dato
 * \return void
 *
 */
void employee_saveLastId(int* lastId)
{
    FILE* pFile = NULL;

    pFile = fopen("lastId.csv", "wb");

    if(pFile != NULL)
    {
        fwrite(lastId, sizeof(int), 1, pFile);
        fclose(pFile);
    }
}
