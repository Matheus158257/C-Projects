/* ***************************************************************** */
/* File name:        lcd.h                                           */
/* File description: Header file containing the function/methods     */
/*                   prototypes of lcd.c                             */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    09may2019                                       */
/* Revision date:    05jun2019                                       */
/* ***************************************************************** */
#ifndef LCD_H
#define LCD_H

/* ***************************************************/
/* Method name: turnOnLcd                            */
/* Method description: This method writes the        */
/* initial screen on the Lcd board.                  */
/* Input params: iIndex used to set correctly the    */
/* cursor position                                   */
/* Output params: n/a                                */
/* ***************************************************/
void turnOnLcd(int *iIndex);

/* ***************************************************/
/* Method name: speedLCD                             */
/* Method description: This method writes the        */
/* cooler velocity.                                  */
/* Input params: iSpeed is the cooler speed in RPS   */
/* Output params: n/a                                */
/* ***************************************************/
void speedLCD(unsigned int iSpeed);

/* ***************************************************/
/* Method name: bothLCD                              */
/* Method description: This method writes the        */
/* cooler velocity and the heater temperature        */
/* Input params: iSpeed is the cooler speed in RPS   */
/* Input params: iTemp is the heater temperature     */
/* Output params: n/a                                */
/* ***************************************************/
void bothLCD(unsigned int iSpeed, int iTemp);

/* ***************************************************/
/* Method name: showDutyCycleLCD                     */
/* Method description: This method writes the        */
/* current duty cycle.                               */
/* Input params: cCommand given by the user          */
/* Output params: n/a                                */
/* ***************************************************/
void showDutyCycleLCD(char *cDC);

/* ***************************************************/
/* Method name: clearLcd                             */
/* Method description: This method clear the Lcd.    */
/*                                                   */
/* Input params: It receives the iIndex to be reseted*/
/* Output params:      n/a                           */
/* ***************************************************/
void clearLcd(int *iIndex);

/* ***************************************************/
/* Method name: showSetPoint                         */
/* Method description: This method writes the        */
/* setpoint			                                 */
/* Input params: cCommand given by the user 		 */
/* iTemp          									 */
/* Output params: n/a                                */
/* ***************************************************/
void showSetPoint(char *cCommand, int iTemp);

/* ***************************************************/
/* Method name: showPID                              */
/* Method description: This method writes on the     */
/* Lcd the values of Kp, Kd and Ki                   */
/* Input params: cCommand given by the user          */
/* Output params: n/a                                */
/* ***************************************************/
void showPID(char *cCommand);

#endif /* LCD_H */
