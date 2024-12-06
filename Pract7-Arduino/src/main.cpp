#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_PIN 14
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte PROGRESS_BAR_FULL_SEGMENT_DATA[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
#define PROGRESS_BAR_FULL_SEGMENT 2
byte temp1, temp2;

void printBars(byte temperature, byte row) {
    byte bars = map(temperature, 35, 95, 0, 10);
    lcd.setCursor(9, row);
    for (byte i = 0; i < bars; i++) {
        lcd.write(PROGRESS_BAR_FULL_SEGMENT);
    }
    for (byte i = bars; i < 10; i++) {
        lcd.print(" ");
    }
}

void getTemperature() {
    temp1 = random(45, 96);
    temp2 = random(45, 96);
}

void updateDisplay() {
    lcd.setCursor(4, 0);
    lcd.print(temp1);
    lcd.write(223);
    lcd.print("C");
    printBars(temp1, 0);

    lcd.setCursor(4, 1);
    lcd.print(temp2);
    lcd.write(223);
    lcd.print("C");
    printBars(temp2, 1);
}

void draw_labels() {
    byte degree[8] = {0b11100, 0b10100, 0b11100, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};
    lcd.createChar(0, degree);

    lcd.setCursor(0, 0);
    lcd.print("CPU:");
    lcd.setCursor(0, 1);
    lcd.print("GPU:");
}

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.createChar(PROGRESS_BAR_FULL_SEGMENT, PROGRESS_BAR_FULL_SEGMENT_DATA);
    draw_labels();
}

void loop() {
    getTemperature();
    updateDisplay();
    delay(1000);
}