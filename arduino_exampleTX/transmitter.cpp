#include <Arduino.h>
#include "transmitter.h"

#define STX (char)2
#define ETX (char)3

void setup() {
  Serial.begin(115200);
}

void loop() {

  your_struct test;
  uint8_t payload[sizeof(test)];

  memcpy(payload, &test, sizeof(test));

  Serial.print(STX);

  for (int i = 0; i < sizeof(test); i++) {
    Serial.print(payload[i] < 16 ? "0" : "");
    Serial.print(payload[i], HEX);
  }

  Serial.print(ETX);

  delay(1000);

}