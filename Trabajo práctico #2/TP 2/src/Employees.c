#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Employees.h"
#include <limits.h>

static int generateNewId(void);
static int findEmptyIndex(Employee* aEmployees, int len, int* emptyIndex);
static int printArrayEmployees(Employee* pArray, int len);
static int printIndex(Employee* pArray, int index);
static int findEmployeeById(Employee* aEmployee, int len, int id);
static int removeEmployee(Employee* pArray, int len, int id);
static int arrayIsEmpty (Employee* pArray, int len);
static int sortEmployees(Employee* list, int len, int order);
static int calculateAverageSalary(Employee* pArray, int len, float* averageSalary, float* totalSalary);
static int salaryAboveAverage (Employee* pArray, int len, float averageSalary, int* counterAboveAverage);

//ESTATICAS

/*\brief to generate a new ID to every log generated
 */
static int generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}
/** \brief search for an empty index for an employee's load
 * \param Employee* aEmployees, Pointer to array of employees
 * \param int len, Array lenght
 * \param int* emptyIndex, pointer to the memory space where the empty index of the array will be saved
 * \return Return (0) if OK or (-1) if there is any error
 */
static int findEmptyIndex(Employee* aEmployees, int len, int* emptyIndex)
{
	int i;
	int retorno = -1;
	if(aEmployees!=NULL && len>0 && emptyIndex!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(aEmployees[i].isEmpty==1 && aEmployees[i].id==0)
			{
				*emptyIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/* \brief print the content of employees array
 * \param Employee* pArray, Pointer to employees array
 * \param int len, Limit of array
 * \return [0] if ok / [1] if error
 */
static int printArrayEmployees(Employee* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && len>=0 && arrayIsEmpty(pArray, len)==0)
	{
		printf("\n>Estos son los empleados activos actualmente: \n");
		printf("\n----------------------------------------------------------------------------------\n");
		printf("      APELLIDO      |       NOMBRE       |   ID   |      SUELDO     |   SECTOR  |");
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0)
			{
				printf( "\n----------------------------------------------------------------------------------\n"
						"%-20s|%-20s|%-8d|%-17.2f|%-11d|\n"
					    "----------------------------------------------------------------------------------",pArray[i].lastName, pArray[i].name, pArray[i].id, pArray[i].salary, pArray[i].sector);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/* \brief print the content of a specific array index
 * \param Employee* pArray, Pointer to employees array
 * \param int index, Index of the array from which the data will be printed
 * \return [0] if ok / [1] if error
 */
static int printIndex(Employee* pArray, int index)
{
	int retorno = -1;
	if(pArray!=NULL && index>=0)
	{
			if(pArray[index].isEmpty == 0)
			{
				printf("\n----------------------------------------------------------------------------------\n");
				printf("      APELLIDO      |       NOMBRE       |   ID   |      SUELDO     |   SECTOR  |");
				printf("\n----------------------------------------------------------------------------------\n"
						"%-20s|%-20s|%-8d|%-17.2f|%-11d|\n"
						"----------------------------------------------------------------------------------",pArray[index].lastName, pArray[index].name, pArray[index].id, pArray[index].salary, pArray[index].sector);
				retorno=0;
			}
	}
	return retorno;
}
/** \brief find an Employee by ID and returns the index position in array
 * \param Employees* aEmployees, Pointer to array of employees
 * \param int len, Array lenght
 * \param int id, Id of the employee sought
 * \return Return employee index position or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int findEmployeeById(Employee* aEmployee, int len, int id)
{
	int i;
	int result = -1;
	if(aEmployee!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(aEmployee[i].id==id && aEmployee[i].isEmpty==0)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}
/* \ brief logically unsubscribe an Employee (put isEmpty Flag in TRUE)
 * \param list Employee* pArray pointer to employees array
 * \param int len, limit of array
 * \param int id, id of specific employee
 * \ returns int Return [-1] if Error - [0] if Ok
 */
static int removeEmployee(Employee* pArray, int len, int id)
{
	int result = -1;
	int bufferIndex;
	if(pArray!=NULL && len>0 && id>0)
	{
		bufferIndex = findEmployeeById(pArray, len, id);
		if(bufferIndex>=0)
		{
			pArray[bufferIndex].isEmpty = 1;
			result = 0;
		}
	}
	return result;
}
/**
 * \brief Function to search in the Employee array for an empty field
 * \param Employee* pArray, Pointer to an Employee array
 * \param int len, Length of the array
 * \return (1) if array is empty, (0) if there is at least one full position
 */
static int arrayIsEmpty (Employee* pArray, int len)
{
	int i;
	int result = 1;
	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0)
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
/* \brief Sort the elements in the array of employees
 * \param Employee* pArray, Receives as a pointer a given array to be listed alphabetically
 * \param int len, Receives the limit of the array to be listed
 * \param int order, [1] indicate UP - [0] indicate DOWN
 * \return int Return [-1] if Error [Invalid length or NULL pointer] - [0] if OK
 */
static int sortEmployees(Employee* pArray, int len, int order)
{
	int result = -1;
	int index;
	int flagSort = 0;
	Employee bufferEmployee;

	if(pArray != NULL && len > 0)
	{
		while(flagSort==0)
		{
			flagSort=1;
			for(index=0 ; index<(len-1)  ; index++)
			{
				if  ((strcmp(pArray[index].lastName, pArray[index+1].lastName) < 0 && order == 0) ||
				    ((strcmp(pArray[index].lastName, pArray[index+1].lastName) > 0) && order == 1) ||
					((strcmp(pArray[index].lastName, pArray[index+1].lastName) == 0 && pArray[index].sector < pArray[index+1].sector) && order == 0) ||
					((strcmp(pArray[index].lastName, pArray[index+1].lastName) == 0 && pArray[index].sector > pArray[index+1].sector) && order == 1))
				{
					bufferEmployee = pArray[index];
					pArray[index] = pArray[index+1];
					pArray[index+1] = bufferEmployee;
					flagSort=0;
				}
			}
		}
		result = 0;
	}
	return result;
}
/* \brief calculate the employees total and average salary
 * \param Employee* pArray, Pointer to employee array
 * \param int len, Array limit
 * \param float* averageSalary, Pointer to the memory space where the result of the average salary will be saved
 * \param float* totalSalary, Pointer to the memory space where the result of the total salary will be saved
 * \return [0] if ok / [1] if error
 */
static int calculateAverageSalary(Employee* pArray, int len, float* averageSalary, float* totalSalary)
{
	int result = -1;
	int i;
	float bufferSalary;
	int employeesCount=0;
	if(pArray!=NULL && len > 0 && averageSalary!=NULL && totalSalary!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0)
			{
				employeesCount++;
				bufferSalary+=pArray[i].salary;
			}
		}
		*totalSalary = bufferSalary;
		*averageSalary = bufferSalary/employeesCount;
		result = 0;
	}
	return result;
}
/* \brief calculates how many employees exceed the average salary
 * \param Employee* pArray, Pointer to employee array
 * \param int len, Array limit
 * \param float* averageSalary, Average salary of employees
 * \param  int* counterAboveAverage, Pointer to the memory space where the result will be saved
 * \return [0] if ok / [1] if error
 */
static int salaryAboveAverage (Employee* pArray, int len, float averageSalary, int* counterAboveAverage)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(pArray!=NULL && len > 0 && counterAboveAverage!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].salary > averageSalary && pArray[i].isEmpty == 0)
			{
				bufferCounter++;
			}
		}
		*counterAboveAverage = bufferCounter;
		result = 0;
	}
	return result;
}
//PUBLICAS

