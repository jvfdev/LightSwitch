 char dateTimeString[16];

void updateTimeLCD(){
  sprintf(dateTimeString, "%04u-%02u-%02u %02u:%02u",  YYYY,MM,DD,hh,mm);
  lcd.home();
  lcd.print(dateTimeString);
}
