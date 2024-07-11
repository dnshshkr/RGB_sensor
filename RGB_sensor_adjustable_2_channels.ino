#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_TCS34725.h"


byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define commonAnode false
#define runPin 6
#define yellowPin 5
#define errPin 3
#define chPin 7

//#define red_LR_addr_ch1 0
//#define red_HR_addr_ch1 4
//#define red_LG_addr_ch1 8
//#define red_HG_addr_ch1 12
//#define red_LB_addr_ch1 16
//#define red_HB_addr_ch1 20

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

float red, green, blue;
float amber_LR_ch1, amber_HR_ch1, amber_LG_ch1, amber_HG_ch1, amber_LB_ch1, amber_HB_ch1;
float amber_LR_ch2, amber_HR_ch2, amber_LG_ch2, amber_HG_ch2, amber_LB_ch2, amber_HB_ch2;
bool relayType, channel;
char cmd;

void setup()
{
  pinMode(runPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(errPin, OUTPUT);
  pinMode(chPin, INPUT_PULLUP);

  EEPROM.get(amber_LR_addr_ch1, amber_LR_ch1);
  EEPROM.get(amber_HR_addr_ch1, amber_HR_ch1);
  EEPROM.get(amber_LG_addr_ch1, amber_LG_ch1);
  EEPROM.get(amber_HG_addr_ch1, amber_HG_ch1);
  EEPROM.get(amber_LB_addr_ch1, amber_LB_ch1);
  EEPROM.get(amber_HB_addr_ch1, amber_HB_ch1);

  EEPROM.get(amber_LR_addr_ch2, amber_LR_ch2);
  EEPROM.get(amber_HR_addr_ch2, amber_HR_ch2);
  EEPROM.get(amber_LG_addr_ch2, amber_LG_ch2);
  EEPROM.get(amber_HG_addr_ch2, amber_HG_ch2);
  EEPROM.get(amber_LB_addr_ch2, amber_LB_ch2);
  EEPROM.get(amber_HB_addr_ch2, amber_HB_ch2);

  relayType = EEPROM.read(relayType_addr);

  Serial.begin(9600);

  Serial.print("Setting up sensor\n");
  while (!tcs.begin())
  {
    Serial.println("\nSensor error");
    relayType ? digitalWrite(runPin, LOW) : digitalWrite(runPin, HIGH);
    TWCR = 0;
    delay(1000);
  }

  Serial.print("\nReady");
  relayType ? digitalWrite(runPin, HIGH) : digitalWrite(runPin, LOW);
}

void loop()
{
  if (Serial.available())
  {
    if (Serial.read() == 's')
      settings();
  }
  tcs.setInterrupt(false);
  delay(60);
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);
  //delay(500);

  channel = digitalRead(chPin);
  Serial.print("\nChannel ");
  !channel ? Serial.print("1") : Serial.print("2");
  Serial.print("\nRGB; ");
  Serial.print("R:");
  Serial.print(int(red));
  Serial.print(" G:");
  Serial.print(int(green));
  Serial.print(" B:");
  Serial.print(int(blue));
  if (red == 0 && green == 0 && blue == 0)
  {
    Serial.print("\nSensor Error");
    if (relayType)
    {
      digitalWrite(yellowPin, LOW);
      digitalWrite(errPin, LOW);
      digitalWrite(runPin, HIGH);
    }
    else
    {
      digitalWrite(yellowPin, HIGH);
      digitalWrite(errPin, HIGH);
      digitalWrite(runPin, LOW);
    }
  }
  else
  {
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
}

void amberDetected()
{
  Serial.print("\nAmber");
  if (relayType)
  {
    digitalWrite(yellowPin, HIGH);
    digitalWrite(errPin, LOW);
  }
  else
  {
    digitalWrite(yellowPin, LOW);
    digitalWrite(errPin, HIGH);
  }
}

void noReading()
{
  Serial.print("\nNoReading");
  if (relayType)
  {
    digitalWrite(yellowPin, LOW);
    digitalWrite(errPin, HIGH);
  }
  else
  {
    digitalWrite(yellowPin, HIGH);
    digitalWrite(errPin, LOW);
  }
}
