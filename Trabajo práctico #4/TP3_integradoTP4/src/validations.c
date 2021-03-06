/*
 * validations.c
 *
 *  Created on: 4 nov. 2020
 *      Author: juji
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validations.h"
/**
 * \brief Validates that what it receives is a valid int number.
 * \param char* number, pointer to the string to be validated
 * \param int len, lenght of the string
 * \return [1] if TRUE / [0] if FALSE
 */
int val_isValidNumber(char* number)
{
    int result = 1;
    int i = 0;

    if(number!= NULL && strlen(number)>0)
    {
        if(number[0] == '-' || number[0] == '+')
        {
            i = 1;
        }
        for( ; i < strlen(number); i++)
        {
            if(number[i] < '0' || number[i] > '9')
            {
                result = 0;
                break;
            }
        }
    }
    return result;
}
/**
 * \brief Validates that what it receives is a string.
 * \param char* string, pointer to the string to be validated
 * \param int len, lenght of the string
 * \return [1] if TRUE / [0] if FALSE
 */
int val_isValidString(char string[], int len)
{
	int result = 1;
	int i;
	if(string != NULL && len > 0)
	{
		for(i = 0; string[i]!='\0' && i<len; i++)
		{
			if((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32 && string[i] != '-')
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
/*
 * \brief Verifies if given array of number is a valid float number
 * \param char* number, pointer to the string to be validated
 * \return [1] if TRUE / [0] if FALSE
 */
int val_isValidFloat(char* number)
{
	int result = 1;
	int i = 0;
	int commaCounter = 0;

	if (number != NULL && strlen(number)>0)
	{
		if (number[0] == '-' || number[0] == '+')
		{
			i = 1;
		}
		for (; i<strlen(number); i++)
		{
			if(number[i]=='.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((number[i] > '9' || number[i] < '0') && number[i]!='.'))
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
