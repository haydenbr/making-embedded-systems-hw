#include "main.hpp"

// volatile int led_on = 0;

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

    // RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    EXTI->IMR |= (1 << BUTTON_PIN);
    SYSCFG->EXTICR[0] |= 0x00;
    //Attach interrupt
    // enable rising edge trigger
    EXTI->RTSR |= (1 << BUTTON_PIN);
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

  while (1) {}
}

volatile void EXTI0_IRQHandler(void) {
  GPIOG->ODR |= (1 << LED_PIN);
  EXTI->PR = EXTI_PR_PR0;
}
