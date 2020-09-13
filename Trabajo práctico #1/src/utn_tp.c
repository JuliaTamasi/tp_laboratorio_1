#include <stdio.h>
#include <stdlib.h>
/*
 * \brief Solicita un entero al usuario
 * \param pResultado*, puntero al espacio de memoria donde se guarda el valor obtenido
 * \param char*mensaje, Es el mensaje a ser mostrado al usuario
 * \param char*mensajeError, Es el mensaje de error a ser mostrado al usuario
 * \param int minimo, Valor minimo admitido
 * \param int maximo, Valor maximo admitido
 * \param int reintentos, Cantidad de oportunidades para ingresar el dato
 * \return (-1)para indicar error/ (0) esta OK.
 */
int utn_getNumero (int* pResultado,char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	int respuestaScanf;
	if(pResultado!= NULL && mensaje!=NULL && mensajeError!= NULL && minimo<=maximo)
	{
		do
		{
			printf("%s", mensaje);
			fflush(stdin);
			respuestaScanf = scanf("%d", &bufferInt);
			if(bufferInt>=minimo && bufferInt<=maximo && respuestaScanf)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				reintentos--;
				if(reintentos!=0)
				{
					printf("%s. \nLe quedan %d reintentos", mensajeError, reintentos);
				}
				else
				{
					printf("Se ha quedado sin reintentos. La calculadora ha finalizado. Goodbye.");
				}
			}
		}while(reintentos>0);
	}
	return retorno;
}
/*
 * \brief Solicita un float al usuario
 * \param pNumberFloat*, puntero al espacio de memoria donde se guarda el valor obtenido
 * \param char*msg, Es el mensaje a ser mostrado al usuario
 * \param char*errorMsg, Es el mensaje de error a ser mostrado al usuario
 * \param int retries, Cantidad de oportunidades para ingresar el dato
 * \return (-1)para indicar error/ (0) esta OK.
 *
 */
int utn_getFloat (float* pNumberFloat,char* msg,char* errorMsg,int retries)
{
	int retorno = -1;
	float bufferFloat;
	int respuestaScanf;
	if(pNumberFloat!= NULL && msg!=NULL && errorMsg!= NULL)
	{
		do
		{
			printf("%s", msg);
			fflush(stdin);
			respuestaScanf = scanf("%f", &bufferFloat);
			if(respuestaScanf==1)
			{
				*pNumberFloat = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				retries--;
				if(retries!=0)
				{
					printf("%s. \nLe quedan %d reintentos", errorMsg, retries);
				}
				else
				{
					printf("Se ha quedado sin reintentos. Se volvera a iniciar el menu.");
				}
			}
		}while(retries>0);
	}
	return retorno;
}
/*
 * \brief Solicita un entero al usuario que representa a una opcion del menu
 * \param pOptionNumber*, puntero al espacio de memoria donde se guarda el valor obtenido
 * \param char*msg, Es el mensaje a ser mostrado al usuario
 * \param char*errorMsg, Es el mensaje de error a ser mostrado al usuario
 * \param int min, Valor minimo admitido
 * \param int max, Valor maximo admitido
 * \return (-1) para indicar error/ (0) esta OK.
 *
 */
int utn_getMenu(int* pOptionNumber, char* msg, char* errorMsg, int min, int max)
{
	int retorno = -1;
	int bufferInt;
	int respuestaScanf;

	if(pOptionNumber!=NULL && msg != NULL && errorMsg != NULL && min<=max)
	{
		do
		{
			printf("%s", msg);
			fflush(stdin);
			respuestaScanf = scanf("%d",&bufferInt);
			if(bufferInt >= min && bufferInt<= max && respuestaScanf == 1)
			{
				retorno = 0;
				*pOptionNumber = bufferInt;
				break;
			}
			else
			{
				printf("%s",errorMsg);
			}
		}while(respuestaScanf==0);
	}
	return retorno;
}
/**
 * \brief Realiza una suma entre dos numeros
 * \param float* pResultado, Puntero que hace referencia al espacio de memoria donde se guarda el resultado de la suma
 * \param float primerOperando, Primer operando ingresado
 * \param float segundoOperando, Segundo operando ingresado
 * \return (-1) si hay error / (0) si salio OK.
 */
