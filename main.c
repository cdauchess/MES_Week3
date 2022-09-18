/* 
    This code originates from the Getting started with Raspberry Pi Pico document
    https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
    CC BY-ND Raspberry Pi (Trading) Ltd
*/

#include "main.h"


//Hardware IO
const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;


uint current_LED = 0;
//ISR Flag(s)
uint buttonEdge = 0; //1 for rising, 2 for falling
uint count = 0;
absolute_time_t prevEdgeTime;

void buttonISR(uint gpio, uint32_t events){
    if(gpio == BUTTON_PIN && events == GPIO_IRQ_EDGE_RISE){
      //Button_Flag = 1;
      prevEdgeTime = get_absolute_time();
      buttonEdge = RISING_EDGE;
      //buttonAlarm = add_alarm_in_ms(40, &debounceTimer, NULL ,true); 
    }
    else if(gpio == BUTTON_PIN && events == GPIO_IRQ_EDGE_FALL){
        prevEdgeTime = get_absolute_time();
        buttonEdge = FALLING_EDGE;
    }
}

bool LED_Toggle(repeating_timer_t *rt){
    count++;
}

int main() {
    LED_STATE LED = NoBlink;
    uint newLED = 0;
    repeating_timer_t timer;
    bi_decl(bi_program_description("PROJECT DESCRIPTION"));
    gpio_set_irq_enabled_with_callback(BUTTON_PIN,GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &buttonISR);
    add_repeating_timer_ms(250,LED_Toggle, &LED ,&timer);

    LED_INIT();
    BUTTON_INIT();

    volatile uint32_t currentTime = to_ms_since_boot(get_absolute_time());
    uint Button_Flag = 0;

    while(1) {
        switch(LED)
        {
            case Blinking:
                if(Button_Flag == 1)
                {
                    LED = NoBlink;
                    LED_OFF();
                    Button_Flag = 0;
                }
                if(count > 1){
                    newLED = Toggle_LED(LED);
                }              
                break;
            case NoBlink:
                
                if(Button_Flag == 1)
                {
                    LED = Blinking;
                    Button_Flag = 0;
                }
                break;
        }
        currentTime = to_ms_since_boot(get_absolute_time());
        if(buttonEdge == RISING_EDGE && (currentTime-to_ms_since_boot(prevEdgeTime)) > 5){
            Button_Flag = 1;
            buttonEdge = 0;
        }
    }
}

void LED_ON(){
    gpio_put(LED_PIN, 1);
}

void LED_OFF(){
    gpio_put(LED_PIN,0);
}

void LED_INIT(){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void BUTTON_INIT(){
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);
}

uint LED_Status(){
    uint LED_Val = 0;
    LED_Val = gpio_get_out_level(LED_PIN);
    return LED_Val;
}

uint Toggle_LED(LED_STATE currentState){
    if(LED_Status()){
        LED_OFF();
        count = 0;
        return 0;
    }
    else if(!LED_Status()){
        LED_ON();
        count = 0;
        return 1;
    }
}