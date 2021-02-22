#include <asf.h>
#include "config.h"

/*
 * main.c
 *
 * Created: 22-02-2021 07:53:12 PM
 *  Author: YURI
 *
 * ADC-DAC-DMA Example
 *
 * What the application does
 *		Application reads the signal on the ADC pin and replicates the same signal on the DAC Channel 0 Output.
 *		DAC PIN = PA02		
 *		ADC PIN = PA04
 *		Put a analog signal in ADC pin and you should see the same signal in the DAC pin.
 *
 * How the example works
 *	-> Application sets up ADC and DAC peripherals with 1V internal bandgap reference.
 *	-> The ADC pin PA04 and DAC pin PA02 are muxed to the respective functions
 *	-> DMA is setup to trigger from ADC result ready event
 *	-> Once ADC has a result, DMA is triggered and data from ADC result register to DAC DATA register
 *	-> Once DAC data register has a value, it converts it to a analog value
 *	-> DAC descriptor is looped onto itself, so it runs forever
 */ 

extern struct adc_module app_adc;
extern struct dac_module app_dac;
extern struct dma_resource app_dma;

void config_app(void){
	// Configure ADC
	conf_ADC();
	// Configure DAC
	conf_DAC();
	// Mux ADC and DAC pins to their specific pins
	conf_pinmux();
	// Configure DMA
	conf_DMA();
	// Start DMA Transfer
	dma_start_transfer_job(&app_dma);	
}

int main (void)
{
	system_init();
	config_app();
	while (1) {
	}
}
