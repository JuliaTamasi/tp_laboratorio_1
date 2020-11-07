#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parse employee data from file data.csv(text)
 * \param FILE* pFile Pointer to file to load
 * \param LinkedList* pArrayListEmployee Pointer to LinkedList
 * \return [0] if OK / [-1] if error
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int result = -1;
	Employee* pEmployee;
	char bufferId [500];
	char bufferName [500];
	char bufferWorkedHours [500];
	char bufferSalary [500];

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		ll_clear(pArrayListEmployee);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferWorkedHours,bufferSalary)==4)
			{
				pEmployee = employee_newParametros(bufferId, bufferName, bufferWorkedHours,bufferSalary);
				if(pEmployee!=NULL)
				{
					ll_add(pArrayListEmployee, pEmployee);
					result = 0;
				}
			}
			else
			{
				employee_delete(pEmployee);
			}
		}while(!feof(pFile));
	}
    return result;
}
/** \brief Parse employee data from file databin.bin (binary mode)
 * \param FILE* pFile, Pointer to file to load
 * \param LinkedList* pArrayListEmployee, Pointer to LinkedList
 * \return [0] if OK / [-1] if error
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	/*//el open ya esta hecho porque recibo el pFile como parametro
	pFile = fopen("data.bin","r");  //primero lo abro en controller*/
	int result = -1;
	int readResult;
	Employee* pBuffer;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		ll_clear(pArrayListEmployee);
		do
		{
			pBuffer = employee_new(); //creo el empleado de manera dinamica
			if(pBuffer!=NULL)
			{
				readResult = fread(pBuffer,sizeof(Employee),1,pFile); //lo cargo con los datos del archivo. retornoLectura queda cargado con la cantidad de var que el fread pudo leer
				if(readResult==1)
				{
					ll_add(pArrayListEmployee,pBuffer);				//añado el empleado(buffer) a la linkedlist
					result = 0;
				}
				else
				{
					employee_delete(pBuffer);				//en caso de que el fread no haya podido levantar los datos, libero este espacio de memoria
				}
			}
		}while(!feof(pFile));
	}
    return result;
}