/** \brief To indicate that all position in the array are empty,
 * 		   and all the employees ID's are 0,
 * 		   this function put the flag (isEmpty) in TRUE in all
 * 		   position of the array
 * \param Employees* pArrayEmployees, Pointer to array of employees
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int initEmployees(Employee* pArrayEmployees, int len)
{
	int i;
	int retorno = -1;
	if(pArrayEmployees!=NULL && len>0)
	{
		for (i=0;i<len;i++)
		{
			pArrayEmployees[i].isEmpty = 1;
			pArrayEmployees[i].id = 0;
		}
		retorno=0;
	}
	else
	{
		printf("\nNo se realizo el proceso correctamente\n");
	}
	return retorno;
}
/* \brief save in an existing list of employees the values received as parameters in the first empty position
 * \param Employee *pArrayEmployee, Pointer to an Employee array
 * \param int len, Length of the array
 * \param int id, Receives the id
 * \param char* name, Receive the name to give to a new employee
 * \param char* lastName, Receive the last name to give to a new employee
 * \param float salary, Receive the salary to give to a new employee
 * \param int sector, Receive the sector to give to a new employee
 * \return int Return [-1] if Error [Invalid length or NULL pointer or without free space] - [0] if Ok
 */
int addEmployees(Employee* aEmployees, int len, int id, char* name, char* lastName, float salary, int sector)
{
	int retorno = -1;
	int bufferIndex;
	if(aEmployees != NULL && len>0)
	{
		if(findEmptyIndex(aEmployees, len, &bufferIndex)==0 && aEmployees[bufferIndex].isEmpty==1)
		{
			aEmployees[bufferIndex].id=id;
			aEmployees[bufferIndex].isEmpty=0;
			aEmployees[bufferIndex].salary=salary;
			aEmployees[bufferIndex].sector=sector;
			strncpy(aEmployees[bufferIndex].name,name,NAME_LEN);
			strncpy(aEmployees[bufferIndex].lastName,lastName,NAME_LEN);//copio los datos del buffer en el array original
			retorno=0;
		}
	}
	return retorno;
}
/* \brief Obtain the employee's data to register it
 * \param Employee* bufferEmployees, Pointer to buffer where the data will be saved momentarily
 * \return Return (-1) if Error [NULL pointer] - (0) if OK
 */