int utn_getSuma(float* pResultado, float primerOperando, float segundoOperando)
{
	int retorno = -1;
	if(pResultado!=NULL)
	{
		*pResultado = primerOperando + segundoOperando;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza una resta entre dos numeros
 * \param float* pResultado, Puntero que hace referencia al espacio de memoria donde se guarda resultado de la resta
 * \param float primerOperando, Primer operando ingresado
 * \param float segundoOperando, Segundo operando ingresado
 * \return (-1) si hay error / (0) si salio OK.
 */
int utn_getResta(float* pResultado, float primerOperando, float segundoOperando)
{
	int retorno = -1;
	if(pResultado!=NULL)
	{
		*pResultado = primerOperando - segundoOperando;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza una multiplicacion entre dos numeros
 * \param float *pResultado, Puntero que hace referencia al espacio de memoria donde se guarda el resultado de la multiplicacion
 * \param float primerOperando, Primer operando ingresado
 * \param float segundoOperando, Segundo operando ingresado
 * \return (-1) si hay error / (0) si salio OK.
 */
int utn_getMultiplicacion(float* pResultado, float primerOperando, float segundoOperando)
{
	int retorno = -1;
	if(pResultado!=NULL)
	{
		*pResultado = primerOperando*segundoOperando;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza una division entre dos numeros
 * \param float *pResultado, Puntero que hace referencia al espacio de memoria donde se guarda el resultado de la division
 * \param float primerOperando, Primer operando ingresado
 * \param float segundoOperando, Segundo operando ingresado
 * \return (-1) si hay error / (0) si salio OK.
 */
int utn_getDivision(float* pResultado, float primerOperando, float segundoOperando)
{
	int retorno = -1;
	if(pResultado!=NULL && segundoOperando!= 0)
	{
		*pResultado = primerOperando/segundoOperando;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza el factorial de un numero
 * \param int *pResultado, Puntero que hace referencia al espacio de memoria donde se guarda el resultado del factorial
 * \param float numero, numero al que se le calculara el factorial
 * \return (-1) si hay error / (0) si salio OK.
 */
int utn_getFactorial(float* pResultado, float numero)
{
	float bufferInt = 1;
	int retorno = -1;
	int i;
	if(numero>=0 && pResultado!=NULL)
	{
		retorno = 0;
		if(numero!=0)
		{
			for (i=numero;i>0;i--)
			{
				bufferInt *= i;
			}
		*pResultado = bufferInt;
		}
		else
		{
			*pResultado = 1;
		}
	}
	return retorno;
}
/**
 * \brief imprime por consola las operaciones a realizar
 * \param float number1, primer operando de la operacion
 * \param float number2, segundo operando de la operacion
 */
void utn_printOperations(float number1, float number2)
{
	printf("Se calculara la suma de %.2f + %.2f", number1, number2);
	printf("\nSe calculara la resta de %.2f - %.2f", number1, number2);
	printf("\nSe calculara la multiplicacion de %.2f * %.2f", number1, number2);
	printf("\nSe calculara la division de %.2f / %.2f", number1, number2);
	printf("\nSe calculara el factorial de %.2f", number1);
	printf("\nSe calculara el factorial de %.2f", number2);
}
/**
 * \brief imprime por consola los resultados de las operaciones
 * \param float number1, primer operando de la operacion
 * \param float number2, segundo operando de la operacion
 */
void utn_printResults(float primerOperando,float segundoOperando, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion, float resultadoDivision,
				  int resultadoFactorial1, int resultadoFactorial2)
{
	printf("El resultado de la suma de %.2f + %.2f es = %.2f", primerOperando, segundoOperando, resultadoSuma);
	printf("\nEl resultado de la resta de %.2f - %.2f es = %.2f", primerOperando, segundoOperando, resultadoResta);
	printf("\nEl resultado de la multiplicacion de %.2f * %.2f es = %.2f", primerOperando, segundoOperando, resultadoMultiplicacion);
	if(primerOperando>=0)
	{
		printf("\nEl resultado del factorial de %.2f es = %d\nNOTA: Se calculó el factorial tomando solo la parte entera del numero", primerOperando, resultadoFactorial1);
	}
	else
	{
		printf("\nNo es posible sacar el factorial de un numero negativo");
	}
	if(segundoOperando!=0)
	{
		printf("\nEl resultado del factorial de %.2f es = %d\nNOTA: Se calculó el factorial tomando solo la parte entera del numero", segundoOperando, resultadoFactorial2);
		printf("\nEl resultado de la division de %.2f / %.2f es = %.2f", primerOperando, segundoOperando, resultadoDivision);
	}
	else
	{
		printf("No es posible dividir por 0.");
	}
}
