void gainSetting() {
  Serial.println("[SETTINGS/Gain]\n1: 1\n2: 4\n3: 16\n4: 60\nS: Back");
waitCmd_gainSetting:
  Serial.print("Selection: ");
  while (!Serial.available());
  char choice = toupper(Serial.readStringUntil('\r\n').charAt(0));
  Serial.println(choice);
  if (choice == 'S')
    return;
  if (choice - '0' < 1 || choice - '0' > 4) {
    Serial.println("Invalid input");
    goto waitCmd_gainSetting;
  }
  setGain(choice - '0' - 1);
  uint8_t gain = getGain(choice - '0' - 1);
  Serial.println("Gain set to " + String(gain));
  return;
}
uint8_t getGain(uint8_t index) {
  static uint8_t values[] = {1, 4, 16, 60};
  return values[index];
}
void setGain(uint8_t index) {
  static uint8_t values[] = {TCS34725_GAIN_1X, TCS34725_GAIN_4X, TCS34725_GAIN_16X, TCS34725_GAIN_60X};
  if (index >= 0 && index < sizeof(values) / sizeof(values[0]))
    tcs.setGain(values[index]);
  else {
    tcs.setGain(TCS34725_GAIN_4X);
    index = 1;
  }
  EEPROM.update(gain_addr, index);
}
