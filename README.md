# SAML21_ADC_DAC_DMA Example
Simple example that mirrors ADC values to DAC using DMA

## What the application does

Application reads the signal on the ADC pin and replicates the same signal on the DAC Channel 0 Output.

## Testing

DAC PIN = PA02		
ADC PIN = PA04
Put a analog signal in ADC pin and you should see the same signal in the DAC pin.

## How the example works

 + Application sets up ADC and DAC peripherals with 1V internal bandgap reference.
 + The ADC pin PA04 and DAC pin PA02 are muxed to the respective functions
 + DMA is setup to trigger from ADC result ready event
 + Once ADC has a result, DMA is triggered and data from ADC result register to DAC DATA register
 + Once DAC data register has a value, it converts it to a analog value
 + DAC descriptor is looped onto itself, so it runs forever

## Waveform Generator Set to generate 1KHz 1V p-p waveform
![alt text](https://github.com/adithyayuri/SAML21_ADC_DAC_DMA/blob/main/Images/wave_gen.png "L21 ADC IN")

## Oscilloscope connected to DAC Channel 0 "PA02" pin
![alt text](https://github.com/adithyayuri/SAML21_ADC_DAC_DMA/blob/main/Images/scope.png "L21 DAC OUT")

## Digilent Waveforms 2 hardware connected to SAM L21 Xplained pro
![alt text](https://github.com/adithyayuri/SAML21_ADC_DAC_DMA/blob/main/Images/l21_analog_discovery.jpg "L21 Analog Discovery 2")
