void gainSetting() {
  Serial.println("Choose new gain:\n1: 1\n2: 4\n3: 16\n4: 60");
waitCmd_gainSetting:
  while (!Serial.available());
  char choice = Serial.readStringUntil('\r\n').charAt(0);
  if (String("sS").indexOf(choice) != -1)
    return;
  if (choice - '0' < 1 or choice - '0' > 4) {
    Serial.println("Invalid input");
    goto waitCmd_gainSetting;
  }
  setGain(choice - '0' - 1);
  uint8_t gain = getGain(choice - '0' - 1);
  Serial.println("Gain set to " + String(gain));
  return;
}
uint8_t getGain(uint8_t index) {
  if (index == 0)
    return 1;
  else if (index == 1)
    return 4;
  else if (index == 2)
    return 16;
  else if (index == 3)
    return 60;
  else
    return 1;
}
void setGain(uint8_t index) {
  if (index == 0)
    tcs.setGain(TCS34725_GAIN_1X);
  else if (index == 1)
    tcs.setGain(TCS34725_GAIN_4X);
  else if (index == 2)
    tcs.setGain(TCS34725_GAIN_16X);
  else if (index == 3)
    tcs.setGain(TCS34725_GAIN_60X);
  else {
    tcs.setGain(TCS34725_GAIN_1X);
    index = 1;
  }
  //  switch (index) {
  //    case 0: {
  //        tcs.setGain(TCS34725_GAIN_1X);
  //        break;
  //      }
  //    case 1: {
  //        tcs.setGain(TCS34725_GAIN_4X);
  //        break;
  //      }
  //    case 2: {
  //        tcs.setGain(TCS34725_GAIN_16X);
  //        break;
  //      }
  //    case 3: {
  //        tcs.setGain(TCS34725_GAIN_60X);
  //        break;
  //      }
  //    default: {
  //        tcs.setGain(TCS34725_GAIN_1X);
  //        index = 1;
  //      }
  //  }
  EEPROM.update(gain_addr, index);
}
