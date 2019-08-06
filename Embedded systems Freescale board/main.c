/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "es670_peripheral_board.h"
#include <MKL25Z4.h>
#include "util.h"
#include "mcg_hal.h"
#include "SevenSeg.h"
#include "target.h"
#include "ledswi_hal.h"
#include "debugUart.h"
#include "print_scan.h"
#include "fsl_debug_console.h"
#include "lcd.h"
#include "lcd_hal.h"
#include "tc_hal.h"
#include "cooler.h"
#include "aquecedor.h"
#include "conversions.h"

#define CYCLIC_EXECUTIVE_PERIOD 1000 * 1000 //micro seconds

char cCommand[9];
/* Global Variables */
int iIndex = 0 , iIndex2 = 0, iShowNames = 0, iShowSpeed = 0, iShowBoth = 0, iShowDutyCycleCooler = 0,iShowDutyCycleAquecedor = 0, iTemp = 25, iShowSetPoint = 0, iShowPID = 0;;
volatile unsigned int uiFlagNextPeriod = 0; /*cyclic executive flag*/
int iKp = 0, iKi = 0, iKd = 0, iSetPoint = 0, iIntError = 0, iPrevError = 0, iCurrError = 0;

/* Handler for temperature acquisition */
void ADC0_IRQHandler(void){
	unsigned char tabela_temp[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, //31
	1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, //47
	7, 7, 8, 8, 8, 8, 9, 9, 10, 10, 10, 10, 11, 11, 12, 12, //63
	12, 12, 13, 13, 14, 14, 15, 15, 15, 15, 16, 16, 16, 17, 17, 17, //79
	17, 18, 18, 19, 19, 19, 19, 20, 20, 21, 21, 21, 21, 22, 22, 23, //95
	23, 24, 24, 24, 24, 25, 25, 26, 26, 26, 26, 27, 27, 28, 28, 28, //111
	28, 29, 29, 30, 30, 30, 30, 31, 31, 32, 32, 32, 32, 33, 33, 34, //127
	34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 39, 39, 39, //143
	39, 40, 40, 41, 41, 41, 41, 42, 42, 43, 43, 44, 44, 44, 44, 45, //159
	45, 46, 46, 46, 46, 47, 47, 48, 48, 48, 48, 49, 49, 50, 50, 50, //175
	50, 51, 51, 52, 52, 53, 53, 53, 53, 54, 54, 55, 55, 55, 55, 56, //191
	56, 57, 57, 57, 57, 58, 58, 59, 59, 59, 59, 60, 60, 61, 61, 62, //207
	62, 62, 62, 63, 63, 64, 64, 64, 64, 65, 65, 66, 66, 66, 66, 67, //223
	67, 68, 68, 68, 68, 69, 69, 70, 70, 71, 71, 71, 71, 72, 72, 72, //239
	73, 73, 73, 73, 74, 74, 75, 75, 75, 75, 76, 76, 77, 77, 77, 77 //255
	};

	int iAux = ADC0_RA;
	iTemp = tabela_temp[iAux];
}



/* ************************************************ */
/* Method name: main_cyclicExecuteIsr 				*/
/* Method description: cyclic executive interrupt 	*/
/* service routine								    */
/* Input params: n/a 								*/
/* Output params: n/a 								*/
/* ************************************************ */
void main_cyclicExecuteIsr(void){
	/* set the cyclic executive flag */
	uiFlagNextPeriod = 1;
}

/* ************************************************ */
/* Method name: UART0_IRQHandler 					*/
/* Method description: UART0 interrupt routine 		*/
/* Input params: n/a 								*/
/* Output params: n/a 								*/
/* ************************************************ */
void UART0_IRQHandler(void){
	NVIC_DisableIRQ(UART0_IRQn);
	cCommand[iIndex] = GETCHAR();
	iIndex++;
	NVIC_EnableIRQ(UART0_IRQn);
}

