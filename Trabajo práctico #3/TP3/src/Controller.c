#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Controller.h"
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


/** \brief Loads employee data from data.csv file (text mode).
 * \param char* path, file path
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int result = -1;
	FILE* pFile;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path,"r");
		if(pFile!=NULL && !parser_EmployeeFromText(pFile, pArrayListEmployee))
		{
			result = 0;
		}
		else
		{
			printf("[No se pudo abrir el archivo correctamente]\n");
		}
		fclose(pFile);
	}
	return result;
}

/** \brief Loads employee data from databin.bin file (binary mode).
 * \param char* path, file path
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int result=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile!=NULL && !parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			result=0;
		}
		else
		{
			printf("[No se pudo abrir el archivo correctamente]\n");
		}
		fclose(pFile);
	}
	return result;
}
//}

/** \brief To register a new employee
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	Employee bufferEmployee;
	Employee* pEmployee;

	if(pArrayListEmployee!=NULL)
	{
		pEmployee = employee_new();
		if( pEmployee!=NULL &&
			!utn_getName("[Ingrese el nombre del empleado]\n", "Error. Ingrese un nombre valido\n", bufferEmployee.nombre, 3, NAME_LEN) &&
			!utn_getNumber("[Ingrese la cantidad de horas trabajadas]\n", &bufferEmployee.horasTrabajadas, 3, INT_MAX, 0) &&
			!utn_getNumberFloat("[Ingrese el sueldo del empleado]\n", &bufferEmployee.sueldo, 3, INT_MAX, 0))
		{
			bufferEmployee.id = controller_findMaxId(pArrayListEmployee);
			if(bufferEmployee.id>0)
			{
				pEmployee = employee_newWithParameters(bufferEmployee.id, bufferEmployee.nombre, bufferEmployee.horasTrabajadas, bufferEmployee.sueldo);
				ll_add(pArrayListEmployee, pEmployee);
				printf("\nID para el nuevo empleado: %d\n", bufferEmployee.id);
				result = 0;
			}
		}
	}
    return result;
}

/** \brief Modify the data of an existing employee
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */

int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int id;
	int bufferIndex;
	int option;
	char bufferName[NAME_LEN];
	int bufferHours;
	float bufferSalary;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL)
	{
		if( !utn_getNumber("\n[Ingrese el id del empleado a modificar]\n", &id, 3, 99999, 1) &&
			!controller_findEmployeeById(pArrayListEmployee, id, &bufferIndex) && bufferIndex>-1)
		{
			employee_printHeader();
			bufferEmp = ll_get(pArrayListEmployee, bufferIndex);
			employee_printByIndex(pArrayListEmployee, bufferIndex);
			if(!utn_getNumber( "\n\n[Ingrese el campo que desea modificar]\n[1] Nombre\n[2] Horas trabajadas\n[3] Sueldo\n[4] Volver al menú\n", &option, 3, 4, 1))
			{
				switch(option)
				{
					case 1:
						if( !utn_getName("[Ingrese el nombre del empleado]\n", "[ERROR. Ingrese un nombre valido]\n", bufferName, 3, NAME_LEN) &&
							!employee_setNombre(bufferEmp, bufferName))
						{
							result=0;
						}
						break;
					case 2:
						if( !utn_getNumber("\n[Ingrese la cantidad de horas trabajadas]\n",&bufferHours, 3, 9999, 1) &&
							!employee_setHorasTrabajadas(bufferEmp, bufferHours))
						{
							result=0;
						}
						break;
					case 3:
						if( !utn_getNumberFloat("[Ingrese el sueldo del empleado]\n", &bufferSalary, 3, 9999, 1) &&
							!employee_setSueldo(bufferEmp, bufferSalary))
						{
							result=0;
						}
						break;
				}
			}
		}
		else
		{
			printf("\n[ERROR. No se pudo encontrar el ID]\n");
		}
	}
	return result;
}

