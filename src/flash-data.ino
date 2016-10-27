#include <EEPROM.h>

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 8
//Variavel com o numero de boots do ESP
uint8_t boot_num = 0;

void  bootIncrement() {
  EEPROM.begin(MEM_ALOC_SIZE);
  boot_num = EEPROM.read(0);
  boot_num++;
  EEPROM.write(0,boot_num);
  EEPROM.end();
}
