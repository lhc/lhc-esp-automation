#include "hal.h"

void initGPIO(void) {
  //Configura a GPIO como saida
  pinMode(LOAD_B, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LOAD_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  //Configura a GPIO como saida
  pinMode(SW_A, INPUT);
  pinMode(SW_B, INPUT);
  //Coloca a GPIO em sinal logico baixo
  digitalWrite(LOAD_B, LOW);//LOAD B
  digitalWrite(LED_A, LOW);//LED
  digitalWrite(LOAD_A, LOW);//LOAD A
  digitalWrite(LED_B, LOW);//LED
}