int main(void)
{
	/* Call functions that initialize the clock, target, 7 segments displays, LED 4, LCD, coooler and the push button 3. */
	mcg_clockInit();
	cooler_init();
	PWM_init();
	aquecedor_init();
	PWM_aquecedor_init();
	targetInit();
	sevenSegInit();
	ledswi_initLedSwitch(1u, 3u);
	lcd_initLcd();
	activate_CAD();

	/* configure cyclic executive interruption */
	tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);
	/* Variables that keep the values shown in the 7 segments displays and the push button 3 status. */
	int iD3 = 10, iD2 = 10, iD1 = 10, iD0 = 10, iStatus = 2;

	/* configure UART0 interrupts */
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	/* receive interrupt enable */
	UART0_C2_REG(UART0) |= UART0_C2_RIE(1);

	/* Initializes the interruption ADC0*/
	NVIC_EnableIRQ(ADC0_IRQn);

	int iI = 0;
    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {

    	/* Checks if the cooler speed must be displayed on the LCD */
    	if (iShowSpeed){
    		speedLCD(cooler_getRPS(CYCLIC_EXECUTIVE_PERIOD));
    	}
    	/* Checks if one of the Duty Cycles must be displayed on the LCD  */
    	else if(iShowDutyCycleCooler || iShowDutyCycleAquecedor){
			showDutyCycleLCD(cCommand);
    	}
    	/* Checks if  both the cooler speed and the temperature must be displayed on the LCD */
    	else if(iShowBoth){
    		start_CAD();
    		bothLCD(cooler_getRPS(CYCLIC_EXECUTIVE_PERIOD), iTemp);
    	}
    	else if(iShowSetPoint){
			
    		TPM1_C0V = TPM_CnV_VAL(255*10/100);
    		iPrevError = (iSetPoint - iTemp);/*gets the error of the previuous ireaction*/
    		start_CAD();
    		char cSetPoint[2] = {cCommand[4], cCommand[5]};/*Gets the SetPoint based on the command*/
    		iSetPoint = atoi(cSetPoint);
    		showSetPoint(cCommand, iTemp);
			
    		iCurrError = (iSetPoint - iTemp);/*Current Error*/
    		iIntError += (iSetPoint - iTemp);/*Integration Error*/
			
			/*Gets the exit value based on all the portions of the PID control*/
    		int iProp = iKp*iCurrError;
    		int iInt = iKi*iIntError;
    		int iDeriv = iKd*(iCurrError - iPrevError);

			/*This is a simmulation of the control loop*/
    		if ((iProp + iInt + iDeriv) < 0){
    			TPM1_C1V = TPM_CnV_VAL(iProp + iInt + iDeriv);
    		} else {
    			TPM1_C1V = TPM_CnV_VAL(0);
    		}
    	}
		/*Used to get the values of the PID gains*/
    	else if(iShowPID){
    		char cKp[2] = {cCommand[1], cCommand[2]};
    		char cKi[2] = {cCommand[4], cCommand[5]};
    		char cKd[2] = {cCommand[7], cCommand[8]};
    		iKp = atoi(cKp);
    		iKi = atoi(cKi);
    		iKd = atoi(cKd);
    		showPID(cCommand);
    	}

    	/* While the interruption is not reached, uiFlagNextPeriod==0 */
    	/* Once the interruption is reached, uiFlagNextPeriod==1 and the loop ends */
    	while(!uiFlagNextPeriod){
    		/* Communication between o Host e o Target.*/
    		respondToHost(&iD3, &iD2, &iD1, &iD0, &iStatus, cCommand, &iIndex, &iIndex2, &iShowNames, &iShowSpeed, &iShowBoth , &iShowDutyCycleAquecedor,&iShowDutyCycleCooler, &iShowSetPoint, &iShowPID, &iIntError);
    		showValues (iD3, iD2, iD1, iD0);
    			/* Checks if the group members names must be displayed on the LCD */
    		    if (iShowNames && (iI%5 == 0)){
    		    	turnOnLcd(&iIndex2);
    		    	iI = 0;
    		    }

    		iI++;
    	}

    	/* Resets uiFlagNextPeriod */
    	uiFlagNextPeriod = 0;
    }

    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
