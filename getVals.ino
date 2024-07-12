void getVals()
{
  EEPROM.get(amber_LR_addr_ch1, amber_LR_ch1);
  EEPROM.get(amber_HR_addr_ch1, amber_HR_ch1);
  EEPROM.get(amber_LG_addr_ch1, amber_LG_ch1);
  EEPROM.get(amber_HG_addr_ch1, amber_HG_ch1);
  EEPROM.get(amber_LB_addr_ch1, amber_LB_ch1);
  EEPROM.get(amber_HB_addr_ch1, amber_HB_ch1);

  EEPROM.get(amber_LR_addr_ch2, amber_LR_ch2);
  EEPROM.get(amber_HR_addr_ch2, amber_HR_ch2);
  EEPROM.get(amber_LG_addr_ch2, amber_LG_ch2);
  EEPROM.get(amber_HG_addr_ch2, amber_HG_ch2);
  EEPROM.get(amber_LB_addr_ch2, amber_LB_ch2);
  EEPROM.get(amber_HB_addr_ch2, amber_HB_ch2);
  return;
}
