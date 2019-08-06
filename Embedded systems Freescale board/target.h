/* ***************************************************************** */
/* File name:        target.h                                        */
/* File description: Header file containing the function/methods     */
/*                   prototypes of target.c                          */
/*                                                                   */
/* Author name:      Breno Vicente de Cerqueira                      */
/*                   Pedro Jairo Nogueira Pinheiro Neto              */
/*                   Matheus Gustavo Alves Sasso                     */
/* Creation date:    05apr2019                                       */
/* Revision date:    05jun2019                                       */
/* ***************************************************************** */

#ifndef TARGET_H
#define TARGET_H

/* ************************************************ */
/* Method name:        targetInit                   */
/* Method description: This method initialize the   */
/* target.                                          */
/*                                                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void targetInit(void);
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
void respondToHost(int *iD3, int *iD2, int *iD1, int *iD0, int *iStatus, char *cCommand, int *iIndex, int *iIndex2, int *iShowNames, int *iShowSpeed,int *iShowB,int *iShowTemp,int *iShowDC, int *iShowSetPoint, int *iShowPID, int *iIntError);

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
void sendResponse(int iAck, int *iStatus);

#endif /* TARGET_H */
