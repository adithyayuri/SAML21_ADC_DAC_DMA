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

void conf_ADC(void);
void conf_DAC(void);
void conf_pinmux(void);

#endif /* CONFIG_H_ */