#include <Arduino.h>
#include <EEPROM.h>

#define firstLamp 13
#define secondLamp 12
#define thirdLamp 11
#define fourthLamp 10

#define firstBtn 7
#define secondBtn 4
#define thirdBtn 2

short firstBtnState = 0;
short secondBtnState = 0;

void setup() {
    EEPROM.get(0, firstBtnState);
    EEPROM.get(2, secondBtnState);

    Serial.begin(9600);
    pinMode(firstLamp, OUTPUT);
    pinMode(secondLamp, OUTPUT);
    pinMode(thirdLamp, OUTPUT);
    pinMode(fourthLamp, OUTPUT);

    pinMode(firstBtn, INPUT);
    pinMode(secondBtn, INPUT);
    pinMode(thirdBtn, INPUT);
}

void loop() {
    if (firstBtnState % 2 == 0) {
        digitalWrite(firstLamp, HIGH);
        digitalWrite(secondLamp, LOW);
    } else {
        digitalWrite(firstLamp, LOW);
        digitalWrite(secondLamp, HIGH);
    }

    if (secondBtnState % 2 == 0) {
        digitalWrite(thirdLamp, HIGH);
        digitalWrite(fourthLamp, LOW);
    } else {
        digitalWrite(thirdLamp, LOW);
        digitalWrite(fourthLamp, HIGH);
    }

    if (digitalRead(firstBtn)) {
        firstBtnState++;
        EEPROM.put(0, firstBtnState);
        Serial.println("Increment firstBtnState: " + String(firstBtnState));
        while (digitalRead(firstBtn)) {}
    }
    if (digitalRead(secondBtn)) {
        secondBtnState++;
        EEPROM.put(2, secondBtnState);
        Serial.println("Increment secondBtnState: " + String(secondBtnState));
        while (digitalRead(secondBtn)) {}
    }
    if (digitalRead(thirdBtn)) {
        firstBtnState = 0;
        secondBtnState = 0;
        Serial.println("Reset both btnStates");
        while (digitalRead(thirdBtn)) {}
    }

    delay(100);
}
