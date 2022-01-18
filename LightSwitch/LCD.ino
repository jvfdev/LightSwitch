char dateTimeString[16];

void updateTimeLCD() {
  sprintf(dateTimeString, "%04u-%02u-%02u %02u:%02u",  YYYY, MM, DD, hh, mm);
  lcd.home();
  lcd.print(dateTimeString);
}

void updateAlarmDisplay(bool enabled){
  lcd.setCursor(0,1);
  if(enabled){
    lcd.print("Alarm: Enabled ");
  }
  else{
    lcd.print("Alarm: Disabled");
  }
}
