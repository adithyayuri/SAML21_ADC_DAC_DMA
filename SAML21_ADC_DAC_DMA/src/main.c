#include <asf.h>
#include "config.h"

extern struct adc_module app_adc;
extern struct dac_module app_dac;

void config_app(void){
	conf_ADC();
	conf_DAC();
	conf_pinmux();
}

int main (void)
{
	system_init();
	config_app();

	// ADC result variable
	uint16_t adc_result;
	
	while (1) {
		do {
			// Wait for ADC result
		} while (adc_read(&app_adc, &adc_result) == STATUS_BUSY);
		dac_chan_write(&app_dac, DAC_CHANNEL_0, adc_result);
	}
}
