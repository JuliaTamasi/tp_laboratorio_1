/*
 * parser.h
 *
 *  Created on: 5 nov. 2020
 *      Author: juji
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);

#endif /* SRC_PARSER_H_ */
