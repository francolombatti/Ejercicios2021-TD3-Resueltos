#ifndef LED_H //chequea que otro archivo no haya llamado a led.h
#define LED_H
#include "driver/gpio.h"

#define VERDE GPIO_NUM_25
#define AMARILLO GPIO_NUM_32
#define ROJO GPIO_NUM_26

//void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV); //especifica en que pines conectar cada led: ROJO, AMARILLO, VERDE
void configurarLed();

void prenderLed(gpio_int_type_t led);

void apagarLed(gpio_int_type_t led);

#endif