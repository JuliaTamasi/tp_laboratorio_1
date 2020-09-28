/*
 ============================================================================
 Name        : TP.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Employees.h"
#define QTY_EMPLOYEES 999

int main(void) {
	setbuf(stdout,NULL);
	int chosenOption;
	int employeeCount=0;
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
				 					employeeCount++;
				 				}
				 			}
				 			break;
				 	}
				}
			}

		}while(chosenOption!=5);
	}
	return EXIT_SUCCESS;
}
