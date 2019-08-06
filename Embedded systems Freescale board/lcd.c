/* ***************************************************************** */
/* File name:        lcd.c                                           */
/* File description: This file has some useful functions to          */
/*                   write the initial information on the ldc        */
/*                   and to clear it                                 */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    09may2019                                       */
/* Revision date:    01jul2019                                       */
/* ***************************************************************** */

#include <MKL25Z4.h>
#include "lcd_hal.h"
#include "lcd.h"
#include "conversions.h"

char *cNames = "Breno Matheus Pedro                ";
char cText[16];
char cText2[16] = "Breno Matheus Pe";

/* ***************************************************/
/* Method name: turnOnLcd                            */
/* Method description: This method writes the        */
/* initial screen on the Lcd board.                  */
/* Input params: iIndex used to set correctly the    */
/* cursor position                                   */
/* Output params: n/a                                */
/* ***************************************************/
void turnOnLcd(int *iIndex){

	// Writes ES670 on the first line
	lcd_setCursor(0,0);
	lcd_writeString("ES670");

	// Writes students names on the right position
	// This position changes each time that turnOnLcd function is called
	if (*iIndex <= 15){
		lcd_setCursor(1,(15-*iIndex));
		lcd_writeString(cText2);
	}

	if (*iIndex >= 16){
		for(int iJ = 0; iJ < 16; iJ++){
			cText[iJ] = cNames[*iIndex + iJ - 15];
		}
		lcd_setCursor(1,0);
		lcd_writeString(cText);
	}

	*iIndex = *iIndex + 1;

	// When it finishes the loop the index is restarted
	if(*iIndex == 35){
		*iIndex=0;
	}
}

/* ***************************************************/
/* Method name: speedLCD                             */
/* Method description: This method writes the        */
/* cooler velocity.                                  */
/* Input params: iSpeed is the cooler speed in RPS   */
/* Output params: n/a                                */
/* ***************************************************/
void speedLCD(unsigned int iSpeed){
	lcd_setCursor(1,0);
    lcd_writeString("                ");

	// Writes ES670 on the first line
	lcd_setCursor(0,0);
	lcd_writeString("Cooler Speed:");

	char cSpeed[20];
	itoa(iSpeed,cSpeed);
	lcd_setCursor(1,0);

	lcd_writeString(cSpeed);
}

/* ***************************************************/
/* Method name: bothLCD                              */
/* Method description: This method writes the        */
/* cooler velocity and the heater temperature        */
/* Input params: iSpeed is the cooler speed in RPS   */
/* Input params: iTemp is the heater temperature     */
/* Output params: n/a                                */
/* ***************************************************/
void bothLCD(unsigned int iSpeed, int iTemp){
	lcd_setCursor(1,0);
    lcd_writeString("                ");

	// Writes ES670 on the first line
	lcd_setCursor(0,0);
	lcd_writeString("Speed: | Temp:");

	char cTemp[20];
	itoa(iTemp,cTemp);
	char cSpeed[20];
	itoa(iSpeed,cSpeed);
	lcd_setCursor(1,0);
	lcd_writeString(cSpeed);
	lcd_setCursor(1,6);
	lcd_writeString(" | ");
	lcd_setCursor(1,9);
	lcd_writeString(cTemp);
}

/* ***************************************************/
/* Method name: showDutyCycleLCD                     */
/* Method description: This method writes the        */
/* current duty cycle.                               */
/* Input params: cCommand given by the user          */
/* Output params: n/a                                */
/* ***************************************************/
void showDutyCycleLCD(char *cCommand){
	lcd_setCursor(1,0);
    lcd_writeString("                ");

	
	lcd_setCursor(0,0);
	// Writes one of the duty Cycles depending by the command
	if(cCommand[0] == 'H'){
		lcd_writeString("Duty Cycle AQ:");
	}
	else{
		lcd_writeString("Duty Cycle CL:");
	}

	lcd_setCursor(1,0);

	char cDC[3] = {cCommand[2], cCommand[3], cCommand[4]};
	lcd_writeString(cDC);
}

/* ***************************************************/
/* Method name: clearLcd                             */
/* Method description: This method clear the Lcd.    */
/*                                                   */
/* Input params: It receives the iIndex to be reseted*/
/* Output params:      n/a                           */
/* ***************************************************/
void clearLcd(int *iIndex){
	*iIndex = 0;
	lcd_setCursor(0,0);
	lcd_writeString("                ");
	lcd_setCursor(1,0);
    lcd_writeString("                ");
}

/* ***************************************************/
/* Method name: showSetPoint                         */
/* Method description: This method writes the        */
/* setpoint			                                 */
/* Input params: cCommand given by the user 		 */
/* iTemp          									 */
/* Output params: n/a                                */
/* ***************************************************/
void showSetPoint(char *cCommand, int iTemp){
	lcd_setCursor(1,0);
    lcd_writeString("                ");

	// Writes ES670 on the first line
	lcd_setCursor(0,0);
	lcd_writeString("SPoint: | Temp:");

	lcd_setCursor(1,0);

	char cDC[2] = {cCommand[4], cCommand[5]};
	lcd_writeString(cDC);
	char cTemp[20];
	itoa(iTemp,cTemp);
	lcd_setCursor(1,7);
	lcd_writeString(" | ");
	lcd_setCursor(1,10);
	lcd_writeString(cTemp);
}

/* ***************************************************/
/* Method name: showPID                              */
/* Method description: This method writes on the     */
/* Lcd the values of Kp, Kd and Ki                   */
/* Input params: cCommand given by the user          */
/* Output params: n/a                                */
/* ***************************************************/
void showPID(char *cCommand){
	lcd_setCursor(1,0);
    lcd_writeString("                ");

	// Writes ES670 on the first line
	lcd_setCursor(0,0);
	lcd_writeString("Kp: | Ki: | Kd:");

	char cKp[2] = {cCommand[1], cCommand[2]};
	char cKi[2] = {cCommand[4], cCommand[5]};
	char cKd[2] = {cCommand[7], cCommand[8]};
	lcd_setCursor(1,0);
	lcd_writeString(cKp);
	lcd_setCursor(1,3);
	lcd_writeString(" | ");
	lcd_setCursor(1,6);
	lcd_writeString(cKi);
	lcd_setCursor(1,9);
	lcd_writeString(" | ");
	lcd_setCursor(1,12);
	lcd_writeString(cKd);
}
