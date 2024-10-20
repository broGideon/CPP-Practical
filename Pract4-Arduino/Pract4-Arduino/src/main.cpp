#include <Arduino.h>
#include "pitches.h"

#define led 6
#define firstButton 2
#define secondButton 4

void setup() {
  pinMode(led, OUTPUT);
  pinMode(firstButton, INPUT);
  pinMode(secondButton, INPUT);
  Serial.begin(9600);
}

int blink;
bool isBlink = false;

int melody[] = {
        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
        NOTE_A4, NOTE_E4, NOTE_B4, NOTE_A4,
        NOTE_G4, NOTE_E4, NOTE_A4, NOTE_B4
};

int noteDurations[] = {
        4, 4, 4, 8,
        8, 4, 8, 8,
        4, 4, 4, 8
};

void music() {
  for (int thisNote = 0; thisNote < 12; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(10, melody[thisNote], noteDuration);
    delay(200);

    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);

    noTone(10);
  }
}

void loop() {
  if (digitalRead(firstButton) == HIGH) {
    Serial.println("Input first button");
    while(digitalRead(firstButton)) {}
  }
  else if (digitalRead(secondButton) == HIGH) {
    Serial.println("Input second button");
    while(digitalRead(secondButton)) {}
  }

  if (Serial.available() > 0){
    String command = Serial.readString();
    if (command == "0,1") {
      isBlink = true;
      blink = 100;
    } else if (command == "0,5") {
      isBlink = true;
      blink = 500;
    } else if (command == "1") {
      isBlink = true;
      blink = 1000;
    } else if (command == "-1") {
      music();
    }
  }

  if (isBlink) {
    digitalWrite(led, HIGH);
    delay(blink);
    digitalWrite(led, LOW);
    delay(blink);
  }

  delay(50);
}