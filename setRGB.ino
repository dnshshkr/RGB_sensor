void setRGB()
{
begin_setRGB:
  Serial.print("\n[SETTINGS/");
  switch (cmd)
  {
    case '1':
      {
        Serial.println("AMBER CH1]");
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
        Serial.println("AMBER CH2]");
        Serial.println("LR: " + String(amber_LR_ch2));
        Serial.println("HR: " + String(amber_HR_ch2));
        Serial.println("LG: " + String(amber_LG_ch2));
        Serial.println("HG: " + String(amber_HG_ch2));
        Serial.println("LB: " + String(amber_LB_ch2));
        Serial.println("HB: " + String(amber_HB_ch2));
        break;
      }
  }
  Serial.print("s: Back");
  while (!Serial.available()) {}
  String color = Serial.readStringUntil('\r\n');
  color.trim();
  //  while (Serial.available())
  //    Serial.readStringUntil('\r\n');
  if (color == "s" || color == "S")
  {
    Serial.println();
    return;
  }
  Serial.print("\nInsert new value for ");
  if (color == '1')
    Serial.print("AMBER CH1 ");
  else if (color == '2')
    Serial.print("AMBER CH2");
  if (color == "lr" || color == "LR")
  {
    Serial.print("LR:");
    color = "LR";
  }
  else if (color == "hr" || color == "HR")
  {
    Serial.print("HR:");
    color = "HR";
  }
  else if (color == "lg" || color == "LG")
  {
    Serial.print("LG:");
    color = "LG";
  }
  else if (color == "hg" || color == "HG")
  {
    Serial.print("HG:");
    color = "HG";
  }
  else if (color == "lb" || color == "LB")
  {
    Serial.print("LB:");
    color = "LB";
  }
  else if (color == "hb" || color == "HB")
  {
    Serial.print("HB:");
    color = "HB";
  }
  while (!Serial.available()) {}
  String valStr = Serial.readStringUntil('\r\n');
  valStr.trim();
  float val = valStr.toFloat();
  switch (cmd)
  {
    case '1':
      {
        if (color == "LR")
        {
          EEPROM.put(amber_LR_addr_ch1, val);
          amber_LR_ch1 = val;
        }
        else if (color == "HR")
        {
          EEPROM.put(amber_HR_addr_ch1, val);
          amber_HR_ch1 = val;
        }
        else if (color == "LG")
        {
          EEPROM.put(amber_LG_addr_ch1, val);
          amber_LG_ch1 = val;
        }
        else if (color == "HG")
        {
          EEPROM.put(amber_HG_addr_ch1, val);
          amber_HG_ch1 = val;
        }
        else if (color == "LB")
        {
          EEPROM.put(amber_LB_addr_ch1, val);
          amber_LB_ch1 = val;
        }
        else if (color == "HB")
        {
          EEPROM.put(amber_HB_addr_ch1, val);
          amber_HB_ch1 = val;
        }
      }
    case '2':
      {
        if (color == "LR")
        {
          EEPROM.put(amber_LR_addr_ch2, val);
          amber_LR_ch2 = val;
        }
        else if (color == "HR")
        {
          EEPROM.put(amber_HR_addr_ch2, val);
          amber_HR_ch2 = val;
        }
        else if (color == "LG")
        {
          EEPROM.put(amber_LG_addr_ch2, val);
          amber_LG_ch2 = val;
        }
        else if (color == "HG")
        {
          EEPROM.put(amber_HG_addr_ch2, val);
          amber_HG_ch2 = val;
        }
        else if (color == "LB")
        {
          EEPROM.put(amber_LB_addr_ch2, val);
          amber_LB_ch2 = val;
        }
        else if (color == "HB")
        {
          EEPROM.put(amber_HB_addr_ch2, val);
          amber_HB_ch2 = val;
        }
      }
  }
  Serial.println();
  goto begin_setRGB;
}
