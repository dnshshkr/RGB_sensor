bool factoryReset() {
  Serial.print("[SETTINGS/Factory Reset]\nAre you sure? (Y): ");
  int8_t cd = 11;
  char choice;
  unsigned long prevmillis;
  //  Serial.print(cd);
  do {
    if (millis() - prevmillis >= 1000)
    {
      cd--;
      cd >= 0 ? Serial.print(String(cd) + " ") : 0;
      prevmillis = millis();
    }
  } while (!Serial.available() && cd >= 0);
  if (Serial.available())
    choice = Serial.readStringUntil('\r\n').charAt(0);
  else
    choice = 'N';
  //  Serial.println(String(choice));
  Serial.println();
  if (toupper(choice) != 'Y') {
    Serial.println("Factory reset cancelled");
    return false;
  }
  Serial.println("Resetting all " + String(EEPROM.length()) + " bytes...");
  for (uint32_t i = 0; i < EEPROM.length(); i++)
    EEPROM.update(i, 255);
  Serial.println("Factory reset successful");
  return true;
}
