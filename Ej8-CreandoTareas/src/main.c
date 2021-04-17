#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define PULSADOR    GPIO_NUM_25
#define SALIDA1     GPIO_NUM_26
#define SALIDA2     GPIO_NUM_27
#define RETARDO_US  1

void tareaSecundaria( void * pvParameters ); //Prototipo de la tarea

void app_main() 
{
    TaskHandle_t xHandle1 = NULL;           //Puntero a la tarea

    xTaskCreate( tareaSecundaria,           //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea secundaria",        //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY,          //Prioridad de la tarea
                 &xHandle1                  //Puntero a la tarea
                );
    configASSERT( xHandle1 );                //entra si no se pudieron crear las tareas, para debug

    gpio_pad_select_gpio(PULSADOR);
	gpio_set_direction(PULSADOR, GPIO_MODE_INPUT);
	gpio_set_pull_mode(PULSADOR, GPIO_PULLDOWN_ONLY);
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while(true)
    {
        if (gpio_get_level(PULSADOR))
        {
            //Borra la tarea usando el handle
            if( xHandle1 != NULL )      //Nos aseguramos de que no sea NULL para que no elimine la tarea actual
            {
            vTaskDelete( xHandle1 );    //Elimina la tarea
            xHandle1 = NULL;
            }
        }
        gpio_set_level(SALIDA1, 1);
        ets_delay_us(RETARDO_US);    //delay en microsegundos que bloquea al procesador
        gpio_set_level(SALIDA1, 0);
        ets_delay_us(RETARDO_US);
    }
}

//Definición de la tarea
void tareaSecundaria( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);
    while (true)
    {
        gpio_set_level(SALIDA2, 1);
        ets_delay_us(RETARDO_US);    //delay en microsegundos que bloquea al procesador
        gpio_set_level(SALIDA2,0);
        ets_delay_us(RETARDO_US);
    }
}