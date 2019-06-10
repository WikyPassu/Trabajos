#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char name[51];
    int hoursWorked;
    int salary;
}Employee;

Employee* employee_new();
Employee* employee_newParameters(int id, char* nameStr, int hoursWorked, int salary);
void employee_delete(Employee* this);

int employee_setId(Employee* this, int id);
int employee_getId(Employee* this, int* id);

int employee_setName(Employee* this, char* name);
int employee_getName(Employee* this, char* name);

int employee_setHoursWorked(Employee* this, int hoursWorked);
int employee_getHoursWorked(Employee* this, int* hoursWorked);

int employee_setSalary(Employee* this, int salary);
int employee_getSalary(Employee* this, int* salary);

int employee_showMenu(int* pOption, char* message, int low, int high);
int employee_verifyCompliance(char* message);

int employee_printOneEmployee(Employee* this, int format);
void employee_verifyAndAddToList(LinkedList* this, Employee* oneEmployee, int* counter);
int employee_verifyIfIsInList(LinkedList* this, int id);
Employee* employee_get(LinkedList* this);

int employee_compareById(void* employeeOne, void* employeeTwo);
int employee_compareByName(void* employeeOne, void* employeeTwo);
int employee_compareByHW(void* employeeOne, void* employeeTwo);
int employee_compareBySalary(void* employeeOne, void* employeeTwo);

void employee_modifyName(Employee* oneEmployee);
void employee_modifyHW(Employee* oneEmployee);
void employee_modifySalary(Employee* oneEmployee);

#endif // employee_H_INCLUDED
