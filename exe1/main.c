#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile bool estado = false;
volatile bool estado2 = false;

void btn_callback(uint gpio, uint32_t events) {
  if (events & GPIO_IRQ_EDGE_FALL) { 
    estado = true;
  } else if (events & GPIO_IRQ_EDGE_RISE) { 
    estado2 = true;
  }
}

int main() {
  stdio_init_all();


  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  

  while (true) {
    if (estado){
      printf("fall \n");
      estado = false;
    }
    if (estado2){
      printf("rise \n");
      estado2 = false;
    }
  }
}
