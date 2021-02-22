/*
 * config.c
 *
 * Created: 22-02-2021 07:53:12 PM
 *  Author: YURI
 */ 

#include "config.h"

// Setup DMAC descriptor instance
COMPILER_ALIGNED(16)
DmacDescriptor adc_dac_dmac SECTION_DMAC_DESCRIPTOR;

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


void conf_dma_resource(struct dma_resource *resource)
{
	// DMA resource config structure
	struct dma_resource_config config;
	// Load default values
	dma_get_config_defaults(&config);
	// Set ADC result ready as trigger for DMA
	config.peripheral_trigger = ADC_DMAC_ID_RESRDY;
	// On trigger do a beat action
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	// Allocate DMA resource 
	dma_allocate(resource, &config);
}

void setup_transfer_descriptor(DmacDescriptor *descriptor)
{
	// Struct for DMA descriptor configuration
	struct dma_descriptor_config descriptor_config;

	dma_descriptor_get_config_defaults(&descriptor_config);
	// 16 bit transfer size on trigger
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.src_increment_enable = false;
	// Max count for block transfer count
	descriptor_config.block_transfer_count = 0xFFFF;
	// Source is ADC result register
	descriptor_config.source_address = (uint32_t)(&app_adc.hw->RESULT.reg);
	// Destination is DAC channel 0 data register
	descriptor_config.destination_address = (uint32_t)(&app_dac.hw->DATA[DAC_CHANNEL_0].reg);
	descriptor_config.next_descriptor_address = (uint32_t)descriptor;
	
	// Create descriptor
	dma_descriptor_create(descriptor, &descriptor_config);
}

void conf_DMA(void){
	// Confif DMA resource
	conf_dma_resource(&app_dma);
	// Setup DMA to do transfer between DAC and ADC
	setup_transfer_descriptor(&adc_dac_dmac);
	// Add descriptor 
	dma_add_descriptor(&app_dma, &adc_dac_dmac);	
}