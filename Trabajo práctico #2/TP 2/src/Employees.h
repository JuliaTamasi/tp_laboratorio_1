/*
 * Employees.h
 *
 *  Created on: 26 sep. 2020
 *      Author: juji
 */

#ifndef EMPLOYEES_H_
#define EMPLOYEES_H_
#define NAME_LEN 51

typedef struct
{
	int id;
	char name [NAME_LEN];
	char lastName [NAME_LEN];
	float salary;
	int sector;
	int isEmpty;
}Employee;
int initEmployees(Employee* pArrayEmployees, int len);
int getEmployeeData(Employee* bufferEmployees);
int addEmployees(Employee* aEmployees, int len, int id, char name[], char lastName[], float salary, int sector);
int printArrayEmployees(Employee* pArray, int index);
#endif /* EMPLOYEES_H_ */
