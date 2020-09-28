/*
 * Employees.c
 *
 *  Created on: 26 sep. 2020
 *      Author: juji
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Employees.h"
#include <limits.h>
#define NAME_LEN 51
#define RETRIES 3
static int generateNewId(void);
static int findEmptyIndex(Employee* aEmployees, int len, int* emptyIndex);

/** \brief To indicate that all position in the array are empty,
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
int addEmployees(Employee* aEmployees, int len, int id, char name[], char lastName[], float salary, int sector)
{
	int retorno = -1;
	int bufferIndex;
	if(aEmployees != NULL && len>0)
	{
		if(findEmptyIndex(aEmployees, len, &bufferIndex)==0)
		{
			aEmployees[bufferIndex].id=id;
			aEmployees[bufferIndex].isEmpty=0;
			aEmployees[bufferIndex].salary=salary;
			aEmployees[bufferIndex].sector=sector;
			strncpy(aEmployees[bufferIndex].name,name,NAME_LEN);
			strncpy(aEmployees[bufferIndex].lastName,lastName,NAME_LEN);//copio los datos del buffer en el array original
		}
	}
	return retorno;
}
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
				bufferEmployees->isEmpty = 0;
				result = 0; //Almaceno los datos en el buffer
			}
	}
		return result;
}
static int generateNewId(void)
{
    static int id=0; // es global para solo la fn puede usarla
    //guardar el ultimo que asigne (ultimo que devolvi)
    //para devolver 1+
    id = id+1;
    return id;
}
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
int printArrayEmployees(Employee* pArray, int index)
{
	int retorno = -1;
	if(pArray!=NULL && index>=0)
	{
			if(pArray[index].isEmpty == 0)
			{
				printf("Nombre: %s\nSalario: %.2f\nIndice: %d\nId: %d\n",pArray[index].name,pArray[index].salary,index,pArray[index].id);
				retorno=0;
			}
	}
	return retorno;
}
