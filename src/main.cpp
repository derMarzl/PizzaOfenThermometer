// Pizzaofen Thermometer
#include <Arduino.h>
#include "max6675.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
float Temperatur=0;

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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C 0x3D(for the 64x48)
  display.display();
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pizzaofen-");
  display.println("Thermo-");
  display.println("meter");
  display.println("");
  display.println("max6675");
  display.display();
  delay(4000);  // mindestens 500ms warten für MAX6675
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
  delay(500);
}