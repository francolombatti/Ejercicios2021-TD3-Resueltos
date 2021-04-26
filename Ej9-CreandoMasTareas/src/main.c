#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define PULSADOR    GPIO_NUM_18
#define SALIDA1     GPIO_NUM_25
#define SALIDA2     GPIO_NUM_26
#define SALIDA3     GPIO_NUM_27
#define PROCESADORA 0
#define PROCESADORB 1
#define RETARDO_US  1
#define RETARDO_MS  1/pdMS_TO_TICKS

void tareaDos( void * pvParameters ); //Prototipo de la tarea
void tareaTres( void * pvParameters );

void app_main() 
{
    UBaseType_t prioridad = uxTaskPriorityGet (NULL);   //para obtener la prioridad de la tarea principal
    printf("%d/n",prioridad);   //debería ser 1

    TaskHandle_t xHandle2 = NULL;            //Puntero a la tarea
    TaskHandle_t xHandle3 = NULL;            //Puntero a la tarea

    xTaskCreatePinnedToCore( tareaDos,      //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea dos",               //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+1,        //Prioridad de la tarea
                 &xHandle2,                 //Puntero a la tarea
                 PROCESADORB                //Procesador donde se ejecuta la tarea
                );
    configASSERT( xHandle2 );                //entra si no se pudieron crear las tareas, para debug

    xTaskCreatePinnedToCore( tareaTres,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea tres",               //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY,          //Prioridad de la tarea
                 &xHandle3,                 //Puntero a la tarea
                 PROCESADORB                //Procesador donde se ejecuta la tarea
                );
    configASSERT( xHandle3 );                //entra si no se pudieron crear las tareas, para debug

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
            if( xHandle2 != NULL )
            {
            vTaskDelete( xHandle2 );
            }
        }
        gpio_set_level(SALIDA1, 1);
        ets_delay_us(RETARDO_US);
        gpio_set_level(SALIDA1,0);
        ets_delay_us(RETARDO_US);
    }
}

//Definición de la tarea
void tareaDos( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);
    while (true)
    {
        gpio_set_level(SALIDA2, 1);
        ets_delay_us(RETARDO_US); // probar con vTaskDelay(RETARDO_MS);
        gpio_set_level(SALIDA2,0);
        ets_delay_us(RETARDO_US); // probar con vTaskDelay(RETARDO_MS);
    }
}

void tareaTres( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA3);
    gpio_set_direction(SALIDA3, GPIO_MODE_OUTPUT);
    while (true)
    {
        gpio_set_level(SALIDA3, 1);
        ets_delay_us(RETARDO_US); // probar con vTaskDelay(RETARDO_MS);
        gpio_set_level(SALIDA3,0);
        ets_delay_us(RETARDO_US); // probar con vTaskDelay(RETARDO_MS);
    }
}