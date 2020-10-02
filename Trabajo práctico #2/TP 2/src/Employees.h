#ifndef EMPLOYEES_H_
#define EMPLOYEES_H_
#define NAME_LEN 51
#define RETRIES 3
#define QTY_EMPLOYEES 999

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
int addEmployees(Employee* aEmployees, int len, int id, char name[], char lastName[], float salary, int sector);
int getEmployeeData(Employee* aEmployees);
int modifyEmployee (Employee* aEmployee, int len);
int unsuscribeEmployee(Employee* pArray, int len);
int employeeReport(Employee* pArray, int len);
#endif /* EMPLOYEES_H_ */