int getEmployeeData(Employee* bufferEmployees)
{
	int result = -1;
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	float salary;
	int sector;
	if(bufferEmployees!=NULL)
	{
		if( utn_getName("Ingrese el nombre del empleado\n", "Error", name, RETRIES, NAME_LEN)==0 &&
			utn_getName("Ingrese el apellido del empleado\n", "Error", lastName, RETRIES, NAME_LEN)==0 &&
			utn_getNumberFloat("Ingrese el sueldo del empleado\n",&salary, RETRIES, LONG_MAX, 0)==0 &&
			utn_getNumber("Ingrese el sector del empleado\n",&sector, RETRIES, INT_MAX, 1)==0)
			{
				strncpy(bufferEmployees->name,name,NAME_LEN);
				strncpy(bufferEmployees->lastName,lastName,NAME_LEN);
				bufferEmployees->sector=sector;
				bufferEmployees->salary=salary;
				bufferEmployees->id=generateNewId();
				result = 0; //Almaceno los datos en el buffer
			}
	}
		return result;
}
/* \brief Modifies employee data
 * \param Employee* aEmployee, Pointer to employees array
 * \param int len, Array limit
 * \return [0] if ok / [-1] if error
 */
int modifyEmployee (Employee* aEmployee, int len)
{
	int result = -1;
	int auxId;
	int bufferIndex;
	int chosenOption;

	if( aEmployee!=NULL && len>0 && printArrayEmployees(aEmployee, len)==0 && utn_getNumber("\n\nPor favor ingrese el Id del registro que desea modificar:\n",&auxId,RETRIES,INT_MAX,1)==0 &&
		arrayIsEmpty(aEmployee, len)==0)
	{
		bufferIndex = findEmployeeById(aEmployee, len, auxId);
		if(bufferIndex>=0)
		{
			printIndex(aEmployee, bufferIndex);
			printf("\n\n[Empleado encontrado con exito]\n\n");
			do
			{
				if( utn_getNumber("¿Que campo del registro desea modificar?\n[1] Nombre\n[2] Apellido\n[3] Sueldo\n[4] Sector\n[5] Volver al menu\n", &chosenOption, RETRIES, 5, 1)==0)
				{
					switch(chosenOption)
					{
						case 1:
						{
								if(utn_getName("Por favor, ingrese el nombre del empleado:\n", "ERROR. Ingrese un nombre valido\n", aEmployee[bufferIndex].name, RETRIES, NAME_LEN)==0)
								{
									printf("¡Nombre ingresado con exito!\nNombre: %s\n", aEmployee[bufferIndex].name);
									result = 0;
								}
								else
								{
									printf("-ERROR. Intentelo nuevamente-\n");
								}
								break;
						}
						case 2:
						{
								if(utn_getName("Por favor, ingrese el apellido del empleado:\n", "ERROR. Ingrese un apellido valido\n", aEmployee[bufferIndex].lastName, RETRIES, NAME_LEN)==0)
								{
									printf("¡Apellido ingresado con exito!\nApellido: %s\n", aEmployee[bufferIndex].lastName);
									result = 0;
								}
								else
								{
									printf("ERROR. Intentelo nuevamente\n");
								}
								break;
						}
						case 3:
						{
								if(utn_getNumberFloat("Por favor ingrese el sueldo del empleado:\n", &aEmployee[bufferIndex].salary, RETRIES, LONG_MAX, 1)==0)
								{
									printf("¡Sueldo ingresado con exito!\nSueldo: %.2f\n", aEmployee[bufferIndex].salary);
									result = 0;
								}
								else
								{
									printf("-ERROR. Intentelo nuevamente-\n");
								}
								break;
						}
						case 4:
						{
								if(utn_getNumber("Por favor ingrese el sector del empleado:\n", &aEmployee[bufferIndex].sector, RETRIES, INT_MAX, 1)==0)
								{
									printf("¡Sector ingresado con exito!\nSector: %d\n", aEmployee[bufferIndex].sector);
									result = 0;
								}
								else
								{
									printf("-ERROR. Intentelo nuevamente-\n");
								}
								break;
						}
					}
				}

			}while(chosenOption!=5);
		}
		else
		{
			printf("-No se pudo encontrar el Id-\n");
		}
	}
	else
	{
		printf("\nERROR\n\n");
	}
	return result;
}
/* \brief Requires the employee's id and logs it off logically
 * \param Employee* pArray, Pointer to employees array
 * \param int len, Limit of array
 * \return [0] if ok / [-1] if error
 */
