#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "validations.h"

/*
 * \brief Request memory for a new employee
 * \param void
 * \return int Return returns a pointer of type Employee
 */
Employee* employee_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}
/*
 * \brief Request memory for a new employee and set the fields with what it receives as a parameter. Receives all parameters as char[]
 * \param char* idTxt Id to be set
 * \param char* name Name to be set
 * \param char* workedHoursTxt Worked hours to be set
 * \param char* salaryTxt Salary to be set
 * \return int Return returns a pointer of type Employee with all the fields already set
 */
Employee* employee_newParametros(char* idTxt,char* name,char* workedHoursTxt,char* salaryTxt)
{
	Employee* pEmployee =  employee_new();
	if (pEmployee != NULL && idTxt != NULL && name != NULL && workedHoursTxt != NULL && salaryTxt != NULL)
	{
		if ( !employee_setNombre(pEmployee, name)  &&
			 !employee_setHorasTrabajadasTxt(pEmployee, workedHoursTxt) &&
			 !employee_setSueldoTxt(pEmployee, salaryTxt) &&
			 !employee_setIdTxt(pEmployee, idTxt))
		{
			return pEmployee;
		}
	}
	employee_delete(pEmployee);
	return NULL;
}
/* \brief add in a existing list of employees the values received as parameters
 * \param int id, id to be set in the employee's "id" field
 * \param char* name, name to be set in the employee's "nombre" field
 * \param int workedHours, hours to be set in the employee's "horasTrabajadas" field
 * \param float salary, salary to be set in the employee's "sueldo" field
 * \returns memory address of employee with loaded data or NULL if error
 */
Employee* employee_newWithParameters(int id,char* name,int workedHours, float salary)
{
	Employee* pEmployee = employee_new();
	if(pEmployee!=NULL)
	{
		if( employee_setId(pEmployee, id)==0 &&
		    employee_setNombre(pEmployee, name)==0 &&
			employee_setHorasTrabajadas(pEmployee, workedHours)==0 &&
			employee_setSueldo(pEmployee, salary)==0)
		{
			return pEmployee;
		}
	}
	employee_delete(pEmployee);
	return NULL;
}
/*
 * \brief frees the memory space reserved for an employee
 * \param Employee* this Pointer to an Employee
 * \return void
 */
void employee_delete(Employee* this)
{
	free(this);
}
/** \brief compares between two names
 *  \param void* thisA: void pointer to be cast to first employee
 *  \param void* thisB: void pointer to be cast to second employee
 *  \return [1] if first employee has a "larger" name than the second one. [-1] if the second employee has a "larger" name than the first, [0] if even
 */
int employee_compararPorNombre(void* thisA, void* thisB) // La funcion que se le pasa al sort siempre va a recibir dos elementos
{
	int result = -2; //error
	int compResult;
	char bufferNameA[NAME_LEN];
	char bufferNameB[NAME_LEN];
	if( thisA!=NULL && thisB!=NULL &&
		!employee_getNombre((Employee*) thisA, bufferNameA) &&
		!employee_getNombre((Employee*) thisB, bufferNameB))
	{
		compResult = strcmp(bufferNameA,bufferNameB);
		if(compResult>0)
		{
			result = 1;
		}
		else if (compResult<0)
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
	}
	return result;
}

void employee_printHeader()
{
	printf("\n****************************** EMPLEADOS *********************************\n");
	printf("\n--------------------------------------------------------------------------\n");
	printf("    ID    |            NOMBRE            |     HORAS     |     SUELDO    |");
}
/*\brief prints the data of a certain employee
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \param int index, position of the linkedlist where the pointer to the searched employee is located
 * \return [-1] if error / [0] if ok
 */
int employee_printByIndex(LinkedList* pArrayListEmployee, int index)
{
	int result = -1;
	Employee* pEmployee;
	Employee bufferEmployee;

	if(pArrayListEmployee!=NULL && index>=0)
	{
		pEmployee = ll_get(pArrayListEmployee, index);
		if( !employee_getNombre(pEmployee, bufferEmployee.nombre) &&
			!employee_getHorasTrabajadas(pEmployee, &bufferEmployee.horasTrabajadas) &&
			!employee_getId(pEmployee, &bufferEmployee.id) &&
			!employee_getSueldo(pEmployee, &bufferEmployee.sueldo))
		{
			printf( "\n--------------------------------------------------------------------------\n"
					"%-10d|%-30s|%-15d|%-15.2f|\n"
					"--------------------------------------------------------------------------\n",bufferEmployee.id, bufferEmployee.nombre, bufferEmployee.horasTrabajadas,bufferEmployee.sueldo);
			result = 0;
		}
	}
	return result;
}
/** \brief compares between two id's
 *  \param void* thisA: void pointer to be cast to first employee
 *  \param void* thisB: void pointer to be cast to second employee
 *  \return [1] if first employee has a higher ID than the second one. [-1] if the second employee has a higher ID than the first, [0] if even
 */
int employee_compararPorId(void* employee1, void* employee2)
{
	int retornar;
	Employee* bufferEmp1 = employee1;
	Employee* bufferEmp2 = employee2;
	int bufferId1;
	int bufferId2;
	if(employee1!=NULL && employee2!=NULL)
	{
		employee_getId(bufferEmp1, &bufferId1);
		employee_getId(bufferEmp2, &bufferId2);
		if(bufferId1>bufferId2)
		{
			retornar=1;
		}
		else
		{
			if(bufferId1<bufferId2)
			{
				retornar=-1;
			}
			else
			{
				retornar=0;
			}
		}
	}
	return retornar;
}
/***********SETTERS Y GETTERS**************/

/* \brief set id of employee as text
 * \param Employee* this: pointer to employee
 * \param int* id: id by reference as text to be set to that employee
 * \return [-1] if error / [0] if ok
 */
