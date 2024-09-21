#include "Arduino.h"

#define red 5
#define yellow 3
#define green 1

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(red, HIGH);
  delay(1500);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(1500);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(1500);
  for (short i=0; i<5; i++) {
    digitalWrite(green, HIGH);
    delay(750);
    digitalWrite(green, LOW);
    delay(750);
  }
  digitalWrite(yellow, HIGH);
  delay(1500);
  digitalWrite(yellow, LOW);
}
