#ifndef UTN_TP_H_
#define UTN_TP_H_

int utn_getNumero (int* pResultado,char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos);
int utn_getFloat (float* pNumberFloat,char* msg,char* errorMsg,int retries);
int utn_getMenu(int* pOptionNumber, char* msg, char* errorMsg, int min, int max);
int utn_getSuma(float* pResultado, float primerOperando, float segundoOperando);
int utn_getResta(float* pResultado, float primerOperando, float segundoOperando);
int utn_getMultiplicacion(float* pResultado, float primerOperando, float segundoOperando);
int utn_getDivision(float* pResultado, float primerOperando, float segundoOperando);
int utn_getFactorial(float* pResultado, float numero);
void utn_printOperations(float number1, float number2);
void utn_printResults(float primerOperando,float segundoOperando, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion, float resultadoDivision,
				  float resultadoFactorial1, float resultadoFactorial2);

#endif /* UTN_TP_H_ */
