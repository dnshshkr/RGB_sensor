#define VERSION "2.1"
#include <Wire.h>
#include <EEPROM.h>
#include <ctype.h>
#include "Adafruit_TCS34725.h"
#define runPin 6
#define amberPin 5
#define chPin 7
#define amber_LR_addr_ch1 0
#define amber_HR_addr_ch1 1
#define amber_LG_addr_ch1 2
#define amber_HG_addr_ch1 3
#define amber_LB_addr_ch1 4
#define amber_HB_addr_ch1 5
#define amber_LR_addr_ch2 6
#define amber_HR_addr_ch2 7
#define amber_LG_addr_ch2 8
#define amber_HG_addr_ch2 9
#define amber_LB_addr_ch2 10
#define amber_HB_addr_ch2 11
#define relayType_addr 12
#define baudRate_addr 13
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
bool relayType;
char cmd;
uint8_t amber_LR_ch1, amber_HR_ch1, amber_LG_ch1, amber_HG_ch1, amber_LB_ch1, amber_HB_ch1;
uint8_t amber_LR_ch2, amber_HR_ch2, amber_LG_ch2, amber_HG_ch2, amber_LB_ch2, amber_HB_ch2;
void (*resMcu)() = 0;
void reboot() {
  Serial.println("Rebooting...");
  delay(100);
  resMcu();
}
void setup() {
  pinMode(runPin, OUTPUT);
  pinMode(amberPin, OUTPUT);
  pinMode(chPin, INPUT_PULLUP);
  getVals();
  relayType = EEPROM.read(relayType_addr);
  Serial.begin(getBaudRate(EEPROM.read(baudRate_addr)));
  Serial.println("RGB Sensor Ver. " + String(VERSION));
  Serial.println("Copyright (C) Delloyd R&D (M) Sdn Bhd");
  initSensor();
}
void loop() {
  if (Serial.available()) {
    if (toupper((char)Serial.read()) == 'S')
      settings();
  }
  if (!checkConnection()) {
    Serial.println("Sensor disconnected. Reconnecting...");
    relayType ? digitalWrite(runPin, LOW) : digitalWrite(runPin, HIGH);
    initSensor();
  }
  float fred, fgreen, fblue;
  uint8_t red, green, blue;
  tcs.getRGB(&fred, &fgreen, &fblue);
  red = round(fred), green = round(fgreen), blue = round(fblue);
  bool channel = digitalRead(chPin);
  Serial.print("Channel ");
  channel ? Serial.println(1) : Serial.println(2);
  Serial.print("R: " + String(red) + "\tG: " + String(green) + "\tB: " + String(blue) + "\nResult: ");
  switch (channel) {
    case HIGH: {
        if (red >= amber_LR_ch1 && red <= amber_HR_ch1 && green >= amber_LG_ch1 && green <= amber_HG_ch1 && blue >= amber_LB_ch1 && blue <= amber_HB_ch1)
          amberDetected();
        else
          noReading();
        break;
      }
    case LOW: {
        if (red >= amber_LR_ch2 && red <= amber_HR_ch2 && green >= amber_LG_ch2 && green <= amber_HG_ch2 && blue >= amber_LB_ch2 && blue <= amber_HB_ch2)
          amberDetected();
        else
          noReading();
        //        break;
      }
  }
}
void amberDetected() {
  Serial.println("Yellow\n");
  relayType ? digitalWrite(amberPin, HIGH) : digitalWrite(amberPin, LOW);
}
void noReading() {
  Serial.println("No reading\n");
  relayType ? digitalWrite(amberPin, LOW) : digitalWrite(amberPin, HIGH);
}
