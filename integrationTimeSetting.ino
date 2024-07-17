void integrationTimeSetting() {
  Serial.println("Choose new integration time (ms):\n1: 2.4\n2: 24\n3: 50\n4: 60\n5: 101\n6: 120\n7: 154\n8: 180\n9: 199\n10: 240\n11: 300\n12: 360\n13: 401\n14: 420\n15: 480\n16: 499\n17: 540\n18: 600\n19: 614\nS: Back");
waitCmd_integrationTimeSetting:
  while (!Serial.available());
  String choiceStr = Serial.readStringUntil('\r\n');
  choiceStr.trim();
  choiceStr.toUpperCase();
  if (choiceStr == "S")
    return;
  uint8_t choice = choiceStr.toInt();
  if (choice < 1 or choice > 19) {
    Serial.println("Invalid input");
    goto waitCmd_integrationTimeSetting;
  }
  setIntegTime(choice - 1);
  float integTime = getIntegTime(choice - 1);
  Serial.println("Integration time set to " + String(integTime));
  //  EEPROM.update(integTime_addr, choice - 1);
  return;
}
float getIntegTime(uint8_t index) {
  if (index == 0)
    return 2.4;
  else if (index == 1)
    return 24.0;
  else if (index == 2)
    return 50.0;
  else if (index == 3)
    return 60.0;
  else if (index == 4)
    return 101.0;
  else if (index == 5)
    return 120.0;
  else if (index == 6)
    return 154.0;
  else if (index == 7)
    return 180.0;
  else if (index == 8)
    return 199.0;
  else if (index == 9)
    return 240.0;
  else if (index == 10)
    return 300.0;
  else if (index == 11)
    return 360.0;
  else if (index == 12)
    return 401.0;
  else if (index == 13)
    return 420.0;
  else if (index == 14)
    return 480.0;
  else if (index == 15)
    return 499.0;
  else if (index == 16)
    return 540.0;
  else if (index == 17)
    return 600.0;
  else if (index == 18)
    return 614.0;
}
void setIntegTime(uint8_t index) {
  switch (index) {
    case 0: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_2_4MS);
        break;
      }
    case 1: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_24MS);
        break;
      }
    case 2: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
        break;
      }
    case 3: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_60MS);
        break;
      }
    case 4: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_101MS);
        break;
      }
    case 5: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_120MS);
        break;
      }
    case 6: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
        break;
      }
    case 7: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_180MS);
        break;
      }
    case 8: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_199MS);
        break;
      }
    case 9: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_240MS);
        break;
      }
    case 10: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_300MS);
        break;
      }
    case 11: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_360MS);
        break;
      }
    case 12: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_401MS);
        break;
      }
    case 13: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_420MS);
        break;
      }
    case 14: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_480MS);
        break;
      }
    case 15: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_499MS);
        break;
      }
    case 16: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_540MS);
        break;
      }
    case 17: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_600MS);
        break;
      }
    case 18: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_614MS);
        break;
      }
    default: {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
        index = 2;
      }
  }
  EEPROM.update(integTime_addr, index);
}
