#ifndef UTN_H_
#define UTN_H_
#define STRING_LEN 50
#define ARRAY_SIZE 4096
int utn_getName(char message[], char errorMessage[], char* pResult, int attemps, int limit);
int utn_getMenu(int *number, int retries, int max, int min);
int utn_getNumber(char* message, int* number, int attempts, int max, int min);
int utn_getNumberFloat(char* message, float* number, int attempts, int max, int min);
#endif /* UTN_H_ */
