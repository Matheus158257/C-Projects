/* ***************************************************************** */
/* File name:        conversions.h                                   */
/* File description: Header file containing the function/methods     */
/*                   prototypes of conversions.c                     */
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
#ifndef CONVERSIONS_H
#define CONVERSIONS_H


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
void reverse(char cS[]);

/* ***************************************************/
/* Method name: itoa                                 */
/* Method description: This method  is used to calcu-*/
/* late the convertion from integer to string.       */
/* Input params: int iN - The integer to be converted*/
/* char cS[] - the string where the function should  */
/* save the result                                   */
/* Output params: n/a                                */
/* ***************************************************/
void itoa(int iN, char cS[]);


#endif /* CONVERSIONS_H */
