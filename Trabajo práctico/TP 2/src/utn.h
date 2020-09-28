/*
 * utn.h
 *
 *  Created on: 8 sep. 2020
 *      Author: juji
 */

#ifndef UTN_H_
#define UTN_H_


int utn_getNumero (int* pResultado,char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos);
int utn_getNumberFloat(char *message, float *numberX, int attempts, int max, int min);
int utn_getChar(char *message, char *userInput, char* errorMessage, int attempts);
int utn_getMaxInt(int array[], int lenght, int *pResult);
int utn_getMaxFloat(float array[], int lenght, int *pResult);
int utn_getMenu(int *number, int retries, int max, int min);
int utn_getValidarArrayChar(char array[], int tamanio);
int utn_getName(char message[], char errorMessage[], char* pResult,int attemps, int limit);
int utn_validarRangoString(char array[], char caracterMinimo, char caracterMaximo);
int utn_contarLetrasEnArray(char array[], char letraBuscada, int* pResultadoContador);
void utn_ordenarArray(int array[], int len);
int utn_contarNumerosEnArray(int array[], int limite, int numeroBuscado, int* pResultadoContador);
int utn_imprimirArray(int array[], int limite);
int utn_getNumber(char *message, int *number, int attempts, int max, int min);
#endif /* UTN_H_ */
