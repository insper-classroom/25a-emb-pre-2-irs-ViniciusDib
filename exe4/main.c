#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;
const int BTN_PIN_G = 26;
const int LED_PIN_G = 6;

volatile int estador = 0;  
volatile int estadog = 0;  
//f

void btn_callback(uint gpio, unt32_t events) {
    sleep_ms(50);  

    if (events = 0x4) {  
            estador = !estador;  
    } 
<<<<<<< HEAD
    else if (events = 0x8) {  
            estadog = !estadog;  
=======
    else if (gpio == BTN_PIN_G && (events & GPIO_IRQ_EDGE_RISE)) {  
            estadog = !estadog;
                       
>>>>>>> f0fdb5f7a7c1e5e96ff3307771248ae65839b7c2
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_put(LED_PIN_R, estador);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);
    gpio_put(LED_PIN_G, 0);  

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

 
    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL , true, &btn_callback);
    gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

    while (true) {

        gpio_put(LED_PIN_R, estador);

        gpio_put(LED_PIN_G, estadog);

        sleep_ms(10); 
    }
}