/** \brief Removes an employee from the list and frees the memory area used by him
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int bufferIndex;
	int bufferId;
	Employee* pEmployee;
	int chosenOption;

	if (pArrayListEmployee != NULL)
	{
		if (!utn_getNumber("\nIngrese el id del empleado que quiere eliminar:\n",&bufferId, 2, INT_MAX, 1) &&
			!controller_findEmployeeById(pArrayListEmployee, bufferId,&bufferIndex) &&
			 bufferIndex>0)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, bufferIndex);
			if ( pEmployee != NULL && !employee_printByIndex(pArrayListEmployee, bufferIndex) && !utn_getNumber("¿Desea confirmar la eliminacion?\n[1] Si\n[2] No\n", &chosenOption, 3, 2, 1) &&
				 chosenOption==1)
			{
				employee_delete(pEmployee);
				ll_remove(pArrayListEmployee,bufferIndex);
				result = 0;
			}
			else
			{
				printf("[Volviendo al menu...]\n");
			}
		}
	}
    return result;
}

/** \brief Prints the employee list data
 * \param LinkedList* pArrayListEmployee, pointer to LinkedList
 * \return [-1] if ERROR or [0] if OK
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int len;
	int i;

	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		len = ll_len(pArrayListEmployee);
		employee_printHeader();
		for (i=0;i<len;i++)
		{
			if(!employee_printByIndex(pArrayListEmployee, i))
			{
				result = 0;
			}
		}
	}
    return result;
}

/** \brief Sort employees alphabetically by name (1 = ascending order / 0 = descending order)
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return (-1) if ERROR (0) if OK
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int chosenOption;
	if(pArrayListEmployee!=NULL)
	{
		if(!utn_getNumber("¿Como desea ordenar la lista?\n[0] Descendente\n[1] Ascendente\n", &chosenOption, 3, 1, 0))
		{
			ll_sort(pArrayListEmployee, employee_compararPorNombre, chosenOption); //preguntarle al usuario por que criterio quiere ordenar
			result = 0;
		}
	}
    return result;
}

/** \brief Save employee data in the file data.csv (text mode)
 * \param char* path, File path
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return (-1) if ERROR (0) if OK
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int result = -1;
	int len;
	char bufferName[NAME_LEN];
	int bufferId;
	int bufferWorkedHours;
	float bufferSalary;
	FILE* pFile;
	Employee* pEmployee;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "w");
		len = ll_len(pArrayListEmployee);
		if(pFile!=NULL)
		{
			ll_sort(pArrayListEmployee, employee_compararPorId, 1);
			fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");
			for(int i=0;i<len;i++)
			{
				pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
				if( pEmployee!=NULL &&
					!employee_getId(pEmployee, &bufferId) &&
					!employee_getNombre(pEmployee, bufferName) &&
					!employee_getHorasTrabajadas(pEmployee, &bufferWorkedHours) &&
					!employee_getSueldo(pEmployee, &bufferSalary))
				{
					fprintf(pFile, "%d,%s,%d,%f\n",bufferId, bufferName, bufferWorkedHours, bufferSalary);
					result=0;
				}
			}
			fclose(pFile);
		}
	}
	return result;
}

/** \brief Save employee data in the file databin.bin (binary mode)
 * \param char* path, File path
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return (-1) if ERROR (0) if OK
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int result = -1;
	FILE* pFile;
	int len;
	Employee* pAuxEmployee;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		len = ll_len(pArrayListEmployee);
		pFile = fopen(path,"wb");
		if(pFile!=NULL)
		{
			ll_sort(pArrayListEmployee,employee_compararPorId,1);
			for(int i = 0; i<len; i++)
			{
				pAuxEmployee = (Employee*) ll_get(pArrayListEmployee,i);
				fwrite(pAuxEmployee,sizeof(Employee),1,pFile);
			}
			result = 0;
			fclose(pFile);
		}
	}
    return result;
}
/** \brief Finds the existing maximum ID in the employee list
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return the value of the maximum ID found + 1 or [-1] if ERROR
 */
int controller_findMaxId (LinkedList* pArraylistEmployee)
{
	int result = -1;
	Employee* bufferEmployee;
	int id;
	int max;
	int len = ll_len(pArraylistEmployee);

	if(pArraylistEmployee!=NULL)
	{
		for(int i=0; i<len; i++)
		{
			bufferEmployee = ll_get(pArraylistEmployee, i);
			employee_getId(bufferEmployee, &id);
			if(id>max || i==0)
			{
				max = id;
			}
		}
		result = max+1;
	}
	return result;
}
/** \brief Search for an employee by ID
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \param int id, "ID" to be searched
 * \param int* index, pointer to the memory space where the index corresponding to the employee's "ID" will be saved
 * \return [-1] if ERROR or [0] if OK
 */
int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id, int* index)
{
	int result = -1;
	int len;
	int bufferId;
	Employee* pEmployee;
	if(pArrayListEmployee!=NULL && id>0)
	{
		len = ll_len(pArrayListEmployee);
		for(int i=0;i<len;i++)
		{
			pEmployee = ll_get(pArrayListEmployee, i);
			if(!employee_getId(pEmployee, &bufferId) && bufferId == id)
			{
				result = 0;
				*index = i;
				break;
			}
		}
	}
	return result;
}
