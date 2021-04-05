#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"

void app_main()
{
    configurarLed();
    iniciarSemaforo();

    while(1)
    {
        actualizarSemaforo();
    }
}