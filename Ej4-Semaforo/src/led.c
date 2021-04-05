#include "../include/led.h"

//void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV)
void configurarLed()
{
    gpio_pad_select_gpio(ROJO);
    gpio_set_direction(ROJO, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(AMARILLO);
    gpio_set_direction(AMARILLO, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(VERDE);
    gpio_set_direction(VERDE, GPIO_MODE_OUTPUT);
}

void prenderLed(gpio_int_type_t led)
{
    gpio_set_level(led, 1);
}

void apagarLed(gpio_int_type_t led)
{
    gpio_set_level(led, 0);

}