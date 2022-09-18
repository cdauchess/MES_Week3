
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/clocks.h"


//Previous edge on interrupt
#define RISING_EDGE 1
#define FALLING_EDGE 2
//Current LED State
#define ON 1
#define OFF 0



typedef enum{
    Blinking,
    NoBlink
}   LED_STATE;


void LED_ON();
void LED_OFF();
void LED_INIT();
void BUTTON_INIT();
uint Toggle_LED(LED_STATE currentState);