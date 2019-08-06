/* ***************************************************************** */
/* File name:        cooler.h                                        */
/* File description: Header file containing the functions/methods    */
/*                   for the cooler                                  */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    11may2019                                       */
/* Revision date:    19may2019                                       */
/* ***************************************************************** */

#ifndef COOLER_H
#define COOLER_H

/* ***************************************************************** */
/* File name:        cooler.c                                        */
/* File description: This file has a couple of useful functions to   */
/*                   use the cooler                                  */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    11may2019                                       */
/* Revision date:    11may2019                                       */
/* ***************************************************************** */

/* ******************************************************** */
/* Method name: cooler_taco_init                            */
/* Method description: Initialize the cooler tachometer     */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void cooler_taco_init(void);

/* ******************************************************** */
/* Method name: cooler_getRPS                               */
/* Method description: Get the cooler speed in RPS          */
/* Input params: uiPeriod in microseconds                   */
/* Output params: uiCount                                   */
/* ******************************************************** */
unsigned int cooler_getRPS(unsigned int uiPeriod);

/* ******************************************************** */
/* Method name: cooler_init                                 */ 
/* Method description: Initialize the cooler                */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void cooler_init(void);

/* ******************************************************** */
/* Method name: PWM_init                                    */
/* Method description: Initialize the PWM pulse.            */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void PWM_init(void);

#endif /* COOLER_H */
