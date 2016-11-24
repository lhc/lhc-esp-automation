#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <NTPClient.h>
#include <Task.h>
#include "hal.h"

int16_t utc = -3; //UTC -3:00 Brazil
uint8_t lhc_status = 0;

WiFiUDP ntpUDP;
WiFiManager wifiManager;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);

void update(uint32_t deltaTime);

TaskManager taskManager;
FunctionTask taskGetInfo(update, MsToTaskTime(60000)); // turn on the led in 400ms

void reset_wifi_config(void) {
  wifiManager.resetSettings();
  delay(1500);
  ESP.reset();
}

void setup() {

  Serial.begin(115200);
  Serial.println("Booting");

  initGPIO();

  restoreLoadState();

  Serial.println("Boot Num:");
  Serial.println(bootIncrement());

  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("LHC-Automation", "tijolo22");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  wifiLED(HIGH);

  lhc_status = updateLHCstatus();

  Serial.print("LHC Status:");
  Serial.println(lhc_status);

  /* ON: 18:00
  * OFF: 06:00
  */
  set_timeSchedule(18,0,6,0);
  dumpMemory(); //DEBUG

  timeClient.begin();
  timeClient.update();

  taskManager.StartTask(&taskGetInfo);
}

void update(uint32_t deltaTime) {

  lhc_status = updateLHCstatus();

  uint8_t time_schedule[2];
  time_schedule[0] = get_timeOn();
  time_schedule[1] = get_timeOff();

  uint8_t ntp_hh = timeClient.getHours();

  if(lhc_status == 1){

    if((ntp_hh >= time_schedule[0]) || (ntp_hh <= time_schedule[1])) {
      Serial.println("LHC Aberto e Noite");
      loadB(HIGH);
    } else {
      Serial.println("LHC Aberto e de dia!");
      loadB(LOW);
    }

  } else {
    Serial.println("LHC Fechado!");
    loadB(LOW);
  }

}

void loop() {
  taskManager.Loop();
}
