#include <Arduino.h>

#define output 3
#define firstButton 7
#define secondButton 4
#define thirdButton 2

void setup() {
  pinMode(output, OUTPUT);
  pinMode(firstButton, INPUT);
  pinMode(secondButton, INPUT);
  pinMode(thirdButton, INPUT);
  Serial.begin(9600);
}

void stringToBinary(String input) {
  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    for (int j = 7; j >= 0; j--) {
      if (c & (1 << j)) {
        Serial.print("1");
      } else {
        Serial.print("0");
      }
    }
  }
  Serial.println();
}

short voltage = 0;
bool isActive = false;
bool isBlink = false;

void loop() {
  if (digitalRead(firstButton) == HIGH) {
    if (isActive) {
      digitalWrite(output, LOW);
      isActive = false;
    } else {
      digitalWrite(output, HIGH);
      isActive = true;
    }

    isBlink=false;
    while(digitalRead(firstButton)) {}
  }
  else if (digitalRead(secondButton) == HIGH) {
    voltage = voltage < 255 ? voltage+51 : 0;
    analogWrite(output, voltage);

    isActive = true;
    isBlink=false;
    while(digitalRead(secondButton)) {}
  }
  else if (digitalRead(thirdButton) == HIGH){
    String surname = "Turuntsev";
    Serial.print(surname + " Leonid Sergeevich");
    Serial.println("");
    stringToBinary(surname);

    isBlink=false;
    while(digitalRead(thirdButton)) {}
  }

  if (Serial.available() > 0){
    char c = Serial.read();
    if (c == 'M'){
      isActive=true;
      isBlink=true;
    }
    else if (c == 'S'){
      isActive=false;
      isBlink=false;
      digitalWrite(output, LOW);
    }
  }
  if (isBlink) {
    digitalWrite(output, HIGH);
    delay(300);
    digitalWrite(output, LOW);
    delay(300);
  }

  delay(100);
}