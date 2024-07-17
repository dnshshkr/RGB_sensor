void settings()
{
  flushSerial();
begin_settings:
  Serial.println("Ver. " + String(VERSION));
  Serial.println("[SETTINGS]");
  Serial.println("1: Yellow Ch1");
  Serial.println("2: Yellow Ch2");
  Serial.print("3: Relay Type: Active "), relayType ? Serial.println("High") : Serial.println("Low");
  Serial.println("4: Baud Rate: " + String(getBaudRate(EEPROM.read(baudRate_addr))));
  Serial.println("5: Integration Time: " + String(getIntegTime(EEPROM.read(integTime_addr))) + " ms");
  Serial.println("6: Gain: " + String(getGain(EEPROM.read(gain_addr))) + "x");
  Serial.println("7: Reboot");
  Serial.println("8: Factory Reset");
  Serial.println("S: Exit");
waitCmd_settings:
  while (!Serial.available());
  cmd = toupper(Serial.readStringUntil('\r\n').charAt(0));
  switch (cmd) {
    case '1': case '2': {
        setRGB();
        goto begin_settings;
      }
    case '3': {
        relayType = !relayType;
        EEPROM.update(relayType_addr, relayType);
        goto begin_settings;
      }
    case '4': {
        if (baudRateSetting())
          reboot();
        else
          goto begin_settings;
      }
    case '5': {
        integrationTimeSetting();
        goto begin_settings;
      }
    case '6': {
        gainSetting();
        goto begin_settings;
      }
    case '7':
      reboot();
    case '8': {
        if (factoryReset())
          reboot();
        else
          goto begin_settings;
      }
    case 'S':
      return;
    default: {
        Serial.println("Invalid command");
        goto waitCmd_settings;
      }
  }
}
