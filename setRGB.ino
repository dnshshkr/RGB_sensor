void setRGB()
{
begin_setRGB:
  getVals();
  Serial.print("[SETTINGS/");
  switch (cmd)
  {
    case '1':
      {
        Serial.println("Amber Ch1]");
        Serial.println("LR: " + String(amber_LR_ch1));
        Serial.println("HR: " + String(amber_HR_ch1));
        Serial.println("LG: " + String(amber_LG_ch1));
        Serial.println("HG: " + String(amber_HG_ch1));
        Serial.println("LB: " + String(amber_LB_ch1));
        Serial.println("HB: " + String(amber_HB_ch1));
        break;
      }
    case '2':
      {
        Serial.println("Amber Ch2]");
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
getRGBCmd:
  while (!Serial.available());
  String color = Serial.readStringUntil('\r\n');
  color.trim();
  color.toUpperCase();
  if (String("SLRHRLGHGLBHB").indexOf(color) == -1)
  {
    Serial.println("Invalid command");
    goto getRGBCmd;
  }
  if (color == "S")
    return;
  Serial.print("Insert new value for " + color + ": ");
  while (!Serial.available());
  String valStr = Serial.readStringUntil('\r\n');
  valStr.trim();
  float val = valStr.toFloat();
  Serial.println(val);
  switch (cmd)
  {
    case '1':
      {
        if (color == "LR")
          EEPROM.put(amber_LR_addr_ch1, val);
        else if (color == "HR")
          EEPROM.put(amber_HR_addr_ch1, val);
        else if (color == "LG")
          EEPROM.put(amber_LG_addr_ch1, val);
        else if (color == "HG")
          EEPROM.put(amber_HG_addr_ch1, val);
        else if (color == "LB")
          EEPROM.put(amber_LB_addr_ch1, val);
        else if (color == "HB")
          EEPROM.put(amber_HB_addr_ch1, val);
        break;
      }
    case '2':
      {
        if (color == "LR")
          EEPROM.put(amber_LR_addr_ch2, val);
        else if (color == "HR")
          EEPROM.put(amber_HR_addr_ch2, val);
        else if (color == "LG")
          EEPROM.put(amber_LG_addr_ch2, val);
        else if (color == "HG")
          EEPROM.put(amber_HG_addr_ch2, val);
        else if (color == "LB")
          EEPROM.put(amber_LB_addr_ch2, val);
        else if (color == "HB")
          EEPROM.put(amber_HB_addr_ch2, val);
        break;
      }
  }
  Serial.println();
  goto begin_setRGB;
}
