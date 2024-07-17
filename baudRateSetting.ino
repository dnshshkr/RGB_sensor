bool baudRateSetting() {
  Serial.println("Choose new baud rate\n1: 9600\n2: 19200\n3: 38400\n4: 57600\n5: 74880\n6: 115200\nS: Back");
waitCmd_baudRateSetting:
  while (!Serial.available());
  char choice = Serial.readStringUntil('\r\n').charAt(0);
  if (String("sS").indexOf(choice) != -1)
    return false;
  if (choice - '0' < 1 or choice - '0' > 6) {
    Serial.println("Invalid input");
    goto waitCmd_baudRateSetting;
  }
  uint32_t baudRate = getBaudRate(choice - '0' - 1);
  //  EEPROM.write(baudRate_addr, baudRate);
  Serial.println("Baud rate changed to " + String(baudRate));
  //  EEPROM.update(baudRate_addr, choice - '0' - 1);
  return true;
}
uint32_t getBaudRate(uint8_t index) {
  uint32_t baudRate;
  switch (index) {
    case 0: {
        baudRate = 9600;
        break;
      }
    case 1: {
        baudRate = 19200;
        break;
      }
    case 2: {
        baudRate = 38400;
        break;
      }
    case 3: {
        baudRate = 57600;
        break;
      }
    case 4: {
        baudRate = 74880;
        break;
      }
    case 5: {
        baudRate = 115200;
        break;
      }
    default: {
        baudRate = 9600;
        index = 0;
      }
  }
  EEPROM.update(baudRate_addr, index);
  return baudRate;
}
