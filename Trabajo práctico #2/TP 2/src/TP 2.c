/*
 ============================================================================
 Name        : TP.c
 Author      : Julia Tamasi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Employees.h"

int main(void) {
	setbuf(stdout,NULL);
	int chosenOption;
	Employee arrayEmployees [QTY_EMPLOYEES];
	if(initEmployees(arrayEmployees, QTY_EMPLOYEES)==0)
	{
		do
		{
			if(utn_getMenu(&chosenOption,3,5,1)==0)
			{
				switch (chosenOption)
				{
				 	case 1:
				 	{
				 			Employee bufferEmployee;
				 			if(getEmployeeData(&bufferEmployee)==0)
				 			{
				 				if( addEmployees(arrayEmployees, QTY_EMPLOYEES, bufferEmployee.id, bufferEmployee.name,
				 					bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector)==0)
				 				{
				 					printf("[El empleado fue ingresado de manera exitosa]\n\n\n");
				 				}
				 			}
				 			break;
				 	}
				 	case 2:
				 	{
				 			if(modifyEmployee(arrayEmployees, QTY_EMPLOYEES)==0)
							{
								printf("[El empleado fue modificado de manera exitosa]\n\n\n");
							}
				 			break;
				 	}
				 	case 3:
				 	{
				 			if(unsuscribeEmployee(arrayEmployees, QTY_EMPLOYEES)==0)
				 			{
				 				printf("[El empleado fue dado de baja de manera exitosa]\n\n\n");
				 			}
				 			else
				 			{
				 				printf("\nIntentelo nuevamente.\n\n");
				 			}
				 			break;
				 	}
				 	case 4:
				 			if(employeeReport(arrayEmployees, QTY_EMPLOYEES)==0)
				 			{
				 				printf("\n-------------------------------FIN DEL REPORTE------------------------------------\n\n\n");
				 			}
				 			else
				 			{
				 				printf("\n-No se pudo realizar el reporte-\n\n");
				 			}
				}
			}
		}while(chosenOption!=5);
	}
	printf("¡Goodbye!");
	return EXIT_SUCCESS;
}
