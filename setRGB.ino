void setRGB() {
  const String validCmd[] = {"S", "LR", "HR", "LG", "HG", "LB", "HB"};
begin_setRGB:
  getVals();
  Serial.print("[SETTINGS/Yellow Ch"), Serial.print(cmd), Serial.println("]");
  switch (cmd) {
    case '1': {
        Serial.println("LR: " + String(amber_LR_ch1));
        Serial.println("HR: " + String(amber_HR_ch1));
        Serial.println("LG: " + String(amber_LG_ch1));
        Serial.println("HG: " + String(amber_HG_ch1));
        Serial.println("LB: " + String(amber_LB_ch1));
        Serial.println("HB: " + String(amber_HB_ch1));
        break;
      }
    case '2': {
        Serial.println("LR: " + String(amber_LR_ch2));
        Serial.println("HR: " + String(amber_HR_ch2));
        Serial.println("LG: " + String(amber_LG_ch2));
        Serial.println("HG: " + String(amber_HG_ch2));
        Serial.println("LB: " + String(amber_LB_ch2));
        Serial.println("HB: " + String(amber_HB_ch2));
      }
  }
  Serial.println("S : Back");
waitCmd_setRGB1:
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
    goto waitCmd_setRGB1;
  }
  if (color == validCmd[0])
    return;
waitCmd_setRGB2:
  Serial.print("Insert new value for " + color + ": ");
  while (!Serial.available());
  int val = Serial.parseInt();
  Serial.println(val);
  if (val < 0 || val > 255) {
    Serial.println("Value out of range");
    goto waitCmd_setRGB2;
  }
  switch (cmd) {
    case '1': {
        if (color == "LR") {
          if (checkValue(val, amber_HR_ch1, "LR"))
            EEPROM.update(amber_LR_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HR") {
          if (checkValue(amber_LR_ch1, val, "HR"))
            EEPROM.update(amber_HR_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "LG") {
          if (checkValue(val, amber_HG_ch1, "LG"))
            EEPROM.update(amber_LG_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HG") {
          if (checkValue(amber_LG_ch1, val, "HG"))
            EEPROM.update(amber_HG_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "LB") {
          if (checkValue(val, amber_HB_ch1, "LB"))
            EEPROM.update(amber_LB_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HB") {
          if (checkValue(amber_LB_ch1, val, "HB"))
            EEPROM.update(amber_HB_addr_ch1, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        break;
      }
    case '2': {
        if (color == "LR") {
          if (checkValue(val, amber_HR_ch2, "LR"))
            EEPROM.update(amber_LR_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HR") {
          if (checkValue(amber_LR_ch2, val, "HR"))
            EEPROM.update(amber_HR_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "LG") {
          if (checkValue(val, amber_HG_ch2, "LG"))
            EEPROM.update(amber_LG_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HG") {
          if (checkValue(amber_LG_ch2, val, "HG"))
            EEPROM.update(amber_HG_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "LB") {
          if (checkValue(val, amber_HB_ch2, "LB"))
            EEPROM.update(amber_LB_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
        else if (color == "HB") {
          if (checkValue(amber_LB_ch2, val, "HB"))
            EEPROM.update(amber_HB_addr_ch2, val);
          else {
            flushSerial();
            goto waitCmd_setRGB2;
          }
        }
      }
  }
  flushSerial();
  goto begin_setRGB;
}
bool checkValue(uint8_t low, uint8_t high, const char* cur) {
  if (cur[0] == 'L') {
    if (low > high) {
      Serial.print(cur), Serial.print("("), Serial.print(low), Serial.print(")"), Serial.print(" cannot be larger than H"), Serial.print(cur[1]), Serial.print("("), Serial.print(high), Serial.println(")");
      return false;
    }
    else
      return true;
  }
  else if (cur[0] == 'H') {
    if (high < low) {
      Serial.print(cur), Serial.print("("), Serial.print(high), Serial.print(")"), Serial.print(" cannot be smaller than L"), Serial.print(cur[1]), Serial.print("("), Serial.print(low), Serial.println(")");
      return false;
    }
    else
      return true;
  }
}
