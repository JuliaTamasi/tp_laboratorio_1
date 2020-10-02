#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int utn_myGets(char* array, int lenght);
static int utn_verifyNumArray(char* array);
static int utn_verifyCharArray(char* pArray);
static int utn_verifyFloat(char* array);

//ESTATICAS
/*
 * \brief static function to use instead of scanf(); to pick up user data
 * \param char* array, pointer to array
 * \param int lenght, limit of array
 */
static int utn_myGets(char* array, int lenght)
{
	int retorno = -1;
	if (array != NULL && lenght > 0 && fgets(array, lenght, stdin) == array)
	{
		fflush(stdin);
		if (array[strlen(array) - 1] == '\n' &&array[0]!='\n')
		{
			array[strlen(array) - 1] = '\0';
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Verifies if given array of number is a valid integer number
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyNumArray(char* array)
{
	int retorno = 1;
	int i = 0;
	if (array != NULL)
	{
		if (array[0] == '-')
		{
			i = 1;
		}
		for (; array[i] != '\0'; i++)
		{
			if ((array[i] > '9' || array[i] < '0'))
			{
				retorno = 0;
				break;
			}
		}
	}
		return retorno;
}
/*
 * \brief Verifies if given array of number is a valid float number
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyFloat(char array[])
{
	int retorno = 1;
	int i = 0;
	int commaCount=0;
	if (array != NULL)
	{
		if (array[0] == '-')
		{
			i = 1;
		}
		for (; array[i] != '\0'; i++)
		{
			if(array[i]=='.')
			{
				commaCount++;
			}
			if ((commaCount>1)||((array[i] > '9' || array[i] < '0') && array[i]!='.'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Verifies if given string as a pointer is a valid string
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyCharArray(char *pArray)
{
	int retorno = 1;
	int i;
	if (pArray != NULL) {
		for (i = 0; pArray[i] != '\0'; i++)
		{
			if( (pArray[i] < 'a' || pArray[i] > 'z') &&
				(pArray[i] < 'A' || pArray[i] > 'Z') && (pArray[i] != 32))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
//PUBLICAS
/* \ brief getName para pedirle al usuario que ingrese un caracter
 * \ param char *message es un puntero al espacio de memoria donde está el mensaje que verá el usuario
 * \ param char *userInput es el puntero al espacio de memoria donde se guarda el caracter que ingresa el usuario
 * \ param char *errorMessage es el puntero al espacio de memoria donde está el mensaje de error que se mostrará si el usario ingresa una opción incorrecta
 * \ param int attempts es la variable que decrementa en 1 cada vez que el usario comete un error al ingresar un caracter no válido
 * \ return (-1) Error / (0) Ok
 */
int utn_getName(char message[], char errorMessage[], char* pResult, int attemps, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	if (message != NULL && errorMessage != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", message);
			if (utn_myGets(bufferString, ARRAY_SIZE) == 0 && utn_verifyCharArray(bufferString) == 1 &&
				strnlen(bufferString, ARRAY_SIZE) < limit)
			{
				strncpy(pResult, bufferString, limit);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", errorMessage);
				attemps--;
			}
		}while (attemps >= 0);
	}
	return retorno;
}
/*
 * \brief asks user for an integer (applied to a starting preset menu)
 * \param int* number, pointer to memory space where value obtained will be saved
 * \param int retries, number of attempts for the user to choose a correct number from the menu
 * \param int max, maximum value allowed
 * \param int min, minimum value allowed
 * \return [-1] if error / [0] if ok
 */
int utn_getMenu(int *number, int retries, int max, int min)
{
	int retorno = -1;
	char textNumber[ARRAY_SIZE];
	if (number != NULL && min<=max && retries>=0)
	{
		do
		{
			printf( "Bienvenido. Elija una opcion:\n\n" //MENU INICIO
					"1- Dar de alta de empleado\n"
					"2- Modificar el registro de un empleado\n"
					"3- Dar de baja un empleado\n"
					"4- Imprimir todos los registros\n"
					"5- Salir");
			if (utn_myGets(textNumber, ARRAY_SIZE) == 0 && utn_verifyNumArray(textNumber) == 1)
			{
				*number = atoi(textNumber);
				retorno = 0;
				break;
			}
			else
			{
				retries--;
				if (retries != 0)
				{
					printf("\nError, te quedan %d intentos \n", retries);
				}
			}
		}while (retries > 0);
	}
	return retorno;
}
/* \brief asks user for an integer number
 * \param char* message, message shown to user
 * \param int* number, pointer to memory space where value obtained will be saved
 * \param int attempts, number of attempts for the user to choose a correct number from the menu
 * \param int max, maximum value allowed
 * \param int min, minimum value allowed
 * \return [-1] if error / [0] if ok
 */
int utn_getNumber(char* message, int* number, int attempts, int max, int min)
{
	int retorno = -1;
	char bufferTextNumber[ARRAY_SIZE];
	int bufferNumber;
	if (message != NULL && number != NULL)
	{
		do
		{
			printf("%s\n", message);
			if (utn_myGets(bufferTextNumber, ARRAY_SIZE) == 0 && utn_verifyNumArray(bufferTextNumber) == 1 && max >= min)
			{
				bufferNumber = atoi(bufferTextNumber);
				if(bufferNumber<=max && bufferNumber>=min)
				{
					*number = bufferNumber;
					retorno = 0;
					break;
				}
				else
				{
					attempts--;
					if (attempts != 0)
					{
						printf("\nError, te quedan %d intentos \n", attempts);
					}
				}
			}
			else
			{
				attempts--;
				if (attempts != 0)
				{
					printf("\nError. Te quedan %d intentos\n", attempts);
				}
			}
		}while(attempts > 0);
	}
	return retorno;
}
/* \brief asks user for a float
 * \param char* message, message shown to user
 * \param float* number, pointer to memory space where value obtained will be saved
 * \param int attempts, number of attempts for the user to choose a correct number from the menu
 * \param int max, maximum value allowed
 * \param int min, minimum value allowed
 * \return [-1] if error / [0] if ok
 * */
int utn_getNumberFloat(char* message, float* number, int attempts, int max, int min)
{
	int retorno = -1;
	char bufferTextNumber[ARRAY_SIZE];
	float bufferFloat;
	if (message != NULL && number != NULL)
	{
		do
		{
			printf("%s\n", message);
			if (utn_myGets(bufferTextNumber, ARRAY_SIZE) == 0 && utn_verifyFloat(bufferTextNumber) == 1 && max >= min)
			{
				bufferFloat = atof(bufferTextNumber);
				if(bufferFloat<=max && bufferFloat>=min)
				{
					*number = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					attempts--;
					if (attempts != 0)
					{
						printf("\nError, te quedan %d intentos \n", attempts);
					}
				}
			}
			else
			{
				attempts--;
				if (attempts != 0)
				{
					printf("\nError, te quedan %d intentos \n", attempts);
				}
			}
		}while(attempts > 0);
	}
	return retorno;
}
