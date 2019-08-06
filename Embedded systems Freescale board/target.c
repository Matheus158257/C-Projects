/* ***************************************************************** */
/* File name:        target.c                                        */
/* File description: This file has some useful functions to          */
/*                   treat the information received by target        */
/*                   and respond correctly to the Host.              */
/*                                                                   */
/*                   Remarks:  	 					                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    05apr2019                                       */
/* Revision date:    05jun2019                                       */
/* ***************************************************************** */

#include <MKL25Z4.h>
#include "util.h"
#include "debugUart.h"
#include "print_scan.h"
#include "fsl_debug_console.h"
#include "ledswi_hal.h"
#include "target.h"
#include "lcd.h"
#include <stdlib.h>

/* ************************************************ */
/* Method name:        targetInit                   */
/* Method description: This method initialize the   */
/* target.                                          */
/*                                                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void targetInit(void){
	debugUart_init();
}

/* ***************************************************************/
/* Method name:        respondToHost                			 */
/* Method description: This method treats the infor-			 */
/* mation sent to the Target and performs the       			 */
/* actions related to the LED 4 and  to the push   				 */
/* button 3, LCD and and 7 segments.                			 */
/*                                                  			 */
/* Input params: Four integers.                    				 */
/* iD3 = Value to be shown in display 1 (DS1)      				 */
/* iD2 = Value to be shown in display 2 (DS2)      				 */
/* iD1 = Value to be shown in display 3 (DS3)      				 */
/* iD0 = Value to be shown in display 4 (DS4)      				 */
/* iStatus = Push button 3 status                  				 */
/* cCommand = command to be checked                				 */
/* iIndex = Instant size of the command            				 */
/* iIndex2 = Position to be written in the LCD      			 */
/* iShowNames = Turn on LCD with names              		     */
/* iShowSpeed = Turn on the LCD with speed         				 */
/* iShowB = Turn on LCD with with speed and temp   				 */
/* iShowTemp = Turn on LCD with heater duty cycle  			     */
/* iShowDC = Turn on the LCD with duty cycle   					 */
/*iShowSetPoint = Turn on LCD with setpoindt        			 */
/*iShowPID = Turn on LCD with PID gains              			 */
/*iIntError = Set the integrative error to zero when temp is set */
/* Output params:      n/a                          			 */
/* ************************************************************* */
void respondToHost(int *iD3, int *iD2, int *iD1, int *iD0, int *iStatus, char *cCommand, int *iIndex, int *iIndex2, int *iShowNames, int *iShowSpeed,int *iShowB,int *iShowTemp,int *iShowDC, int *iShowSetPoint, int *iShowPID, int *iIntError){

	int iAck = 2;
	char iC;

	// This sequence of if and else is used to find out which command was written
	if (cCommand[0] == 'L' && *iIndex>0){
	    if (cCommand[1] =='S' && *iIndex>1){
	    	if (cCommand[2] =='4'  && *iIndex>2){ // If it found LS4
	    		iAck = 1;
	    		ledswi_setLed(4u); // Turn on the led 4
	    	}
	    	else if(*iIndex>2)
	    	{
	    		iAck = 0;
	    	}
	    }
	    else if (cCommand[1] =='C' && *iIndex>1){
	    	if (cCommand[2] =='4'  && *iIndex>2){ // If it found LC4
	    		iAck = 1;
	    		ledswi_clearLed(4u); // Turn off the led 4
	    	}
	    	else if(cCommand[2] =='D'  && *iIndex>2)
	    	{
	    		if (cCommand[3] =='O'  && *iIndex>3)
	    		{
	    			if (cCommand[4] =='N'  && *iIndex>4) // If it found LCDON
	    			{
	    				iAck =1;
	    				*iShowSpeed = 0; //Indicates that the cooler velocity should no longer be displayed.
	    				*iShowDC = 0;
	    				*iShowTemp = 0;
	    				*iShowB = 0;
	    				*iShowSetPoint = 0;
	    				*iShowPID = 0;
	    				clearLcd(iIndex2);
	    				*iShowNames = 1; // Indicates that it should write on the LCD - This will be updated on main
	    			}
	    			else if(cCommand[4] =='F'  && *iIndex>4)
	    			{
	    				if (cCommand[5] =='F'  && *iIndex>5) // If it found LCDOFF
	    				{
	    					iAck =1;
	    					*iShowSpeed = 0; //Indicates that the cooler velocity should no longer be displayed.
	    					*iShowDC = 0;
	    					*iShowNames = 0; // Indicates that it should clean the lcd
	    					*iShowTemp = 0;
		    				*iShowB = 0;
		    				*iShowSetPoint = 0;
		    				*iShowPID = 0;
	    					clearLcd(iIndex2);
	    				}
	    				else if(*iIndex>5)
	    				{
	    					iAck = 0;
	    				}
	    			}
	    			else if(*iIndex>4)
	    			{
	    				iAck = 0;
	    			}
	    		}
	    		else if(*iIndex>3)
	    		{
	    			iAck = 0;
	    		}
	    	}
	    	else if(*iIndex>2)
	    	{
	    		iAck = 0;
	    	}
	    }
	    else if(*iIndex>1)
    	{
    		iAck = 0;
    	}
	}
	else if(cCommand[0] == 'S' && *iIndex>0){
	    if(cCommand[1] == '3' && *iIndex>1){ // If it found S3
	    	iAck = 1;
	    	*iStatus = ledswi_getSwitchStatus(3u); // Take the status of switch 3
	    }
	    else if(cCommand[1] == 'S' && *iIndex>1){
	    	if(cCommand[2] >= '0' &&  cCommand[2] <= '1' && *iIndex>2){
	    		if(cCommand[3] == '0' ||  (cCommand[3] >= '0' && cCommand[3] <= '9' && *iIndex>3 && cCommand[2] == '0')){
	    			if(cCommand[4] == '0' ||  (cCommand[4] >= '0' && cCommand[4] <= '9' && *iIndex>4 && cCommand[2] == '0')){ //Changes the duty cycle of the cooler.
	    				iAck = 1;
	    				char cDuty_cycle[3] = {cCommand[2], cCommand[3], cCommand[4]};
	    				int iDuty_cycle = atoi(cDuty_cycle);
	    				iDuty_cycle = 255*iDuty_cycle/100;
	    				TPM1_C1V = TPM_CnV_VAL(iDuty_cycle);

	    				*iShowNames = 0; // Indicates that it should clean the lcd
	    				*iShowSpeed = 0;
	    				*iShowTemp = 0;
	    				*iShowB = 0;
	    				*iShowSetPoint = 0;
	    				*iShowPID = 0;
	    				clearLcd(iIndex2);
	    				*iShowDC = 1; //Indicates that the cooler duty cycle must be displayed.
	    			}
	    			else if(*iIndex>4)
	    			{
	    				iAck = 0;
	    			}
	    		}
	    		else if(*iIndex>3)
	    		{
	    			iAck = 0;
	    		}
	    	}
	    	else if(*iIndex>2)
	    	{
	    		iAck = 0;
	    	}
	    }
	    else if(*iIndex>1)
    	{
    		iAck = 0;
    	}
	}
	else if(cCommand[0] == 'H' && *iIndex>0){
		if(cCommand[1] == 'C' && *iIndex>1){
			iAck = 1;
			*iShowNames = 0; // Indicates that it should clean the lcd
			*iShowSpeed = 0;
			*iShowDC = 0;
			*iShowTemp = 0;
			*iShowSetPoint = 0;
			*iShowPID = 0;
			clearLcd(iIndex2);
			*iShowB = 1; // Indicates that both speed and temperature must be displayed on the LCD.
		}

		else if(cCommand[1] == 'S' && *iIndex>1){
	    	if(cCommand[2] >= '0' &&  cCommand[2] <= '1' && *iIndex>2){
	    		if(cCommand[3] == '0' ||  (cCommand[3] >= '0' && cCommand[3] <= '9' && *iIndex>3 && cCommand[2] == '0')){
	    			if(cCommand[4] == '0' ||  (cCommand[4] >= '0' && cCommand[4] <= '9' && *iIndex>4 && cCommand[2] == '0')){
	    				iAck = 1;
	    				char cDuty_cycle[3] = {cCommand[2], cCommand[3], cCommand[4]};
	    				int iDuty_cycle = atoi(cDuty_cycle);
	    				iDuty_cycle = 255*iDuty_cycle/100;
	    				TPM1_C0V = TPM_CnV_VAL(iDuty_cycle);

	    				*iShowNames = 0; // Indicates that it should clean the lcd
	    				*iShowSpeed = 0;
						*iShowDC = 0;
	    				*iShowB = 0;
	    				*iShowSetPoint = 0;
	    				*iShowPID = 0;
	    				clearLcd(iIndex2);
	    				*iShowTemp = 1; //Indicates that the heater duty cycle must be displayed.
						
	    			}
	    			else if(*iIndex>4)
	    			{
	    				iAck = 0;
	    			}
	    		}
	    		else if(*iIndex>3)
	    		{
	    			iAck = 0;
	    		}
	    	}
	    	else if(*iIndex>2)
	    	{
	    		iAck = 0;
	    	}
	    }
	    else if(*iIndex>1)
    	{
    		iAck = 0;
    	}
	}
	else if(cCommand[0] == 'D' && *iIndex>0){
	    iC = cCommand[1];
	    if((iC == '1' || iC == '2' || iC == '3' || iC == '4') && *iIndex>1){
	    	char M = iC;
	    	iC = cCommand[2];
	    	switch(M){ // If it found D[1-4][0-9], it should write the value on the correct display
	    		case '1':
	    			if(iC == 'C' &&  *iIndex>2){
	    				iAck = 1;
	    				*iD3 = 10;
	    			}
	    			else if((iC == '0' || iC == '1' || iC == '2' || iC == '3' || iC == '4' || iC == '5' || iC == '6' || iC == '7' || iC == '8' || iC == '9')&&  *iIndex>2){
	    				iAck = 1;
	    				*iD3 = (iC -'0');
	    			}
	    			else if(*iIndex>2)
	    	    	{
	    	    		iAck = 0;
	    	    	}
	    			break;
	    					
	    		case '2':
	    			if(iC == 'C' &&  *iIndex>2){
	    				iAck = 1;
	    				*iD2 = 10;
	    			}
	    			else if((iC == '0' || iC == '1' || iC == '2' || iC == '3' || iC == '4' || iC == '5' || iC == '6' || iC == '7' || iC == '8' || iC == '9')&&  *iIndex>2){
	    				iAck = 1;
	    				*iD2 = (iC -'0');
	    			}
	    			else if(*iIndex>2)
	    	    	{
	    	    		iAck = 0;
	    	    	}
	    			break;
	    					
	    		case '3':
	    			if(iC == 'C' &&  *iIndex>2){
	    				iAck = 1;
	    				*iD1 = 10;
	    			}
	    			else if((iC == '0' || iC == '1' || iC == '2' || iC == '3' || iC == '4' || iC == '5' || iC == '6' || iC == '7' || iC == '8' || iC == '9')&&  *iIndex>2){
	    				iAck = 1;
	    				*iD1 = (iC -'0');
	    			}
	    			else if(*iIndex>2)
	    	    	{
	    	    		iAck = 0;
	    	    	}
	    			break;
	    					
	    		case '4':
	    			if(iC == 'C' &&  *iIndex>2){
	    				iAck = 1;
	    				*iD0 = 10;
	    			}
	    			else if((iC == '0' || iC == '1' || iC == '2' || iC == '3' || iC == '4' || iC == '5' || iC == '6' || iC == '7' || iC == '8' || iC == '9')&&  *iIndex>2){
	    				iAck = 1;
	    				*iD0 = (iC -'0');
	    			}
	    			else if(*iIndex>2)
	    	    	{
	    	    		iAck = 0;
	    	    	}
	    			break;
	    	}
	    }
    	else if(*iIndex>1)
    	{
    		iAck = 0;
    	}
	}
	else if(cCommand[0] == 'C' && *iIndex>0){
		if(cCommand[1] == 'S' && *iIndex>1){ // If it found S3
			iAck = 1;
			*iShowNames = 0; // Indicates that it should clean the lcd
			*iShowDC = 0;
			*iShowB = 0;
			*iShowTemp = 0;
			*iShowSetPoint = 0;
			*iShowPID = 0;
			clearLcd(iIndex2);
			*iShowSpeed = 1; //Indicates that the cooler velocity must be displayed.
		}
		else if(*iIndex>1)
		{
			iAck = 0;
	    }
	}
	else if(cCommand[0] == 'T' && *iIndex>0){
		if(cCommand[1] == 'E' && *iIndex>1){
			if(cCommand[2] == 'M' && *iIndex>2){
				if(cCommand[3] == 'P' && *iIndex>3){
					if(cCommand[4] >= '3' &&  cCommand[4] <= '4' && *iIndex>4){
						if(cCommand[5] == '0' ||  (cCommand[5] >= '0' && cCommand[5] <= '9' && *iIndex>5 && cCommand[4] == '3')){
							iAck = 1;

							*iShowNames = 0; // Indicates that it should clean the lcd
							*iShowSpeed = 0;
							*iShowDC = 0;
							*iShowB = 0;
							*iShowTemp = 0; //Indicates that the heater duty cycle must be displayed.
							*iShowPID = 0;
							clearLcd(iIndex2);
							*iShowSetPoint = 1;
							*iIntError = 0; //Sets the int error to zero when the temparature is set

						}
						else if(*iIndex>5)
						{
							iAck = 0;
						}
					}
					else if(*iIndex>4)
					{
						iAck = 0;
					}
				}
				else if(*iIndex>3)
				{
					iAck = 0;
				}
			}
			else if(*iIndex>2)
			{
				iAck = 0;
			}
		}
		else if(*iIndex>1)
		{
			iAck = 0;
	    }
	}
	else if(cCommand[0] == 'P' && *iIndex>0){
		if(cCommand[1] >= '0' && cCommand[1] <= '9' && *iIndex>1){
			if(cCommand[2] >= '0' && cCommand[2] <= '9' && *iIndex>2){
				if(cCommand[3] == 'I' && *iIndex>3){
					if(cCommand[4] >= '0' && cCommand[4] <= '9' && *iIndex>4){
						if(cCommand[5] >= '0' && cCommand[5] <= '9' && *iIndex>5){
							if(cCommand[6] == 'D' && *iIndex>6){
								if(cCommand[7] >= '0' && cCommand[7] <= '9' && *iIndex>7){
									if(cCommand[8] >= '0' && cCommand[8] <= '9' && *iIndex>8){
										iAck = 1;

										*iShowNames = 0; // Indicates that it should clean the lcd
										*iShowSpeed = 0;
										*iShowDC = 0;
										*iShowB = 0;
										*iShowTemp = 0; //Indicates that the heater duty cycle must be displayed.
										*iShowSetPoint = 0;
										clearLcd(iIndex2);
										*iShowPID = 1;//Shows the message to get the PID gains

									}
									else if(*iIndex>8)
									{
										iAck = 0;
									}
								}
								else if(*iIndex>7)
								{
									iAck = 0;
								}
							}
							else if(*iIndex>6)
							{
								iAck = 0;
							}
						}
						else if(*iIndex>5)
						{
							iAck = 0;
						}
					}
					else if(*iIndex>4)
					{
						iAck = 0;
					}
				}
				else if(*iIndex>3)
				{
					iAck = 0;
				}
			}
			else if(*iIndex>2)
			{
				iAck = 0;
			}
		}
		else if(*iIndex>1)
		{
			iAck = 0;
		}
	}
	else if(*iIndex>0) // If it found an error
	{
		iAck = 0; // Show ERR message
	}
	
	if (iAck == 0 || iAck == 1){
		*iIndex = 0;
		sendResponse(iAck, iStatus);
	}
}

/* ************************************************ */
/* Method name:        sendResponse                 */
/* Method description: This method sends the appro- */
/* priate response to the Host.                     */
/*                                                  */
/* Input params: 2 integers                         */
/* iAck = If the command is valid                   */
/* iStatus = Status of the push button 3            */
/* Output params:      n/a                          */
/* ************************************************ */
void sendResponse(int iAck, int *iStatus){
	if (iAck == 1){
    	PUTCHAR('A');
    	PUTCHAR('C');
    	PUTCHAR('K');
    		
    	if (*iStatus == 0){
    		PUTCHAR('O');
    		PUTCHAR('F');
    		PUTCHAR('F');
    		*iStatus = 2;
    	}
    	else if (*iStatus == 1){
    		PUTCHAR('O');
    		PUTCHAR('N');
    		*iStatus = 2;
    	}
    }
    else{
    	PUTCHAR('E');
    	PUTCHAR('R');
    	PUTCHAR('R');
    }
	PUTCHAR(' ');
}
