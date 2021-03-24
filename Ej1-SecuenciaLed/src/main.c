/*=============================================================================
 * Author: Fernando Ezequiel Daniele <fernandodaniele1993@gmai.com>
 * Date: 2021/03/17 
 *===========================================================================*/
#include "../driver/include/driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define N_LED 		3
#define N_PULSADOR 	2
#define T_ON		500/portTICK_PERIOD_MS

int led [N_LED] = {GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_25};
int pulsador [N_PULSADOR] = {GPIO_NUM_26, GPIO_NUM_27};

void app_main()
{
	//Configuración
	for(int i = 0; i < N_LED; i++){
		gpio_pad_select_gpio(led[i]);
		gpio_set_direction(led[i], GPIO_MODE_OUTPUT);
	}
	
	for(int i = 0; i < N_PULSADOR; i++){
		gpio_pad_select_gpio(pulsador[i]);
		gpio_set_direction(pulsador[i], GPIO_MODE_INPUT);
		gpio_set_pull_mode(pulsador[i], GPIO_PULLDOWN_ONLY);
	}

   int i = 0, sentido = 0;
   //Bucle infinito
   while( true )
    {
		if (gpio_get_level(pulsador[0]) == 1)
		{
			sentido = 1;
		}
	   	else if (gpio_get_level(pulsador[1]) == 1)
		{
			sentido = 0;
		}	

	   	if (sentido == 0)
		{
			gpio_set_level(led[i], 0);
			i++;
			if ( i >= N_LED ){
				i = 0;
			}
			gpio_set_level(led[i], 1);
		}
	   	else 
		{
			gpio_set_level(led[i], 0);
			i--;
			if ( i < 0 ){
				i = N_LED;
			}
			gpio_set_level(led[i], 1);
		}
		vTaskDelay(T_ON);	
	}
   return 0;
}


/*
#define LED1 GPIO_NUM_32 //ver de crear un tipo de datos
#define LED2 GPIO_NUM_33
#define LED3 GPIO_NUM_25
#define PULSADOR1 GPIO_NUM_26
#define PULSADOR2 GPIO_NUM_27
#define T_ON		500/portTICK_PERIOD_MS

void app_main()
{
	//Configuración
	gpio_pad_select_gpio(LED1);
	gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED2);
	gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED3);
	gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(PULSADOR1);
	gpio_set_direction(PULSADOR1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(PULSADOR2);
	gpio_set_direction(PULSADOR2, GPIO_MODE_INPUT);

   int i = 0;
   unsigned int sentido = 0;
   // ----- Repeat for ever -------------------------
   while( true )
    {
	   	if (gpio_get_level(PULSADOR1) == 0)
		{
			sentido = 1;
		}
	   	else if (gpio_get_level(PULSADOR2) == 0)
		{
			sentido = 0;
		}

		if ( i == 0 ){
			gpio_set_level(LED1, 1);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 0);
		}
		if ( i == 1 ){
			gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 1);
			gpio_set_level(LED3, 0);
		}
		if ( i == 2 ){
			gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 1);
		}

		if(sentido == 0){
			i++;
		}
		else{
			i--;
		}

		if ( i < 0 ){
		i = 2;
		}
		if ( i > 2 ){
		i = 0;
		}
		vTaskDelay(T_ON);
	}
   return 0;
}
*/