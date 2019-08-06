/* ***************************************************************** */
/* File name:        converstions.c                                  */
/* File description: This file has some useful functions to          */
/*                   convert an integer into a string                */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    16may2019                                       */
/* Revision date:    16may2019                                       */
/* ***************************************************************** */

#include <string.h>

/* ***************************************************/
/* Method name: reverse                              */
/* Method description: This method  is used to calcu-*/
/* late reverse string from a given initial string.  */
/* Input params: char cS[] - the string that has to  */
/* be reverted                                       */
/*                                                   */
/* Output params: n/a                                */
/* ***************************************************/

/* reverse:  reverse string s in place */
void reverse(char cS[])
{
    int iI, jJ;
    char cC;

    for (iI = 0, jJ = strlen(cS)-1; iI<jJ; iI++, jJ--) {
    	cC = cS[iI];
        cS[iI] = cS[jJ];
        cS[jJ] = cC;
    }
}

/* ***************************************************/
/* Method name: itoa                                 */
/* Method description: This method  is used to calcu-*/
/* late the convertion from integer to string.       */
/* Input params: int iN - The integer to be converted*/
/* char cS[] - the string where the function should  */
/* save the result                                   */
/* Output params: n/a                                */
/* ***************************************************/
void itoa(int iN, char cS[])
{
    int iI, iSign;

    if ((iSign = iN) < 0)  /* record sign */
        iN = -iN;          /* make n positive */
    iI = 0;
    do {       /* generate digits in reverse order */
        cS[iI++] = iN % 10 + '0';   /* get next digit */
    } while ((iN /= 10) > 0);     /* delete it */
    if (iSign < 0)
        cS[iI++] = '-';
    cS[iI] = '\0';
    reverse(cS);
}
