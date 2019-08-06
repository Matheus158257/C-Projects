/* ***************************************************************** */
/* File name:        SevenSeg.h                                      */
/* File description: Header file containing the function/methods     */
/*                   prototypes of SevenSeg.c                        */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    29mar2019                                       */
/* Revision date:    09may2019                                       */
/* ***************************************************************** */

#ifndef SEVENSEG_H
#define SEVENSEG_H

/* ************************************************ */
/* Method name:        sevenSegInit                 */
/* Method description: This method initialize the   */
/* Ports for the 7 segments display. It set this    */
/* pins as GPIO and as digital outputs.             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void sevenSegInit(void);

/* ************************************************ */
/* Method name:        showValues                   */
/* Method description: This method show the 4 values*/
/* given as input on the 7 segments displays        */
/*                                                  */
/* Input params: Four integers.                     */
/* iD3 = Value to be shown in display 1 (DS1)        */
/* iD2 = Value to be shown in display 2 (DS2)        */
/* iD1 = Value to be shown in display 3 (DS3)        */
/* iD0 = Value to be shown in display 4 (DS4)        */
/* Output params:      n/a                          */
/* ************************************************ */
void showValues(int iD3, int iD2, int iD1, int iD0);

#endif /* SEVENSEG_H */
