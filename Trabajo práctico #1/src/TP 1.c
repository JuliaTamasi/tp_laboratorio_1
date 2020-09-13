#include <stdio.h>
#include <stdlib.h>
#include "utn_tp.h"


int main(void)
{
	setbuf(stdout, NULL);
	int opcionIngresada;
	float primerOperando;
	float segundoOperando;
	int flagPrimerOperando=0;
	int flagSegundoOperando=0;
	int flagCalcular=0;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	float resultadoFactorial1;
	float resultadoFactorial2;


		if(utn_getNumero(&opcionIngresada,"\nBienvenido, por favor ingrese una opcion:\n\n1 = Ingresar el primer operando\n2 = Ingresar el segundo operando\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error.\nPor favor ingrese una opcion valida(1-5)",1,5,3)==0)
		{
			do
			{
				switch(opcionIngresada)
				{
					case 1:
							if(utn_getFloat(&primerOperando,"\nPor favor ingrese el primer operando", "Error. Por favor ingrese un numero", 3)==0)
							{
								flagPrimerOperando = 1;
								printf("Usted ingresó el numero: %.2f", primerOperando);
								utn_getMenu(&opcionIngresada, "\nComo desea continuar?\n1 = Reemplazar el primer operando por otro\n2 = Ingresar el segundo operando\n3 = Realizar calculos con los operandos", "Error. Ingrese una opcion valida",1,3);
							}
					break;
					case 2:
							if(utn_getFloat(&segundoOperando,"\nPor favor ingrese el segundo operando\n","\nError, ingrese un numero.\n",3)==0)
							{
								flagSegundoOperando = 1;
								printf("Usted ingreso el numero %.2f", segundoOperando);
								utn_getMenu(&opcionIngresada, "\nComo desea continuar?\n1 = Ingresar el primer operando.\n2 = Reemplazar el segundo operando por otro\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error. Ingrese una opcion valida",1,5);
							}
					break;
					case 3:
							if(flagPrimerOperando==1 && flagSegundoOperando==1 && utn_getSuma(&resultadoSuma, primerOperando, segundoOperando)==0 && utn_getResta(&resultadoResta, primerOperando, segundoOperando)==0 &&
								utn_getMultiplicacion(&resultadoMultiplicacion, primerOperando, segundoOperando)==0 && utn_getDivision(&resultadoDivision, primerOperando, segundoOperando)==0 &&
								utn_getFactorial(&resultadoFactorial1, primerOperando)==0 && utn_getFactorial(&resultadoFactorial2, segundoOperando)==0)
							{
								utn_printOperations(primerOperando,segundoOperando);
								flagCalcular = 1;
								utn_getMenu(&opcionIngresada, "\n\nComo desea continuar?\n1 = Ingresar el primer operando.\n2 = Reemplazar el segundo operando por otro\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error. Ingrese una opcion valida",1,5);
							}
							else
							{
								printf("\nDebe ingresar los operadores antes de intentar realizar los calculos.");
								utn_getMenu(&opcionIngresada, "\nComo desea continuar?\n1 = Ingresar el primer operando.\n2 = Reemplazar el segundo operando por otro\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error. Ingrese una opcion valida",1,5);
							}
					break;
					case 4:
							if(flagPrimerOperando == 1 && flagSegundoOperando == 1 && flagCalcular == 1)
							{
								utn_printResults(primerOperando, segundoOperando, resultadoSuma, resultadoResta, resultadoMultiplicacion, resultadoDivision, resultadoFactorial1, resultadoFactorial2);
								utn_getMenu(&opcionIngresada, "\n\nComo desea continuar?\n\n1 = Ingresar el primer operando.\n2 = Reemplazar el segundo operando por otro\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error. Ingrese una opcion valida",1,5);
							}
							else
							{
								printf("Necesita ingresar los operandos y realizar las operaciones antes de pedir los resultados");
								utn_getMenu(&opcionIngresada, "\n\nComo desea continuar?\n\n1 = Ingresar el primer operando.\n2 = Reemplazar el segundo operando por otro\n3 = Realizar calculos con los operandos\n4 = Informar los resultados de las operaciones\n5 = Salir de la calculadora.\n", "Error. Ingrese una opcion valida",1,5);
							}
					break;

				}
			} while(opcionIngresada!=5);
			printf("Usted ingreso la opción 5... Goodbye!");
		}
	return EXIT_SUCCESS;
}
