#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

uint8_t updateLHCstatus(void);
uint8_t parseLHCstatus(String payload);

#define JSON_BUFFER 2048

uint8_t parseLHCstatus(String payload) {
  uint8_t status = 0;

  StaticJsonBuffer<JSON_BUFFER> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return 0;
  }

  status = root["state"]["open"];

  Serial.print("Status: ");
  Serial.println(status);

  return status;
}

uint8_t updateLHCstatus(void) {

  String status;

  HTTPClient http;
  String httpStatus = "http://lhc.net.br/spacenet.json";

  http.begin(httpStatus);

  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      status = parseLHCstatus(payload);
    }
  } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

  return status.toInt();
}
