/*=============================================================================
 * Author: Fernando Ezequiel Daniele <fernandodaniele1993@gmai.com>
 * Date: 2021/03/24 
 *===========================================================================*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define N_LED 		2
#define T_MS		10/portTICK_PERIOD_MS

//Arreglos para facilitar el agregado de leds y pulsadores
int led [N_LED] = {GPIO_NUM_32, GPIO_NUM_33};
int pulsador [N_LED] = {GPIO_NUM_26, GPIO_NUM_27};
unsigned long int contador[N_LED] = { 0, 0}; //almacenan el tiempo

void app_main()
{
	
	//Configuración
	for(int i = 0; i < N_LED; i++){
		gpio_pad_select_gpio(led[i]); //Elige un pin desde el IOMUX
		gpio_set_direction(led[i], GPIO_MODE_OUTPUT); //Configura el pin como salida digital
	}
	
	for(int i = 0; i < N_LED; i++){
		gpio_pad_select_gpio(pulsador[i]);
		gpio_set_direction(pulsador[i], GPIO_MODE_INPUT); //Configura el pin como entrada digital
		gpio_set_pull_mode(pulsador[i], GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna
	}

   //Bucle infinito
   while( true )
    {
		while (gpio_get_level(pulsador[0]) == 1) //Mientras el pulsador esté habilitado, incrementa el contador
		{
			vTaskDelay(T_MS);
			contador[0] += T_MS;
		}
	   	while (gpio_get_level(pulsador[1]) == 1)
		{
			vTaskDelay(T_MS);
			contador[1] += T_MS;
		}	

		//Si algun contador es mayor a 0, habilita el led correspondiente
	   	if (contador[0] >0)
		{
			gpio_set_level(led[0], 1);
			vTaskDelay(contador[0]);
			gpio_set_level(led[0], 0);
            contador[0] = 0;
		}
	   	if (contador[1] >0)
		{
			gpio_set_level(led[1], 1);
			vTaskDelay(contador[1]);
			gpio_set_level(led[1], 0);
            contador[1] = 0;
		}
	}
}