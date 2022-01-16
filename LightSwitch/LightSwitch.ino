#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
DateTime rtcTime;
int ss;
int mm;
int hh;
int DD;
int MM;
int YYYY;
int dayOfWeek;


void setup() {
  rtc.begin();
  rtc.adjust(DateTime(2022,1,15,18,25,0));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
