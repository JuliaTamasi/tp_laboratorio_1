#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Controller.h"
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(!utn_getNumber("¿Como desea ordenar la lista?\n[0] Descendente\n[1] Ascendente\n", &chosenOption, 3, 1, 0))
		{
			ll_sort(pArrayListEmployee, employee_compararPorNombre, chosenOption); //preguntarle al usuario por que criterio quiere ordenar
			result = 0;
		}
	}
	else
	{
		printf("[ERROR. No se puede ordenar una lista vacia]\n");
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
	int result=-1;
	int len = ll_len(pArrayListEmployee);
	char bufferName[NAME_LEN];
	int bufferId;
	int bufferWorkedHours;
	float bufferSalary;
	FILE* pFile;
	Employee* pEmployee;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			ll_sort(pArrayListEmployee, employee_compararPorId, 1);
			fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");
			for(int i=0;i<len;i++)
			{
				pEmployee = ll_get(pArrayListEmployee, i);
				if( !employee_getId(pEmployee, &bufferId) &&
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

/** \brief Save employee data in the file data.bin (binary mode)
 * \param char* path, File path
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return (-1) if ERROR (0) if OK
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	//recorro la lista y solamente escribo en el archivo. La interaccion importante es con la lista
	//hacer una funcion que valide el path, que se fije si existe
	int result = -1;
	FILE* pFile;
	int len = ll_len(pArrayListEmployee); //me fijo cuanto mide la lista de punteros
	Employee* pAuxEmployee;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path,"wb"); //destruye el archivo original y se crea uno nuevo
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
/** \brief Busca en la lista de empleados el maximo id y retorna ese valor + 1
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return el valor del maximo id encontrado + 1 o (-1) si algo salio mal
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
/** \brief Buscar empleado por ID
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \param int id: Recibimos el ID a buscar
 * \param int* index: Devolvemos por referencia el indice del empleado encontrado
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
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
