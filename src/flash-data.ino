#include <EEPROM.h>

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 10
#define BOOT_COUNTER  4
#define FULL_MEMORY   4096
//Variavel com o numero de boots do ESP
uint32_t boot_num = 0;

uint32_t  bootIncrement() {

  EEPROM.begin(MEM_ALOC_SIZE);

  boot_num = ((uint8_t)EEPROM.read(3) << 24) | ((uint8_t)EEPROM.read(2) << 16) | ((uint8_t)EEPROM.read(1) << 8) | ((uint8_t)EEPROM.read(0));

  boot_num++;

  EEPROM.write(3,(boot_num & 0xff000000UL) >> 24);
  EEPROM.write(2,(boot_num & 0x00ff0000UL) >> 16);
  EEPROM.write(1,(boot_num & 0x0000ff00UL) >>  8);
  EEPROM.write(0,(boot_num & 0x000000ffUL));

  EEPROM.end();

  return boot_num;
}

void reset_memory(uint32_t memory_alloc) {

  EEPROM.begin(memory_alloc);
  uint16_t mem_pos = 0;

  for (mem_pos = 0; mem_pos < memory_alloc; mem_pos++) {
    EEPROM.write(mem_pos,0);
  }

  EEPROM.end();
}

void reset_counter(void){
  reset_memory(BOOT_COUNTER);
}

void set_timeSchedule(int h_on, int m_on, int h_off, int m_off) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(4,h_on);
  EEPROM.write(5,m_on);
  EEPROM.write(6,h_off);
  EEPROM.write(7,m_off);
  EEPROM.end();
}

uint8_t get_timeOn(void){
  uint8_t t_on = 0;
  EEPROM.begin(MEM_ALOC_SIZE);
  t_on = EEPROM.read(4);
  EEPROM.end();
  return t_on;
}

uint8_t get_timeOff(void){
  uint8_t t_off = 0;
  EEPROM.begin(MEM_ALOC_SIZE);
  t_off = EEPROM.read(6);
  EEPROM.end();
  return t_off;
}

void updateGPIOstate(uint8_t loadA, uint8_t loadB){
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(8,loadA);
  EEPROM.write(9,loadB);
  EEPROM.end();
}

uint8_t getGPIOstateLoadA(void){
  uint8_t la_state = 0;
  EEPROM.begin(MEM_ALOC_SIZE);
  la_state = EEPROM.read(8);
  EEPROM.end();
  return la_state;
}

uint8_t getGPIOstateLoadB(void){
  uint8_t lb_state = 0;
  EEPROM.begin(MEM_ALOC_SIZE);
  lb_state = EEPROM.read(9);
  EEPROM.end();
  return lb_state;
}

void dumpMemory(void) {

  uint8_t mem_cnt = 0;

  EEPROM.begin(MEM_ALOC_SIZE);

  for (mem_cnt; mem_cnt < MEM_ALOC_SIZE; mem_cnt++) {
    Serial.print(EEPROM.read(mem_cnt));
  }

  EEPROM.end();

}
