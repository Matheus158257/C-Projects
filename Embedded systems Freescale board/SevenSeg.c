/* ***************************************************************** */
/* File name:        SevenSeg.c                                      */
/* File description: This file has a couple of useful functions to   */
/*                   use the seven segments on the board             */
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

#include <MKL25Z4.h>
#include "SevenSeg.h"
#include "util.h"
#include <math.h>

/* ************************************************ */
/* Method name:        sevenSegInit                 */
/* Method description: This method initialize the   */
/* Ports for the 7 segments display. It set this    */
/* pins as GPIO and as digital outputs.             */
/*                                                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void sevenSegInit(void){
	/* un-gate port clock */
	SIM_SCGC5 = SIM_SCGC5_PORTC(0x01);
	/* set pin as gpio */
	PORTC_PCR0 = PORT_PCR_MUX(0x01);
	PORTC_PCR1 = PORT_PCR_MUX(0x01);
	PORTC_PCR2 = PORT_PCR_MUX(0x01);
	PORTC_PCR3 = PORT_PCR_MUX(0x01);
	PORTC_PCR4 = PORT_PCR_MUX(0x01);
	PORTC_PCR5 = PORT_PCR_MUX(0x01);
	PORTC_PCR6 = PORT_PCR_MUX(0x01);
	PORTC_PCR7 = PORT_PCR_MUX(0x01);

	PORTC_PCR10 = PORT_PCR_MUX(0x01);
	PORTC_PCR11 = PORT_PCR_MUX(0x01);
	PORTC_PCR12 = PORT_PCR_MUX(0x01);
	PORTC_PCR13 = PORT_PCR_MUX(0x01);

	/* set pin as digital output */
	GPIOC_PDDR = GPIO_PDDR_PDD(0b11110011111111);
	GPIOC_PCOR = GPIO_PCOR_PTCO(0b11110011111111);
}

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
void showValues(int iD3, int iD2, int iD1, int iD0){

	int iDisp[4] = {iD0, iD1, iD2, iD3};
	// Turn on the right value on the display
	for (int iI = 0; iI < 4; iI++){
		switch(iDisp[iI]){
			case 0:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000000111111 + (pow(2, iI))*0b00010000000000);
				break;
			case 1:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000000000110 + (pow(2, iI))*0b00010000000000);
				break;
			case 2:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001011011 + (pow(2, iI))*0b00010000000000);
				break;
			case 3:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001001111 + (pow(2, iI))*0b00010000000000);
				break;
			case 4:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001100110 + (pow(2, iI))*0b00010000000000);
				break;
			case 5:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001101101 + (pow(2, iI))*0b00010000000000);
				break;
			case 6:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001111101 + (pow(2, iI))*0b00010000000000);
				break;
			case 7:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000000000111 + (pow(2, iI))*0b00010000000000);
				break;
			case 8:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001111111 + (pow(2, iI))*0b00010000000000);
				break;
			case 9:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000001101111 + (pow(2, iI))*0b00010000000000);
				break;
			case 10:
				GPIOC_PSOR = GPIO_PSOR_PTSO(0b00000000000000 + (pow(2, iI))*0b00010000000000);
				break;
		}

		// Add delay to show the value before clear
		util_genDelay1ms();
		util_genDelay1ms();
		util_genDelay1ms();
		util_genDelay1ms();
		GPIOC_PCOR = GPIO_PCOR_PTCO(0b11110000000000);
		util_genDelay088us();
		GPIOC_PCOR = GPIO_PCOR_PTCO(0b00000001111111);
	}
}
