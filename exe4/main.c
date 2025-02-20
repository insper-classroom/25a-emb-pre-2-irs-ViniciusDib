#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>


const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;

const int BTN_PIN_G = 26;
const int LED_PIN_G = 6;

volatile bool estador = false;
volatile bool estadog = false;


void btn_callback(uint gpio, uint32_t events) {
  if (events == GPIO_IRQ_EDGE_FALL) { 
    if (gpio == BTN_PIN_R)
      estador = true;
    else if (gpio == BTN_PIN_G)
      estadog = true;
  } else if (events & GPIO_IRQ_EDGE_RISE) { 
    if (gpio == BTN_PIN_R)
      estador = false;
    else if (gpio == BTN_PIN_G)
      estadog = false;
  }
}



int main() {
  stdio_init_all();

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);


  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  gpio_set_irq_enabled_with_callback(
      BTN_PIN_G, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);


  while (true) {
    if (estadog){
      gpio_put(LED_PIN_G, 1);
    }
    if (estadog == false){
    gpio_put(LED_PIN_G, 0);
    }
    if (estador){
      gpio_put(LED_PIN_R, 1);
    }
    if (estador == false){
      gpio_put(LED_PIN_R, 0);
    }
  }
}





