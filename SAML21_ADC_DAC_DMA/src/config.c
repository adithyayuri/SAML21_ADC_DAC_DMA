/*
 * config.c
 *
 * Created: 22-02-2021 07:53:12 PM
 *  Author: YURI
 */ 

#include "config.h"

void conf_ADC(void){
	// Config struct for ADC
	struct adc_config config_adc;
	// Get default config for ADC
	adc_get_config_defaults(&config_adc);

	config_adc.clock_source		= GCLK_GENERATOR_0;
	config_adc.resolution		= ADC_RESOLUTION_12BIT;
	config_adc.clock_prescaler	= ADC_CLOCK_PRESCALER_DIV16;
	config_adc.reference		= ADC_REFCTRL_REFSEL_INTREF;
	config_adc.positive_input	= ADC_POSITIVE_INPUT_PIN4;
	config_adc.negative_input	= ADC_NEGATIVE_INPUT_GND;
	config_adc.freerunning		= true;
	config_adc.left_adjust		= false;

	// ADC init
	adc_init(&app_adc, ADC, &config_adc);
	// Enable ADC
	adc_enable(&app_adc);
}

void conf_DAC(void){
	// Config struct for DAC
	struct dac_config config_dac;
	// Config struct for DAC channel 0
	struct dac_chan_config dac_chan0;

	// Get default config for DAC
	dac_get_config_defaults(&config_dac);
	config_dac.reference = DAC_REFERENCE_INTREF;
	// DAC init
	dac_init(&app_dac, DAC, &config_dac);
	
	// Get chanel defaults
	dac_chan_get_config_defaults(&dac_chan0);
	// Configure DAC channel 0
	dac_chan_set_config(&app_dac, DAC_CHANNEL_0, &dac_chan0);
	// Enable DAC channel 0
	dac_chan_enable(&app_dac, DAC_CHANNEL_0);
	// Enable DAC
	dac_enable(&app_dac);
}

void conf_pinmux(void){
	// Struct for pinconf
	struct system_pinmux_config pin_conf;

	// PA02 as DAC0 output
	system_pinmux_get_config_defaults(&pin_conf);
	pin_conf.mux_position = MUX_PA02B_DAC_VOUT0;
	system_pinmux_pin_set_config(PIN_PA02B_DAC_VOUT0, &pin_conf);
	
	// PA04 as ADC[4] input
	system_pinmux_get_config_defaults(&pin_conf);
	pin_conf.mux_position = MUX_PA04B_ADC_AIN4;
	system_pinmux_pin_set_config(PIN_PA04B_ADC_AIN4, &pin_conf);
}