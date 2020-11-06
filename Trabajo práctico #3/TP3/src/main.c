/*
 ============================================================================
 Name        : TP3.c
 Author      : Julia Tamasi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/
int main()
{
	setbuf(stdout,NULL);
	int chosenOption;
	//int answer;
	int loadFlag = 0;
	LinkedList *listaEmpleados = ll_newLinkedList();
	do{
		if(!utn_getMenu(&chosenOption, 3, 10, 1))
		{
			switch(chosenOption)
			{
				case 1:
						if(!controller_loadFromText("data.csv",listaEmpleados))
						{
							printf("[Empleados cargados de manera exitosa]\n");
						}

						/*else
						{
							if( !utn_getNumber("\n- Actualmente ya hay una lista cargada, desea reemplazarla?\n[1]- Si\n[2]- No\n", &answer, 3, 2, 1) &&
								answer == 1 && !controller_loadFromBinary("data.bin", listaEmpleados))
							{
								printf("[Empleados cargados de manera exitosa]\n");
							}
						}*/
						break;
				case 2:
						if(controller_loadFromBinary("data.bin", listaEmpleados)==0)
						{
							printf("Exito\n");
						}
						/*if(loadFlag)
						{
							if( !utn_getNumber("\n- Actualmente ya hay una lista cargada, desea reemplazarla?\n[1]- Si\n[2]- No\n", &answer, 3, 2, 1) &&
								answer == 1 && !controller_loadFromBinary("data.bin", listaEmpleados))
							{
								printf("[Empleados cargados de manera exitosa]\n");
							}
							else
							{
								printf("[Volviendo al menú...]\n");
							}
						}
						else
						{
							if(!controller_loadFromBinary("data.csv", listaEmpleados))
							{
								loadFlag = 1;
								printf("[Empleados cargados de manera exitosa]\n");
							}
						}*/
						break;
				case 3:
						if(loadFlag && !controller_addEmployee(listaEmpleados) && !ll_isEmpty(listaEmpleados))
						{
							printf("[Empleado dado de alta con exito]\n");
						}
						break;
				case 6:
						if(!ll_isEmpty(listaEmpleados))
						{
							if(!controller_ListEmployee(listaEmpleados))
							{
								printf("\n********************************************** FIN DE LA LISTA **********************************************\n");
							}
						}
						else
						{
							printf("[ERROR. Debe realizar la carga de los empleados primero]\n");
						}
						break;
				case 9:
						if(!ll_isEmpty(listaEmpleados) && !controller_saveAsBinary("data.bin", listaEmpleados))
						{
							printf("[El archivo se guardó con exito en modo binario]\n");
						}
						break;
			}
		}
	}while(chosenOption != 10);
	printf("\nGOODBYE!");
    return 0;
}
