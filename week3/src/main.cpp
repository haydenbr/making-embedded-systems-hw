#include "main.hpp"

int main() {
  // enable clock for GPIOA port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // button pin input mode
  GPIOA->MODER &= ~(0x3 << (BUTTON_PIN*2));
  // button pin pull-down
  GPIOA->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
  GPIOA->PUPDR |= (0x2 << (BUTTON_PIN*2));

  // enable clock for GPIOG port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
  // write 00 (reset) for LED pin mode
  GPIOG->MODER  &= ~(0x3 << (LED_PIN*2));
  // write 01 (general purpose output) for LED pin mode
  GPIOG->MODER  |=  (0x1 << (LED_PIN*2));
  // write 0 (output push-pull) for LED pin output type
  GPIOG->OTYPER &= ~(1 << LED_PIN);

  // bool button_pressed = 0;
  while (1) {
    unsigned int idr_val = GPIOA->IDR;
    if (idr_val & (1 << BUTTON_PIN)) {
      GPIOG->ODR |= (1 << LED_PIN);
    } else {
      GPIOG->ODR &= ~(1 << LED_PIN);
    }
  }
}
