void settings()
{
  while (Serial.available())
    Serial.readStringUntil('\r\n');
enterSettings:
  Serial.println("Ver. " + String(VERSION));
  Serial.println("[SETTINGS]");
  Serial.println("1: Amber Ch1");
  Serial.println("2: Amber Ch2");
  Serial.print("3: Relay Type: Active "), relayType ? Serial.println("High") : Serial.println("Low");
  Serial.println("4: Factory Reset");
  Serial.println("S: Exit");
getSettingsCmd:
  while (!Serial.available()) {}
  cmd = Serial.readStringUntil('\r\n').charAt(0);
  //  while (Serial.available())
  //    Serial.readStringUntil('\r\n');
  switch (cmd)
  {
    case '1': case '2':
      {
        setRGB();
        goto enterSettings;
      }
    case '3':
      {
        relayType = !relayType;
        EEPROM.update(relayType_addr, relayType);
        goto enterSettings;
      }
    case '4':
      {
        factoryReset();
        goto enterSettings;
      }
    case 's': case 'S':
      {
        //        Serial.println();
        return;
      }
    default:
      {
        Serial.println("Invalid command");
        //        delay(1000);
        //        Serial.println();
        goto getSettingsCmd;
      }
  }
}
