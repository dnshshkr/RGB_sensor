#define VERSION "2.11"
#include <EEPROM.h>
#include "Adafruit_TCS34725.h"
#define runPin 6
#define amberPin 5
#define chPin 7
#define relayType_addr 0
#define baudRate_addr 1
#define integTime_addr 2
#define gain_addr 3
#define amber_LR_addr_ch1 4
#define amber_HR_addr_ch1 5
#define amber_LG_addr_ch1 6
#define amber_HG_addr_ch1 7
#define amber_LB_addr_ch1 8
#define amber_HB_addr_ch1 9
#define amber_LR_addr_ch2 10
#define amber_HR_addr_ch2 11
#define amber_LG_addr_ch2 12
#define amber_HG_addr_ch2 13
#define amber_LB_addr_ch2 14
#define amber_HB_addr_ch2 15
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
bool relayType;
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
  printInfo();
  setIntegTime(EEPROM.read(integTime_addr));
  setGain(EEPROM.read(gain_addr));
  float integTime = getIntegTime(EEPROM.read(integTime_addr));
  uint8_t gain = getGain(EEPROM.read(gain_addr));
  Serial.print("Integration Time: "), Serial.print(integTime), Serial.print(" ms, Gain: "), Serial.print(gain), Serial.println("x");
  initSensor();
}
void loop() {
  char cmd;
  uint8_t red, green, blue;
  float fred, fgreen, fblue;
  if (Serial.available()) {
    if (toupper((char)Serial.read()) == 'S') {
      turnOffOutputs();
      settings();
    }
  }
  if (!checkConnection()) {
    Serial.println("Sensor disconnected. Reconnecting...");
    relayType ? digitalWrite(runPin, LOW) : digitalWrite(runPin, HIGH);
    initSensor();
  }
  relayType ? digitalWrite(runPin, HIGH) : digitalWrite(runPin, LOW);
  tcs.getRGB(&fred, &fgreen, &fblue);
  red = round(fred), green = round(fgreen), blue = round(fblue);
  bool channel = digitalRead(chPin);
  Serial.print("Channel ");
  channel ? Serial.println(1) : Serial.println(2);
  Serial.print("R: "), Serial.print(red), Serial.print("\tG: "), Serial.print(green), Serial.print("\tB: "), Serial.print(blue), Serial.println(), Serial.print("Result: ");
  if ((channel == HIGH && red >= amber_LR_ch1 && red <= amber_HR_ch1 && green >= amber_LG_ch1 && green <= amber_HG_ch1 && blue >= amber_LB_ch1 && blue <= amber_HB_ch1) ||
      (channel == LOW && red >= amber_LR_ch2 && red <= amber_HR_ch2 && green >= amber_LG_ch2 && green <= amber_HG_ch2 && blue >= amber_LB_ch2 && blue <= amber_HB_ch2)) {
    Serial.println("Yellow\n");
    relayType ? digitalWrite(amberPin, HIGH) : digitalWrite(amberPin, LOW);
  }
  else {
    Serial.println("No reading\n");
    relayType ? digitalWrite(amberPin, LOW) : digitalWrite(amberPin, HIGH);
  }
}
bool checkConnection() {
  Wire.beginTransmission(TCS34725_ADDRESS);
  return (Wire.endTransmission() == 0);
}
void turnOffOutputs() {
  digitalWrite(LED_BUILTIN, LOW);
  if (relayType) {
    digitalWrite(runPin, LOW);
    digitalWrite(amberPin, LOW);
  }
  else {
    digitalWrite(runPin, HIGH);
    digitalWrite(amberPin, HIGH);
  }
}
void printInfo() {
  Serial.print("RGB Sensor Ver. "), Serial.println(VERSION);
  Serial.println("Copyright(C) Delloyd R&D (M) Sdn Bhd");
}
void flushSerial() {
  while (Serial.available())
    Serial.read();
}
void printBack() {
  Serial.println("S: Back");
}
