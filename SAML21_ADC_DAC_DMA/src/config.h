/*
 * config.h
 *
 * Created: 22-02-2021 07:53:33 PM
 *  Author: YURI
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <asf.h>

// Setup ADC instance
struct adc_module app_adc;

// Setup DAC instance
struct dac_module app_dac;

// Setup DMA instance
struct dma_resource app_dma;

void conf_ADC(void);
void conf_DAC(void);
void conf_DMA(void);
void conf_pinmux(void);
void setup_transfer_descriptor(DmacDescriptor *descriptor);
void conf_dma_resource(struct dma_resource *resource);

#endif /* CONFIG_H_ */