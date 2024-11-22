#include <Arduino.h>
#define latchPin 8
#define clockPin 12
#define dataPin 11
#define output 3


void playMelody() {
    tone(output, 523, 500);
    delay(500);
    tone(output, 587, 500);
    delay(500);
    tone(output, 659, 500);
    delay(500);
    noTone(output);
}

void timer(short number) {
    for (int i = number; i >= 0; i--) {
        digitalWrite(latchPin, LOW);
        if (i == 9) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01101111);
        } else if (i == 8) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01111111);
        } else if (i == 7) {
            shiftOut(dataPin, clockPin, MSBFIRST, B00000111);
        } else if (i == 6) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01111101);
        } else if (i == 5) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01101101);
        } else if (i == 4) {
            shiftOut(dataPin, clockPin, MSBFIRST, B11100110);
        } else if (i == 3) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01001111);
        } else if (i == 2) {
            shiftOut(dataPin, clockPin, MSBFIRST, B01011011);
        } else if (i == 1) {
            shiftOut(dataPin, clockPin, MSBFIRST, B00000110);
        } else if (i == 0) {
            shiftOut(dataPin, clockPin, MSBFIRST, B10111111);
        }
        digitalWrite(latchPin, HIGH);
        delay(1000);
    }
    playMelody();
    // 0000110 1
    // 01011011 2
    // 01001111 3
    // 11000110 4
    // 01101101 5
    // 01111101 6
    // 01101111 7
    // 01111111 8
    // 00000111 9
}

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int c = Serial.read();

        if (c >= '1' && c <= '9') {
            int num = c - '0';
            timer(num);
        }
    }

    delay(100);
}
