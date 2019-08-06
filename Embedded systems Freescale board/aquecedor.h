/* ***************************************************************** */
/* File name:        aquecedor.h                                     */
/* File description: Header file containing the function/methods     */
/*                   prototypes of aquecedor.c                       */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    11may2019                                       */
/* Revision date:    05jun2019                                       */
/* ***************************************************************** */

#include "tc_hal.h"

#define CGC_CLOCK_ENABLED 0x01U


/* ******************************************************** */
/* Method name: aquecedor_init                              */
/* Method description: Initialize the heater                */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void aquecedor_init(void);

/* ******************************************************** */
/* Method name: PWM_init                                    */
/* Method description: Initialize the PWM pulse.            */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void PWM_aquecedor_init(void);

/* ******************************************************** */
/* Method name: activate_CAD                                */
/* Method description: Set registers for Analog to digital  */
/* convertion            									*/
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void activate_CAD(void);

/* ******************************************************** */
/* Method name: start_CAD                                   */
/* Method description: Start one analog digital convertion  */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void start_CAD(void);
