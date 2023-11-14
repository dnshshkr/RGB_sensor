void setRGB()
{
begin_setRGB:
  Serial.print("\n[SETTINGS/");
  switch (cmd)
  {
    case '1':
      {
        Serial.println("RED]");
        Serial.println("LR: " + String(red_LR));
        Serial.println("HR: " + String(red_HR));
        Serial.println("LG: " + String(red_LG));
        Serial.println("HG: " + String(red_HG));
        Serial.println("LB: " + String(red_LB));
        Serial.println("HB: " + String(red_HB));
        break;
      }
    case '2':
      {
        Serial.println("AMBER]");
        Serial.println("LR: " + String(amber_LR));
        Serial.println("HR: " + String(amber_HR));
        Serial.println("LG: " + String(amber_LG));
        Serial.println("HG: " + String(amber_HG));
        Serial.println("LB: " + String(amber_LB));
        Serial.println("HB: " + String(amber_HB));
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
    Serial.print("RED ");
  else if (color == '2')
    Serial.print("AMBER ");
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
  if (cmd == '1')
  {
    if (color == "LR")
    {
      EEPROM.put(red_LR_addr, val);
      red_LR = val;
    }
    else if (color == "HR")
    {
      EEPROM.put(red_HR_addr, val);
      red_HR = val;
    }
    else if (color == "LG")
    {
      EEPROM.put(red_LG_addr, val);
      red_LG = val;
    }
    else if (color == "HG")
    {
      EEPROM.put(red_HG_addr, val);
      red_HG = val;
    }
    else if (color == "LB")
    {
      EEPROM.put(red_LB_addr, val);
      red_LB = val;
    }
    else if (color == "HB")
    {
      EEPROM.put(red_HB_addr, val);
      red_HB = val;
    }
  }
  else if (cmd == '2')
  {
    if (color == "LR")
    {
      EEPROM.put(amber_LR_addr, val);
      amber_LR = val;
    }
    else if (color == "HR")
    {
      EEPROM.put(amber_HR_addr, val);
      amber_HR = val;
    }
    else if (color == "LG")
    {
      EEPROM.put(amber_LG_addr, val);
      amber_LG = val;
    }
    else if (color == "HG")
    {
      EEPROM.put(amber_HG_addr, val);
      amber_HG = val;
    }
    else if (color == "LB")
    {
      EEPROM.put(amber_LB_addr, val);
      amber_LB = val;
    }
    else if (color == "HB")
    {
      EEPROM.put(amber_HB_addr, val);
      amber_HB = val;
    }
  }
  Serial.println();
  goto begin_setRGB;
}
