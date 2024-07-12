#define VERSION "2.0"
#include <Wire.h>
#include <EEPROM.h>
#include <ctype.h>
#include "Adafruit_TCS34725.h"

#define runPin 6
#define amberPin 5
#define chPin 7

#define amber_LR_addr_ch1 0
#define amber_HR_addr_ch1 4
#define amber_LG_addr_ch1 8
#define amber_HG_addr_ch1 12
#define amber_LB_addr_ch1 16
#define amber_HB_addr_ch1 20

#define amber_LR_addr_ch2 24
#define amber_HR_addr_ch2 28
#define amber_LG_addr_ch2 32
#define amber_HG_addr_ch2 36
#define amber_LB_addr_ch2 40
#define amber_HB_addr_ch2 44

#define relayType_addr 48 //1 byte

byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

bool relayType, channel;
char cmd;
float red, green, blue;
float amber_LR_ch1, amber_HR_ch1, amber_LG_ch1, amber_HG_ch1, amber_LB_ch1, amber_HB_ch1;
float amber_LR_ch2, amber_HR_ch2, amber_LG_ch2, amber_HG_ch2, amber_LB_ch2, amber_HB_ch2;

void setup()
{
  pinMode(runPin, OUTPUT);
  pinMode(amberPin, OUTPUT);
  pinMode(chPin, INPUT_PULLUP);
  getVals();
  relayType = EEPROM.read(relayType_addr);
  Serial.begin(9600);
  initSensor();
}

void loop()
{
  if (Serial.available())
  {
    if (toupper((char)Serial.read()) == 'S')
      settings();
  }
  if (!checkConnection())
  {
    Serial.println("Sensor disconnected. Attempting reconnection...");
    relayType ? digitalWrite(runPin, LOW) : digitalWrite(runPin, HIGH);
    initSensor();
  }
  relayType ? digitalWrite(runPin, HIGH) : digitalWrite(runPin, LOW);
  tcs.setInterrupt(false);
  delay(60);
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);
  channel = digitalRead(chPin);
  Serial.print("Channel ");
  channel ? Serial.print("1") : Serial.print("2");
  Serial.print("\nR: " + String((int)red));
  Serial.print(" G: " + String((int)green));
  Serial.println(" B: " + String((int)blue));
  switch (channel)
  {
    case HIGH:
      {
        if (red >= amber_LR_ch1 && red <= amber_HR_ch1 && green >= amber_LG_ch1 && green <= amber_HG_ch1 && blue >= amber_LB_ch1 && blue <= amber_HB_ch1)
          amberDetected();
        else
          noReading();
        break;
      }
    case LOW:
      {
        if (red >= amber_LR_ch2 && red <= amber_HR_ch2 && green >= amber_LG_ch2 && green <= amber_HG_ch2 && blue >= amber_LB_ch2 && blue <= amber_HB_ch2)
          amberDetected();
        else
          noReading();
        break;
      }
  }
}

void amberDetected()
{
  Serial.println("Amber\n");
  relayType ? digitalWrite(amberPin, HIGH) : digitalWrite(amberPin, LOW);
}

void noReading()
{
  Serial.println("No reading\n");
  relayType ? digitalWrite(amberPin, LOW) : digitalWrite(amberPin, HIGH);
}
