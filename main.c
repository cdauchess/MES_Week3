/* 
    This code originates from the Getting started with Raspberry Pi Pico document
    https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
    CC BY-ND Raspberry Pi (Trading) Ltd
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;
typedef enum{
    Blinking,
    NoBlink
}   LED_STATE;



int main() {
    bi_decl(bi_program_description("PROJECT DESCRIPTION"));
    
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    LED_STATE LED = NoBlink;

    while(1) {

        switch(LED)
        {
            case Blinking:
                gpio_put(LED_PIN, 0);
                sleep_ms(250);
                gpio_put(LED_PIN, 1);
                puts("Hello World\n");
                sleep_ms(500);
                if(gpio_get(BUTTON_PIN) != 0)
                {
                    LED = NoBlink;
                    gpio_put(LED_PIN,0);
                    sleep_ms(100);
                }
                break;
            case NoBlink:
                
                if(gpio_get(BUTTON_PIN) !=0)
                {
                    LED = Blinking;
                    sleep_ms(100);
                }
                sleep_ms(50);
                break;
        }
    }
}