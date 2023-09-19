#include <Arduino.h>
#include "max6675.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
float Temperatur;

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);


#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define LED_PIN 2

void LEDan() {
  digitalWrite(LED_PIN, LOW);
}

void LEDaus() {
  digitalWrite(LED_PIN, HIGH);
}

void LEDinit() {
  pinMode(LED_PIN, OUTPUT);
}


void setup() {
  LEDinit();
  LEDan();
  Serial.begin(115200);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  //delay(500);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pizzaofen-");
  display.println("Thermometer");
  display.println("");
  display.println("thermocouple");
  display.println("max6675");
  display.display();
  delay(4000);
  LEDaus();
}

void printValues() {
  Temperatur=thermocouple.readCelsius();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(Temperatur,0);
  display.display();

  Serial.println(Temperatur);
}

void loop() {
  LEDan();

  printValues();
  
  LEDaus();
  delay(1000);
}