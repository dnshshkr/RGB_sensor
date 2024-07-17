bool baudRateSetting() {
  Serial.println("[SETTINGS/Baud Rate]\n1: 9600\n2: 19200\n3: 38400\n4: 57600\n5: 74880\n6: 115200\nS: Back");
waitCmd_baudRateSetting:
  Serial.print("Selection: ");
  while (!Serial.available());
  char choice = toupper(Serial.readStringUntil('\r\n').charAt(0));
  Serial.println(choice);
  if (choice == 'S')
    return false;
  if (choice - '0' < 1 || choice - '0' > 6) {
    Serial.println("Invalid input");
    goto waitCmd_baudRateSetting;
  }
  uint32_t baudRate = getBaudRate(choice - '0' - 1);
  Serial.println("Baud rate changed to " + String(baudRate));
  return true;
}
uint32_t getBaudRate(uint8_t index) {
  static uint32_t values[] = {9600, 19200, 38400, 57600, 74880, 115200};
  uint32_t baudRate;
  if (index >= 0 && index < sizeof(values) / sizeof(values[0]))
    baudRate = values[index];
  else {
    baudRate = 9600;
    index = 0;
  }
  EEPROM.update(baudRate_addr, index);
  return baudRate;
}
