#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NAME_LEN 128
#include "LinkedList.h"
typedef struct
{
    int id;
    char nombre[NAME_LEN];
    int horasTrabajadas;
    float sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idTxt,char* name,char* workedHoursTxt,char* salaryTxt);
Employee* employee_newWithParameters(int id,char* name,int workedHours, float salary);
void employee_delete();
void employee_printHeader();
int employee_printByIndex(LinkedList* pArrayListEmployee, int index);

int employee_setId(Employee* this,int id);
int employee_setIdTxt(Employee* this, char* id);
int employee_getId(Employee* this,int* id);
int employee_getIdTxt(Employee* this, char* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int employee_getHorasTrabajadasTxt(Employee* this, char* horasTrabajadas);

int employee_setSueldo(Employee* this,float sueldo);
int employee_setSueldoTxt(Employee* this, char* sueldo);
int employee_getSueldo(Employee* this,float* sueldo);
int employee_getSueldoTxt(Employee* this, char* sueldo);

int employee_compararPorNombre(void* thisA, void* thisB);
int employee_compararPorId(void* employee1, void* employee2);

#endif // employee_H_INCLUDED
