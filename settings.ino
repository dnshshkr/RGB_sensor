void settings()
{
  while (Serial.available())
    Serial.readStringUntil('\r\n');
enterSettings:
  Serial.println("\n[SETTINGS]");
  Serial.println("1: Amber CH1");
  Serial.println("2: Amber CH2");
  Serial.print("3: Relay type: "), relayType ? Serial.println("Active high") : Serial.println("Active low");
  Serial.println("s: Exit");
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
    case 's':
      {
        Serial.println();
        return;
      }
    default:
      {
        Serial.print("Invalid command");
        delay(1000);
        Serial.println();
        goto enterSettings;
      }
  }
}
