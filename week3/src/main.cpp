#include "main.hpp"

int main() {
  /*
  green - PB0
  blue - PB7
  red - PB14
  */

  // enable clock for GPIOA port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  // button pin input mode
  GPIOC->MODER &= ~(0x3 << (BUTTON_PIN*2));
  // button pin pull-down (couldn't get it working with pull-up)
  GPIOC->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
  GPIOC->PUPDR |= (0x2 << (BUTTON_PIN*2));

  // enable clock for GPIOB port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  // write 00 (reset) for LED pin mode
  GPIOB->MODER  &= ~(0x3 << (BLUE_LED_PIN*2));
  // write 01 (general purpose output) for LED pin mode
  GPIOB->MODER  |=  (0x1 << (BLUE_LED_PIN*2));
  // write 0 (output push-pull) for LED pin output type
  GPIOB->OTYPER &= ~(1 << BLUE_LED_PIN);
  // set LED pin high
  // GPIOB->ODR |= (1 << BLUE_LED_PIN);

  // bool button_pressed = 0;
  while (1) {
    unsigned int idr_val = GPIOC->IDR;
    if (idr_val & (1 << BUTTON_PIN)) {
      GPIOB->ODR |= (1 << BLUE_LED_PIN);
    } else {
      GPIOB->ODR &= ~(1 << BLUE_LED_PIN);
    }
  }
}
