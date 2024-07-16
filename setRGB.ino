void setRGB() {
  const String validCmd[] = {"S", "LR", "HR", "LG", "HG", "LB", "HB"};
begin_setRGB:
  getVals();
  Serial.print("[SETTINGS/");
  switch (cmd) {
    case '1': {
        Serial.println("Yellow Ch1]");
        Serial.println("LR: " + String(amber_LR_ch1));
        Serial.println("HR: " + String(amber_HR_ch1));
        Serial.println("LG: " + String(amber_LG_ch1));
        Serial.println("HG: " + String(amber_HG_ch1));
        Serial.println("LB: " + String(amber_LB_ch1));
        Serial.println("HB: " + String(amber_HB_ch1));
        break;
      }
    case '2': {
        Serial.println("Yellow Ch2]");
        Serial.println("LR: " + String(amber_LR_ch2));
        Serial.println("HR: " + String(amber_HR_ch2));
        Serial.println("LG: " + String(amber_LG_ch2));
        Serial.println("HG: " + String(amber_HG_ch2));
        Serial.println("LB: " + String(amber_LB_ch2));
        Serial.println("HB: " + String(amber_HB_ch2));
        break;
      }
  }
  Serial.println("S : Back");
waitCmd_setRGB:
  while (!Serial.available());
  String color = Serial.readStringUntil('\r\n');
  color.trim();
  color.toUpperCase();
  bool isValid = false;
  for (uint8_t i = 0; i < sizeof(validCmd) / sizeof(validCmd[0]); i++) {
    if (color == validCmd[i]) {
      isValid = true;
      break;
    }
  }
  if (!isValid) {
    Serial.println("Invalid command");
    goto waitCmd_setRGB;
  }
  if (color == validCmd[0])
    return;
  Serial.print("Insert new value for " + color + ": ");
  while (!Serial.available());
  int val = Serial.parseInt();
  Serial.println(val);
  if (val < 0 || val > 255) {
    Serial.println("Value out of range");
    goto waitCmd_setRGB;
  }
  switch (cmd) {
    case '1': {
        if (color == "LR")
          EEPROM.update(amber_LR_addr_ch1, val);
        else if (color == "HR")
          EEPROM.update(amber_HR_addr_ch1, val);
        else if (color == "LG")
          EEPROM.update(amber_LG_addr_ch1, val);
        else if (color == "HG")
          EEPROM.update(amber_HG_addr_ch1, val);
        else if (color == "LB")
          EEPROM.update(amber_LB_addr_ch1, val);
        else if (color == "HB")
          EEPROM.update(amber_HB_addr_ch1, val);
        break;
      }
    case '2': {
        if (color == "LR")
          EEPROM.update(amber_LR_addr_ch2, val);
        else if (color == "HR")
          EEPROM.update(amber_HR_addr_ch2, val);
        else if (color == "LG")
          EEPROM.update(amber_LG_addr_ch2, val);
        else if (color == "HG")
          EEPROM.update(amber_HG_addr_ch2, val);
        else if (color == "LB")
          EEPROM.update(amber_LB_addr_ch2, val);
        else if (color == "HB")
          EEPROM.update(amber_HB_addr_ch2, val);
        break;
      }
  }
  while (Serial.available())
    Serial.readStringUntil('\r\n');
  goto begin_setRGB;
}
