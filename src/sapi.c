#include "sapi.h"

uint16_t adcRead( adcMap_t analogInput )
{
   uint8_t lpcAdcChannel = (uint8_t)(analogInput + 1);
   uint16_t analogValue = 0;

   // Enable channel
   Chip_ADC_EnableChannel(LPC_ADC0, lpcAdcChannel, ENABLE);

   // Start conversion
   Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

   // Wait for conversion complete
   while(
      (Chip_ADC_ReadStatus(LPC_ADC0, lpcAdcChannel, ADC_DR_DONE_STAT) != SET)
   );

   // Enable Read value
   Chip_ADC_ReadValue( LPC_ADC0, lpcAdcChannel, &analogValue );

   // Disable channel
   Chip_ADC_EnableChannel( LPC_ADC0, lpcAdcChannel, DISABLE );

   return analogValue;
}