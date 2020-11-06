/*
 * validations.c
 *
 *  Created on: 4 nov. 2020
 *      Author: juji
 */
#include <stdio.h>
#include <stdlib.h>
#include "validations.h"
/**
 * \brief Validates that what it receives is a number.
 * \param char* number, pointer to the string to be validated
 * \param int len, lenght of the string
 * \return (0) FALSE (1) TRUE
 */
int val_isValidNumber(char* number, int len)
{
    int result = 1;
    int i = 0;

    if(number!= NULL && len > 0)
    {
        if(number[0] == '-' || number[0] == '+')
        {
            i = 1;
        }
        for( ; number[i]!= '\0' && i < len; i++)
        {
            if(number[i] < '0' || number[i] > '9')
            {
                result = 0;
                break;
            }
        }
        result = 0;
    }
    return result;
}
/**
 * \brief Validates that what it receives is a string.
 * \param char* string, pointer to the string to be validated
 * \param int len, lenght of the string
 * \return (0) FALSE (1) TRUE
 */
int val_isValidString(char string[], int len)
{
	int retorno = 1;
	if(string != NULL && len > 0)
	{
		for(int i = 0; string[i]!='\0' && i<len; i++)
		{
			if((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32 && string[i] != '-')
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
int val_isValidFloat(char array[], int len)
{
	int result = 1;
	int i = 0;
	int commaCounter = 0;
	if (array != NULL && len>0)
	{
		if (array[0] == '-' || array[0] == '+')
		{
			i = 1;
		}
		for (; array[i]!='\0' && i<len; i++)
		{
			if(array[i]=='.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((array[i] > '9' || array[i] < '0') && array[i]!='.'))
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
