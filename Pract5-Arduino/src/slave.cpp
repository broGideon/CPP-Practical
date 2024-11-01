#include <Arduino.h>
#include <Wire.h>

#define led 8

bool led_state = false;

void helloMaster(int bytes) {
  Serial.println("slave write response");
  while (Wire.available()) {
        char c = Wire.read();
        Serial.print(c);

        Serial.println();
    }
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(helloMaster);
  ///*  */pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Slave is ready");
}

void loop() {
  delay(100);
}