int employee_setIdTxt(Employee* this, char* id)
{
    int result = -1;
    char bufferId[500];
    if (this != NULL && id!=NULL && val_isValidNumber(id))
    {
        strncpy(bufferId,id,500);
        this->id = atoi(bufferId);
        result = 0;
    }
    return result;
}
/*
 * \brief Gets the id of the employee (treated as text)
 * \param Employee* this, Pointer to employee
 * \param char* id, Pointer to the space where the obtained id will be saved
 * \return int Return [-1] if ERROR or [0] if OK
 */
int employee_getIdTxt(Employee* this, char* id)
{
    int result = -1;
    if (this != NULL)
    {
        sprintf(id, "%d", this->id);
        result = 0;
    }
    return result;
}
/* \brief set id of employee
 * \param Employee* this: pointer to employee
 * \param int* id: id by reference to be set to that employee
 * \return [-1] if error / [0] if ok
 */
int employee_setId(Employee* this, int id)
{
	int result = -1;
	if (this != NULL && id >= 0)
	{
		this->id = id;
		result = 0;
	}
	return result;
}
/* \brief get id of employee
 * \param Employee* this: pointer to employee
 * \param int* id: id by reference of employee
 * \return [-1] if error / [0] if ok
 */
int employee_getId(Employee* this, int* id)
{
    int result = -1;
    if (this != NULL && id != NULL)
    {
        *id = this->id;
        result = 0;
    }
    return result;
}
/*
 * \brief Load the name in the employee field and validate that the data is correct
 * \param Employee* this: pointer to employee
 * \param char* nombre: pointer of the name to be set to an employee
 * \return [-1] if error / [0] if ok
 */
int employee_setNombre(Employee *this, char* nombre)
{
	int result = -1;
	if (this != NULL && nombre != NULL && val_isValidString(nombre, NAME_LEN)==1)
	{
		strncpy(this->nombre, nombre, NAME_LEN);
		result = 0;
	}
	return result;
}

/* \brief get name of one employee
 * \param Employee* this: pointer to employee
 * \param char* nombre: get pointer of the place in memory to save name of employee
 * \return [-1] if error / [0] if ok
 */
int employee_getNombre(Employee* this, char* nombre)
{
    int result = -1;
    if (this != NULL && nombre != NULL)
    {
        strncpy(nombre, this->nombre, NAME_LEN);
        result = 0;
    }
    return result;
}

/* \brief set worked hours of an employee
 * \param Employee* this: pointer to employee
 * \param int horasTrabajadas: set worked hours to be asign an employee
 * \return [-1] if error / [0] if ok
 */
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int result = -1;
	if(this != NULL && horasTrabajadas > 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		result = 0;
	}
	return result;
}

/* \brief get worked hours by an employee
 * \param Employee* this: pointer to employee
 * \param int* horasTrabajadas: get by reference worked hours of employee
 * \return [-1] if error / [0] if ok
 */
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
    int result = -1;
    if (this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        result = 0;
    }
    return result;
}

/*
 * \brief Load the hours worked in the employee's field (treated as text) and validate that the data is correct
 * \param Employee* this: pointer to employee
 * \param int horasTrabajadas: set worked hours to be asign an employee
 * \return [-1] if error / [0] if ok
 */
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
    int result = -1;
    char bufferHours[500];
    if (this != NULL && horasTrabajadas>0 && val_isValidNumber(horasTrabajadas))
    {
    	strncpy(bufferHours,horasTrabajadas,500);
        this->horasTrabajadas = atoi(horasTrabajadas);
        result = 0;
    }
    return result;
}

/*
 * \brief Gets the worked hours of the employee (treated as text)
 * \param Employee* this, Pointer to employee
 * \param char* horasTrabajadas, Pointer to the space where the obtained id will be saved
 * \return int Return [-1] if ERROR or [0] if OK
 */
int employee_getHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
    int result = -1;
    if (this != NULL && horasTrabajadas != NULL)
    {
        sprintf(horasTrabajadas, "%d", this->horasTrabajadas);
        result = 0;
    }
    return result;
}

/*
 * \brief Load salary in employee's field
 * \param Employee* this: pointer to employee
 * \param float sueldo: get salary to be set to an employee
 * \return [-1] if error / [0] if ok
 */
int employee_setSueldo(Employee* this, float sueldo)
{
	int result = -1;
	if(this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		result = 0;
	}
	return result;
}
/*
 * \brief Get the employee's salary
 * \param Employee* this: pointer to employee
 * \param float* sueldo:  get by reference salary of employee
 * \return [-1] if error / [0] if ok
 */
int employee_getSueldo(Employee* this, float* sueldo)
{
    int result = -1;
    if (this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        result = 0;
    }
    return result;
}

/*
 * \brief Load the salary in the employee field (treated as text) and validate that the data is correct
 * \param Employee* this: pointer to employee
 * \param float sueldo: get salary as text to be set to an employee
 * \return [-1] if error / [0] if ok
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
    int result = -1;
    char bufferSalary [500];
    if (this != NULL && val_isValidFloat(sueldo))
    {
        strncpy(bufferSalary,sueldo,500);
        this->sueldo = atof(bufferSalary);
        result = 0;
    }
    return result;
}
/*
 * \brief Get the salary of the employee (treated as text)
 * \param Employee* this, Pointer to employee
 * \param char* sueldo , Pointer to the memory space where the obtained salary will be saved
 * \return [-1] if error / [0] if ok
 */
int employee_getSueldoTxt(Employee* this, char* sueldo)
{
    int result = -1;
    if (this != NULL && sueldo != NULL)
    {
        sprintf(sueldo, "%.2f", this->sueldo);
        result = 0;
    }
    return result;
}