int unsuscribeEmployee(Employee* pArray, int len)
{
	int result = -1;
	int bufferId;
	if(pArray!=NULL && len>0)
	{
		if( printArrayEmployees(pArray, len) == 0 &&
			utn_getNumber("\n\nIngrese el id del empleado que desea dar de baja:\n", &bufferId, RETRIES, INT_MAX, 1)==0)
		{
			if(removeEmployee(pArray, len, bufferId)==0)
			{
				printf("-Empleado encontrado-\n");
				result = 0;
			}
		}
		else
		{
			printf("\n-Opcion incorrecta-\n");
		}
	}
	return result;
}
/* \brief prints alphabetically ordered the array of employees and the report on wages
 * \param Employee* pArray, Pointer to employee array
 * \param int len, Array limit
 * \return [0] if ok / [1] if error
 */
int employeeReport(Employee* pArray, int len)
{
	int result = -1;
	int bufferOrder;
	int op;
	float averageSalary;
	float totalSalary;
	int employeesAboveAverage;
	if( pArray!=NULL && len>0 && arrayIsEmpty(pArray, len)==0 &&
		utn_getNumber("\nIngrese la opcion que desea:\n\n[1] Mostrar el listado de empleados ordenado alfabeticamente por apellido\n[2] Mostrar informacion sobre los salarios\n[3] Volver al menu\n", &op, RETRIES, 3, 1)==0)
	{
		switch(op)
		{
			case 1:
			{
				if(utn_getNumber("\n¿De que manera desea ordenar los empleados?\n\n[1] Ascendente (A-Z)\n[0] Descendente (Z-A)\n" ,&bufferOrder, RETRIES,1,0)==0)
				{
					if(sortEmployees(pArray, len, bufferOrder)==0)
					{
						printArrayEmployees(pArray, len);
						result = 0;
					}
				}
				else
				{
					printf("Ingrese una opcion valida.\n");
				}
				break;
			}
			case 2:
			{
				if( calculateAverageSalary(pArray, len, &averageSalary, &totalSalary)==0 &&
					salaryAboveAverage(pArray, len, averageSalary, &employeesAboveAverage)==0)
				{
					printf("\n----------------------------------------------------------------------------------\n");
					printf("> La suma de los sueldos de todos los empleados es $%.2f\n", totalSalary);
					printf("> El sueldo promedio de los empleados es $%.2f\n", averageSalary);
					if(employeesAboveAverage>0)
					{
						printf("> Del total de los empleados [%d] superan el sueldo promedio\n",employeesAboveAverage);
					}
					else
					{
						printf("> No hay ningun empleado que supere el sueldo promedio\n");
					}
					result = 0;
				}
				break;
			}
		}
	}
	return result;
}
