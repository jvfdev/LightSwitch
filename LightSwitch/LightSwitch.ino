#include <Wire.h>
#include <RTClib.h>

int lightSwitchPin = 7;
bool lightSwitch = false;

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
  pinMode(lightSwitchPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSwitch = digitalRead(lightSwitchPin);
  digitalWrite(LED_BUILTIN, lightSwitch);
}
