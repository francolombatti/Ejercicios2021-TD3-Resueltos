#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void iniciarSemaforo()
{

}

void actualizarSemaforo()
{
    prenderLed(ROJO);
    vTaskDelay(30);
    prenderLed(AMARILLO);
    vTaskDelay(10);
    apagarLed(ROJO);
    apagarLed(AMARILLO);
    prenderLed(VERDE);
    vTaskDelay(10);
    apagarLed(VERDE);
    prenderLed(AMARILLO);
    vTaskDelay(5);
    apagarLed(AMARILLO);
}