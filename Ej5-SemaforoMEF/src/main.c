#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"

#define T 10/portTICK_PERIOD_MS

void app_main()
{
    configurarLed();
    iniciarSemaforo();

    while(1)
    {
        actualizarSemaforo();
        vTaskDelay(T);
    }
}