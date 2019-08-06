/* ***************************************************************** */
/* File name:        aquecedor.c                                     */
/* File description: This file has a couple of useful functions to   */
/*                   use the heater                                  */
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
#include <MKL25Z4.h>

#define CGC_CLOCK_ENABLED 0x01U


/* ******************************************************** */
/* Method name: aquecedor_init                              */
/* Method description: Initialize the heater                */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void aquecedor_init(void){
	/* turn on fan */
	/* un-gate port clock */
	SIM_SCGC5 |= SIM_SCGC5_PORTA(0x01);
	/* set pin as gpio */
	PORTA_PCR12 |= PORT_PCR_MUX(0x01);
	/* set pin as digital output */
	GPIOA_PDDR |= GPIO_PDDR_PDD(0b01 << 13);
	/* set desired pin */
	GPIOA_PSOR = GPIO_PSOR_PTSO(0b01 << 13);
}


/* ******************************************************** */
/* Method name: PWM_aquecedor_init                          */
/* Method description: Initialize the PWM pulse for the     */
/* heater.   											 	*/
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void PWM_aquecedor_init(void){
	/* turn on fan */
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); // Un-gate TPM1 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED); // Un-gate PORTA clock
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10); // Select TPM Source OSCERCLK clock
	PORTA_PCR12 |= PORT_PCR_MUX(0b011); // Configure PTA13 as TPM1_CH1
	TPM1_SC &= ~TPM_SC_CPWMS(1); // Increase counting
	TPM1_SC |= TPM_SC_CMOD(0b01) | TPM_SC_PS(0b000); // LPTPM increments on every clock & preescaler = 1
	TPM1_CNT = 0; // Reset counter
	TPM1_MOD = TPM_MOD_MOD(0xFF); // Cycle period
	
	TPM1_C0SC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1); // Edge-aligned PWM
	TPM1_C0SC &= ~(TPM_CnSC_MSA(1) | TPM_CnSC_ELSA(1)); // Edge-aligned PWM
	TPM1_C0V = TPM_CnV_VAL(0x00); // Duty cycle 0%
}

/* ******************************************************** */
/* Method name: activate_CAD                                */
/* Method description: Set registers for Analog to digital  */
/* convertion            									*/
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void activate_CAD(void){
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED); // Un-gate CAD conversor
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED); // Un-gate PORTE clock
	PORTE_PCR21 &= ~PORT_PCR_MUX(0b111); // Configure pin 21 as analog input.
	ADC0_CFG1 &= ~ADC_CFG1_MODE(0b11);
	ADC0_SC2 &= ~ADC_SC2_ADTRG(0b1);
	ADC0_SC3 |= ADC_SC3_AVGE(0b1);
	ADC0_SC3 &= ~ADC_SC3_AVGS(0b11);
	ADC0_SC3 &= ~ADC_SC3_ADCO(0b1);
}

/* ******************************************************** */
/* Method name: start_CAD                                   */
/* Method description: Start one analog digital conversion  */
/* Input params: n/a                                        */
/* Output params: n/a                                       */
/* ******************************************************** */
void start_CAD(void){
	ADC0_SC1A &= ~ADC_SC1_DIFF(0b1);
	ADC0_SC1A &= ~ADC_SC1_ADCH(0b11011);
	ADC0_SC1A |= ADC_SC1_AIEN(0b1);
}
