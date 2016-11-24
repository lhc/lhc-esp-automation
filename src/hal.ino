#include "hal.h"

uint8_t ledStatus_state = 0;
uint8_t ledWiFi_state = 0;
uint8_t loadA_state = 0;
uint8_t loadB_state = 0;

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

void updateStatus(void){
    updateGPIOstate(loadA_state ,loadB_state);
}

void restoreLoadState(void) {
    digitalWrite(LOAD_A, getGPIOstateLoadA());//LOAD B
    digitalWrite(LOAD_B, getGPIOstateLoadB());//LOAD B
}

void statusLED(uint8_t state){
  digitalWrite(LED_A, state);
  ledStatus_state = state;
}

void statusLED_toggle(void){
  digitalWrite(LED_A, !ledStatus_state);
  ledStatus_state = !ledStatus_state;
}

void wifiLED(uint8_t state){
  digitalWrite(LED_B, state);
  ledWiFi_state = state;
}

void wifiLED_toggle(void){
  digitalWrite(LED_B, !ledWiFi_state);
  ledWiFi_state = !ledWiFi_state;
}

void loadA(uint8_t state){
  digitalWrite(LOAD_A, state);
  loadA_state = state;
  updateStatus();
}

void loadB(uint8_t state){
  digitalWrite(LOAD_B, state);
  loadB_state = state;
  updateStatus();
}
