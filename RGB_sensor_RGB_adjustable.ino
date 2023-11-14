#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_TCS34725.h"


byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define commonAnode false
#define RUNpin 6
#define YELLOWpin 5
#define REDpin 4
#define ERRORpin 3
#define red_LR_addr 0
#define red_HR_addr 4
#define red_LG_addr 8
#define red_HG_addr 12
#define red_LB_addr 16
#define red_HB_addr 20
#define amber_LR_addr 24
#define amber_HR_addr 28
#define amber_LG_addr 32
#define amber_HG_addr 36
#define amber_LB_addr 40
#define amber_HB_addr 44
#define relayType_addr 48 //1 byte

float red, green, blue, red_LR, red_HR, red_LG, red_HG, red_LB, red_HB, amber_LR, amber_HR, amber_LG, amber_HG, amber_LB, amber_HB;
bool relayType;
char cmd;

void setup()
{
  pinMode(RUNpin, OUTPUT);
  pinMode(YELLOWpin, OUTPUT);
  pinMode(REDpin, OUTPUT);
  pinMode(ERRORpin, OUTPUT);

  EEPROM.get(red_LR_addr, red_LR);
  EEPROM.get(red_HR_addr, red_HR);
  EEPROM.get(red_LG_addr, red_LG);
  EEPROM.get(red_HG_addr, red_HG);
  EEPROM.get(red_LB_addr, red_LB);
  EEPROM.get(red_HB_addr, red_HB);
  EEPROM.get(amber_LR_addr, amber_LR);
  EEPROM.get(amber_HR_addr, amber_HR);
  EEPROM.get(amber_LG_addr, amber_LG);
  EEPROM.get(amber_HG_addr, amber_HG);
  EEPROM.get(amber_LB_addr, amber_LB);
  EEPROM.get(amber_HB_addr, amber_HB);
  relayType = EEPROM.read(relayType_addr);

  Serial.begin(9600);

initializeSensor:
  Serial.print("Setting up sensor\n");
  //  delay(3000);
  if (tcs.begin())
  {
    Serial.print("\nReady");
    relayType ? digitalWrite(RUNpin, HIGH) : digitalWrite(RUNpin, LOW);
  }
  else
  {
    Serial.println("\nSensor error");
    relayType ? digitalWrite(RUNpin, LOW) : digitalWrite(RUNpin, HIGH);
    settings();
    goto initializeSensor;
    //while (true);
  }
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

  Serial.print("\nRGB; ");
  Serial.print("R:");
  Serial.print(int(red));
  Serial.print(" G:");
  Serial.print(int(green));
  Serial.print(" B:");
  Serial.print(int(blue));

  // 220 <= R <= 255
  // 10 <= G <= 25
  // 15 <= B <= 35
  if (red >= red_LR & red <= red_HR & green >= red_LG & green <= red_HG & blue >= red_LB & blue <= red_HB)
  {
    Serial.print("\nRed");
    if (relayType)
    {
      digitalWrite(YELLOWpin, LOW);
      digitalWrite(REDpin, HIGH);
      digitalWrite(ERRORpin, LOW);
    }
    else
    {
      digitalWrite(YELLOWpin, HIGH);
      digitalWrite(REDpin, LOW);
      digitalWrite(ERRORpin, HIGH);
    }
  }
  // 160 <= R <= 220
  // 30 <= G <= 60
  // 10 <= B <= 40
  else if (red >= amber_LR & red <= amber_HR & green >= amber_LG & green <= amber_HG  & blue >= amber_LB & blue <= amber_HB)
  {
    Serial.print("\nAmber");
    if (relayType)
    {
      digitalWrite(YELLOWpin, HIGH);
      digitalWrite(REDpin, LOW);
      digitalWrite(ERRORpin, LOW);
    }
    else
    {
      digitalWrite(YELLOWpin, LOW);
      digitalWrite(REDpin, HIGH);
      digitalWrite(ERRORpin, HIGH);
    }
  }
  else if (red == 0 & green == 0 & blue == 0)
  {
    Serial.print("\nSensor Error");
    if (relayType)
    {
      digitalWrite(REDpin, LOW);
      digitalWrite(YELLOWpin, LOW);
      digitalWrite(ERRORpin, LOW);
      digitalWrite(RUNpin, HIGH);
    }
    else
    {
      digitalWrite(REDpin, HIGH);
      digitalWrite(YELLOWpin, HIGH);
      digitalWrite(ERRORpin, HIGH);
      digitalWrite(RUNpin, LOW);
    }
  }
  else
  {
    Serial.print("\nNoReading");
    if (relayType)
    {
      digitalWrite(REDpin, LOW);
      digitalWrite(YELLOWpin, LOW);
      digitalWrite(ERRORpin, HIGH);
    }
    else
    {
      digitalWrite(REDpin, HIGH);
      digitalWrite(YELLOWpin, HIGH);
      digitalWrite(ERRORpin, LOW);
    }
  }
  //delay(500);
}
