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
 * \brief Request memory for a new employee and set the fields with what it receives as a parameter
 * \param char* idTxt Id to be set
 * \param char* name Name to be set
 * \param char* workedHoursTxt Worked hours to be set
 * \param char* salaryTxt Salary to be set
 * \return int Return returns a pointer of type Employee with all the fields already set
 */
Employee* employee_newParametros(char* idTxt,char* name,char* workedHoursTxt,char* salaryTxt)
{
	Employee* pEmployee = NULL;
	if (idTxt != NULL && name != NULL && workedHoursTxt != NULL && salaryTxt != NULL)
	{
		pEmployee = employee_new();
		if ( pEmployee != NULL && !employee_setNombre(pEmployee, name)  &&
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
/** \brief Dar de alta un empleado recibiendo los parametros tal y como son
 * \param char* idStr: Recibo el id en forma de entero
 * \param char* nombreStr: Recibo el nombre
 * \param char* horasTrabajadasStr: Recibo las horas trabajadas en forma de entero
 * \param char* sueldo: Recibo el sueldo en forma de flotante
 * \return la direccion de memoria del empleado con todos sus datos cargados o NULL en caso de que algo haya salido mal
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
int employee_compararPorNombre(void* thisA, void* thisB) // La funcion que se le pasa al sort siempre va a recibir dos elementos
{
	int result = -2; //error
	Employee* pEmpleadoA = (Employee*) thisA;
	int r;
	char bufferNombreA[NAME_LEN];
	char bufferNombreB[NAME_LEN];
	if( thisA!=NULL && thisB!=NULL &&
		!employee_getNombre(pEmpleadoA, bufferNombreA) &&
		!employee_getNombre((Employee*) thisB, bufferNombreB))
	{
		r = strcmp(bufferNombreA,bufferNombreB);
		if(r>0)
		{
			result = 1;
		}
		else if (r<0)
		{
			result = -1;
		}
		else
		{
			result = 0;
			//si quisiera agregar criterios de ordenamiento los tendria que escribir aca
		}
	}
	return result;
}

void employee_printHeader()
{
	printf("\n***************************** EMPLEADOS *********************************\n");
	printf("\n-------------------------------------------------------------------------\n");
	printf("    ID    |               NOMBRE             |     HORAS     |     SUELDO    |");
}

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
			printf( "\n------------------------------------------------------------------------\n"
					"%-10d|%-30s|%-12d|%-16.2f|\n"
					"------------------------------------------------------------------------\n",bufferEmployee.id, bufferEmployee.nombre, bufferEmployee.horasTrabajadas,bufferEmployee.sueldo);
			result = 0;
		}
	}
	return result;
}
/** \brief Funcion criterio que compara ids entre dos empleados
 *  \param void* employee1: Puntero void que castearemos al primer empleado
 *  \param void* employee2: Puntero void que castearemos al segundo empleado
 *  \return (1) Si el primer empleado tiene un id mayor al segundo, (-1) Si el segundo empleado tiene un id mayor al primero o (0) si son iguales
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

/*
 * \brief Carga el id en el campo del empleado (tratado como texto) y valida que el dato sea correcto
 * \param this Employee* puntero a empleado
 * \param id char* puntero al id que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int employee_setIdTxt(Employee* this, char* id)
{
    int result = -1;
    char bufferId[500];
    if (this != NULL && val_isValidNumber(id, sizeof(id)))
    {
        strncpy(bufferId,id,500);
        this->id = atoi(bufferId);
        result = 0;
    }
    return result;
}
/*
 * \brief Obtiene el id del empleado (tratado como texto)
 * \param this Employee* puntero a empleado
 * \param id char* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
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
/*
 * \brief Carga el id en el campo del empleado
 * \param this Employee* puntero a empleado
 * \param id int id a cargar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si el id no es valido
 * 					  (0) EXITO
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

/*
 * \brief Obtiene el id del empleado
 * \param this Employee* puntero a empleado
 * \param id int* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
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
 * \brief Carga el nombre en el campo del empleado y valida que el dato sea correcto
 * \param this Employee* puntero a empleado
 * \param name char* puntero al nombre que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al nombre es NULL
 * 					  (0) EXITO
 */
int employee_setNombre(Employee *this, char* nombre)
{
	int result = -1;
	if (this != NULL && nombre != NULL && val_isValidString(nombre, NAME_LEN))
	{
		strncpy(this->nombre, nombre, NAME_LEN);
		result = 0;
	}
	return result;
}

/*
 * \brief Obtiene el nombre del empleado
 * \param this Employee* puntero a empleado
 * \param name char* puntero al espacio donde va a guardar el nombre obtenido
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
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

/*
 * \brief Carga las horas trabajadas en el campo del empleado
 * \param this Employee* puntero a empleado
 * \param workedHours int horas trabajadas a cargar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si el valor no es valido
 * 					  (0) EXITO
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

/*
 * \brief Obtiene las horas trabajadas del empleado
 * \param this Employee* puntero a empleado
 * \param workedHours int* puntero al espacio donde va a guardar las horas trabajadas obtenidas
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al entero es NULL
 * 					  (0) EXITO
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
 * \brief Carga las horas trabajadas en el campo del empleado (tratado como texto) y valida que el dato sea correcto
 * \param this Employee* puntero a empleado
 * \param workedHours char* puntero a las horas trabajadas que va a guardar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
    int result = -1;
    if (this != NULL && horasTrabajadas>0 && val_isValidNumber(horasTrabajadas, sizeof(horasTrabajadas)))
    {
        this->horasTrabajadas = atoi(horasTrabajadas);
        result = 0;
    }
    return result;
}

/*
 * \brief Obtiene las horas trabajadas del empleado (tratado como texto)
 * \param this Employee* puntero a empleado
 * \param workedHours char* puntero al espacio donde va a guardar las horas trabajadas obtenidas
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero a las horas trabajadas es NULL
 * 					  (0) EXITO
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
 * \brief Carga el sueldo en el campo del empleado
 * \param this Employee* puntero a empleado
 * \param salary float sueldo a cargar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si el valor no es valido
 * 					  (0) EXITO
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
 * \brief Obtiene el sueldo del empleado
 * \param this Employee* puntero a empleado
 * \param salary float* puntero al espacio donde va a guardar el sueldo obtenido
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al flotante es NULL
 * 					  (0) EXITO
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
 * \brief Carga el sueldo en el campo del empleado (tratado como texto) y valida que el dato sea correcto
 * \param this Employee* puntero a empleado
 * \param salary char* puntero al sueldo que va a guardar
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al sueldo es NULL
 * 					  (0) EXITO
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
    int result = -1;
    char bufferSalary [500];
    if (this != NULL && val_isValidFloat(sueldo, sizeof(sueldo)))
    {
        strncpy(bufferSalary,sueldo,500);
        this->sueldo = atof(bufferSalary);
        result = 0;
    }
    return result;
}

/*
 * \brief Obtiene el sueldo del empleado (tratado como texto)
 * \param this Employee* puntero a empleado
 * \param salary char* puntero al espacio donde va a guardar el sueldo obtenido
 * \return int Return (-1) ERROR - Si el puntero a Employee* es NULL o si e puntero al sueldo es NULL
 * 					  (0) EXITO
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
