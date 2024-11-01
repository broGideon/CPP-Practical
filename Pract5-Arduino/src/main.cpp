#include <Arduino.h>
#include <Wire.h>

#define input A0
#define output 11

void setup() {
   Wire.begin();
    //pinMode(input, INPUT);
    Serial.begin(9600);
}

void loop() {
    Wire.beginTransmission(8);
    Wire.write("Hello, Slave!");
    Wire.endTransmission();
    Serial.println("AAA");
    delay(2000);
}
