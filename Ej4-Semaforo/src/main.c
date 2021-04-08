#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"

void app_main()
{
    iniciarSemaforo();

    while(1)
    {
        actualizarSemaforo();
    }
}