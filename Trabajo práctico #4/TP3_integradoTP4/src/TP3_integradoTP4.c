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
	int answer;
	int loadFlag = 0;
	LinkedList *listaEmpleados = ll_newLinkedList();

	do{
		if(!utn_getMenu(&chosenOption, 3, 10, 1))
		{
			switch(chosenOption)
			{
				case 1:
						if(loadFlag==0 && controller_loadFromText("data.csv", listaEmpleados)==0)
						{
							loadFlag = 1;
							printf("[¡Archivo cargado con exito!]\n");
						}
						else
						{
							if( !utn_getNumber("\n- Actualmente ya hay una lista cargada, desea reemplazarla?\n[1]- Si\n[2]- No\n", &answer, 3, 2, 1) &&
								answer==1 && !controller_loadFromText("data.csv", listaEmpleados))
							{
								printf("[¡Archivo cargado con exito!]\n");
							}
							else
							{
								printf("[Volviendo al menú...]\n");
							}
						}
						break;
				case 2:
						if(loadFlag==0 && controller_loadFromBinary("databin.bin", listaEmpleados)==0)
						{
							loadFlag = 1;
							printf("[¡Archivo cargado con exito!]\n");
						}
						else
						{
							if( !utn_getNumber("\n- Actualmente ya hay una lista cargada, desea reemplazarla?\n[1]- Si\n[2]- No\n", &answer, 3, 2, 1) &&
								answer == 1 && !controller_loadFromBinary("databin.bin", listaEmpleados))
							{
								printf("[¡Archivo cargado con exito!]\n");
							}
							else
							{
								printf("[Volviendo al menú...]\n");
							}
						}
						break;
				case 3:
						if(loadFlag && !controller_addEmployee(listaEmpleados) && !ll_isEmpty(listaEmpleados))
						{
							printf("[¡Empleado dado de alta con exito!]\n");
						}
						else
						{
							printf("[Debe cargar el archivo antes de realizar el alta]\n");
						}
						break;
				case 4:
						if(!ll_isEmpty(listaEmpleados))
						{
							if(!controller_editEmployee(listaEmpleados))
							{
								printf("[¡Empleado modificado con exito!]\n");
							}
						}
						else
						{
							printf("[ERROR. No se encontraron empleados disponibles para la modificacion]\n");
						}
						break;
				case 5:
						if(!ll_isEmpty(listaEmpleados))
						{
							if(!controller_removeEmployee(listaEmpleados))
							{
								printf("[¡Empleado dado de baja con exito!]\n");
							}
						}
						else
						{
							printf("[ERROR. Debe cargar al menos un empleado primero]");
						}
						break;
				case 6:
						if(!ll_isEmpty(listaEmpleados))
						{
							if(!controller_ListEmployee(listaEmpleados))
							{
								printf("\n***************************** FIN DE LA LISTA ****************************\n\n");
							}
						}
						else
						{
							printf("[ERROR. Debe realizar la carga de los empleados antes de listarlos]\n");
						}
						break;
				case 7:
						if(!ll_isEmpty(listaEmpleados))
						{
							if(!controller_sortEmployee(listaEmpleados))
							{
								printf("\n[¡Listado ordenado con exito!]\n\n");
							}
						}
						else
						{
							printf("[ERROR. Debe realizar la carga de los empleados primero]\n");
						}
						break;
				case 8:
						if(!ll_isEmpty(listaEmpleados) && !controller_saveAsText("data.csv", listaEmpleados))
						{
							printf("¡[El archivo se guardó con exito (txt)!]\n");
						}
						break;
				case 9:
						if(!ll_isEmpty(listaEmpleados) && !controller_saveAsBinary("databin.bin", listaEmpleados))
						{
							printf("[¡El archivo se guardó con exito (bin)!]\n");
						}
						break;
			}
		}
	}while(chosenOption != 10);
	ll_deleteLinkedList(listaEmpleados);
	printf("\nGOODBYE!");
    return 0;
}
