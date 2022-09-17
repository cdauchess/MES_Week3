
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"


typedef enum{
    Blinking,
    NoBlink
}   LED_STATE;


void LED_ON();
void LED_OFF();
void LED_INIT();
void BUTTON_INIT();