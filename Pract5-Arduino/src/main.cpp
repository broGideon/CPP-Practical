#include <Arduino.h>
#include <Wire.h>

#define input A0
#define output 9

int newBrightness = 0;
bool isLedOn = false;

void playMelody() {
    tone(output, 523, 500);
    delay(500);
    tone(output, 587, 500);
    delay(500);
    tone(output, 659, 500);
    delay(500);
    noTone(output);
}

void setup() {
    Wire.begin();
    pinMode(input, INPUT);
    Serial.begin(9600);
}

void loop() {
    newBrightness = map(analogRead(input), 0, 1023, 255, 0);
    Wire.beginTransmission(8);
    Wire.write(newBrightness);
    Wire.endTransmission();
    delay(100);
    Wire.requestFrom(8, 32);
    if (Wire.available()) {
        isLedOn = Wire.read();
        if (isLedOn) {
            playMelody();
        }
    }
}