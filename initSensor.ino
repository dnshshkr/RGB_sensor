void initSensor()
{
  Serial.println("Setting up sensor...");
  bool bl = true;
  unsigned long prevmillis;
  bool sensorInit = tcs.begin();
  while (!sensorInit)
  {
    relayType ? digitalWrite(amberPin, LOW) : digitalWrite(amberPin, HIGH);
    if (Serial.available())
    {
      if (tolower(Serial.readStringUntil('\t\n').charAt(0)) == 's')
        settings();
    }
    if (prevmillis == 0 || millis() - prevmillis >= 500)
    {
      bl = !bl;
      Serial.println("Sensor error (Press 's' to enter settings)");
      relayType ? digitalWrite(runPin, bl) : digitalWrite(runPin, !bl);
      digitalWrite(LED_BUILTIN, bl);
      sensorInit = tcs.begin();
      prevmillis = millis();
    }
  }
  Serial.println("Ready");
  relayType ? digitalWrite(runPin, HIGH) : digitalWrite(runPin, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
}
