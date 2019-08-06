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
/* Revision date:    19may2019                                       */
/* ***************************************************************** */

#include "tc_hal.h"

#define CGC_CLOCK_ENABLED 0x01U

/* ******************************************************** */
/* Method name: cooler_taco_init                            */
/* Method description: Initialize the cooler tachometer     */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void cooler_taco_init(void){
	
	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED); // Un-gate TPM0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED); // Un-gate PORTE clock
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10); // Select TPM Source OSCERCLK
	
	// clock
	SIM_SOPT4 &= ~SIM_SOPT4_TPM0CLKSEL(1); // Select TPM0 external clock as
	
	// TPM_CLKIN0
	PORTE_PCR29 |= PORT_PCR_MUX(0b100); // Configure PTE29 as TPM_CLKIN0
	TPM0_SC &= ~TPM_SC_CPWMS(1); // Increase counting
	
	/* LPTPM counter increments on rising edge & preescaler = 1 */
	TPM0_SC |= TPM_SC_CMOD(0b10) | TPM_SC_PS(0b000);
	TPM0_CNT = 0; // Reset counter
}

/* ******************************************************** */
/* Method name: cooler_getRPS                               */
/* Method description: Get the cooler speed in RPS          */
/* Input params: uiPeriod in microseconds                   */
/* Output params: uiCount                                   */
/* ******************************************************** */
unsigned int cooler_getRPS(unsigned int uiPeriod){
	unsigned int uiCount = 0;
	
	uiCount = TPM0_CNT; // get counter value
	
	TPM0_CNT = 0; // restart TPM0 counter
	
	uiCount = uiCount*1000000 / (uiPeriod * 7); // compute speed
	
	return uiCount;
}

/* ******************************************************** */
/* Method name: cooler_init                                 */ 
/* Method description: Initialize the cooler                */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void cooler_init(void){
	
	cooler_taco_init();
	
	/* turn on fan */
	/* un-gate port clock */
	SIM_SCGC5 |= SIM_SCGC5_PORTA(0x01);
	/* set pin as gpio */
	PORTA_PCR13 |= PORT_PCR_MUX(0x01);
	/* set pin as digital output */
	GPIOA_PDDR |= GPIO_PDDR_PDD(0b01 << 13);
	/* set desired pin */
	GPIOA_PSOR = GPIO_PSOR_PTSO(0b01 << 13);
}


/* ******************************************************** */
/* Method name: PWM_init                                    */
/* Method description: Initialize the PWM pulse.            */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void PWM_init(void){
	/* turn on fan */
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); // Un-gate TPM1 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED); // Un-gate PORTA clock
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10); // Select TPM Source OSCERCLK clock
	PORTA_PCR13 |= PORT_PCR_MUX(0b011); // Configure PTA13 as TPM1_CH1
	TPM1_SC &= ~TPM_SC_CPWMS(1); // Increase counting
	TPM1_SC |= TPM_SC_CMOD(0b01) | TPM_SC_PS(0b000); // LPTPM increments on every clock & preescaler = 1
	TPM1_CNT = 0; // Reset counter
	TPM1_MOD = TPM_MOD_MOD(0xFF); // Cycle period
	TPM1_C1SC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1); // Edge-aligned PWM
	TPM1_C1SC &= ~(TPM_CnSC_MSA(1) | TPM_CnSC_ELSA(1)); // Edge-aligned PWM
	TPM1_C1V = TPM_CnV_VAL(0x00); // Duty cycle 0%
}

void init_ANC(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED); // Un-gate PORTE clock
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED); // Un-gate ANC clock
	PORTE_PCR21 &= ~PORT_PCR_MUX(0b111);
}
