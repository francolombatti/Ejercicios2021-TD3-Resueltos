#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <driver/dac.h>

void app_main()
{
    adc1_config_width(ADC_WIDTH_12Bit); //configuran la resoluncion 
    adc1_config_channel_atten (ADC1_CHANNEL_0 ,ADC_ATTEN_11db);
   
    adc2_config_channel_atten (ADC2_CHANNEL_0, ADC_ATTEN_11db);
    
    dac_output_enable(DAC_CHANNEL_1);

    while(true)
    {
        int lectura = adc1_get_raw(ADC1_CHANNEL_0);
        printf("El valor del ADC1 es %d\n",lectura);

        dac_output_voltage(DAC_CHANNEL_1,(lectura*255/4095)); //0 y 255 DAC -- 8 bit -- va de 0 V a VDA (pin de alimentacion analogico) 
                                                              //0 y 4095 ADC

        int lectura2 = 0;
        adc2_get_raw(ADC2_CHANNEL_0, ADC_WIDTH_12Bit, &lectura2);
        printf("El valor del ADC2 es %d\n", lectura2);

        vTaskDelay(500/portTICK_PERIOD_MS);        
    }

}