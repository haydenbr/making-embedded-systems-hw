#include "main.hpp"

int main() {
  // enable clock for GPIO A port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // button pin input mode
  // GPIOA->MODER &= ~(0x3 << (BUTTON_PIN*2));
  GPIOA->MODER = 0x00000000;
  // button pin pull-down
  // GPIOA->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
  // GPIOA->PUPDR |= (0x2 << (BUTTON_PIN*2));

  // enable clock for GPIO G port
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
  // write 00 (reset) for LED pin mode
  GPIOG->MODER  &= ~(0x3 << (LED_PIN*2));
  // write 01 (general purpose output) for LED pin mode
  GPIOG->MODER  |=  (0x1 << (LED_PIN*2));
  // write 0 (output push-pull) for LED pin output type
  GPIOG->OTYPER &= ~(1 << LED_PIN);

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[0] |= 0x00;

  // enable rising edge trigger
  EXTI->RTSR |= (1 << BUTTON_PIN);
  // unmask interrupt
  EXTI->IMR |= (1 << BUTTON_PIN);

  NVIC_SetPriority(EXTI0_IRQn, 1);
  NVIC_EnableIRQ(EXTI0_IRQn);

  while (1) {
    if (led_on) {
      GPIOG->ODR |= (1 << LED_PIN);
    } else {
      GPIOG->ODR &= ~(1 << LED_PIN);
    }
  }
}

void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1 << BUTTON_PIN)) {
    EXTI->PR |= (1 << BUTTON_PIN);
    led_on = true;
  }
}