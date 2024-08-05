void setRGB(char cmd) {
  const String validCmd[] = {"S", "LR", "HR", "LG", "HG", "LB", "HB"};
begin_setRGB:
  getVals();
  Serial.print("[SETTINGS/Yellow Ch"), Serial.print(cmd), Serial.println("]");
  switch (cmd) {
    case '1': {
        Serial.print("LR: "), Serial.println(amber_LR_ch1);
        Serial.print("HR: "), Serial.println(amber_HR_ch1);
        Serial.print("LG: "), Serial.println(amber_LG_ch1);
        Serial.print("HG: "), Serial.println(amber_HG_ch1);
        Serial.print("LB: "), Serial.println(amber_LB_ch1);
        Serial.print("HB: "), Serial.println(amber_HB_ch1);
        break;
      }
    case '2': {
        Serial.print("LR: "), Serial.println(amber_LR_ch2);
        Serial.print("HR: "), Serial.println(amber_HR_ch2);
        Serial.print("LG: "), Serial.println(amber_LG_ch2);
        Serial.print("HG: "), Serial.println(amber_HG_ch2);
        Serial.print("LB: "), Serial.println(amber_LB_ch2);
        Serial.print("HB: "), Serial.println(amber_HB_ch2);
      }
  }
  printBack();
waitCmd_setRGB1:
  while (!Serial.available());
  String color = Serial.readStringUntil('\n');
  color.trim();
  color.toUpperCase();
  bool isValid = false;
  for (uint8_t i = 0; i < sizeof(validCmd) / sizeof(validCmd[0]); i++) {
    if (color == "\0")
      goto waitCmd_setRGB1;
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
  uint8_t minVal, maxVal;
  getMinMax(cmd, color, minVal, maxVal);
  int val;
  bool outOfRange;
  do {
    Serial.print("Insert new value for " + color + " ("), Serial.print(minVal), Serial.print("-"), Serial.print(maxVal), Serial.print("): ");
    while (!Serial.available());
    val = Serial.readStringUntil('\n').toInt();
    Serial.println(val);
    if (val < minVal || val > maxVal) {
      outOfRange = true;
      Serial.println("Value out of range");
    }
    else
      outOfRange = false;
  } while (outOfRange);
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
      }
  }
  goto begin_setRGB;
}
void getMinMax(char channel, String color, uint8_t &minVal, uint8_t &maxVal) {
  const uint8_t absMin = 0, absMax = 255;
  if (channel == '1') {
    if (color == "LR") {
      minVal = absMin;
      maxVal = amber_HR_ch1;
    }
    else if (color == "HR") {
      minVal = amber_LR_ch1;
      maxVal = absMax;
    }
    else if (color == "LG") {
      minVal = absMin;
      maxVal = amber_HG_ch1;
    }
    else if (color == "HR") {
      minVal = amber_LG_ch1;
      maxVal = absMax;
    }
    else if (color == "LB") {
      minVal = absMin;
      maxVal = amber_HB_ch1;
    }
    else {
      minVal = amber_LB_ch1;
      maxVal = absMax;
    }
  }
  else {
    if (color == "LR") {
      minVal = absMin;
      maxVal = amber_HR_ch2;
    }
    else if (color == "HR") {
      minVal = amber_LR_ch2;
      maxVal = absMax;
    }
    else if (color == "LG") {
      minVal = absMin;
      maxVal = amber_HG_ch2;
    }
    else if (color == "HR") {
      minVal = amber_LG_ch2;
      maxVal = absMax;
    }
    else if (color == "LB") {
      minVal = absMin;
      maxVal = amber_HB_ch2;
    }
    else {
      minVal = amber_LB_ch2;
      maxVal = absMax;
    }
  }
}
