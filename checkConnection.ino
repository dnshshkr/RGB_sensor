bool checkConnection()
{
  Wire.beginTransmission(TCS34725_ADDRESS);
  return (Wire.endTransmission() == 0);
}
