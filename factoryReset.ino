void factoryReset()
{
  char choice;
  Serial.print("[SETTINGS/Factory Reset]\nAre you sure? (Y): ");
  while (!Serial.available());
  choice = Serial.readStringUntil('\r\n').charAt(0);
  Serial.println(choice);
  if (toupper(choice) != 'Y')
  {
    Serial.println("Factory reset cancelled");
    return;
  }
  Serial.println("Resetting all " + String(EEPROM.length()) + " bytes...");
  for (uint32_t i = 0; i < EEPROM.length(); i++)
    EEPROM.update(i, 255);
  Serial.println("Factory reset successful");
  return;
}
