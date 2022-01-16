#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

// light switch button vars
const int lightSwitchPin = 8;
bool lightSwitchButton = false;
bool lightSwitchPrevPress = false;
bool light = false;
bool buttonAlreadyPressed = true;
int t0;

RTC_DS3231 rtc;
DateTime rtcTime;
int ss;
int mm;
int hh;
int DD;
int MM;
int YYYY;
int dayOfWeek;


//LCD vars
LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);


void setup() {
  rtc.begin();
  rtc.adjust(DateTime(2022, 1, 15, 18, 25, 0));
  pinMode(lightSwitchPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  lcd.begin(16,2);
  lcd.home();
  lcd.print("YYYY-MM-DD HH:MM");
  lcd.setCursor(0,1);
  lcd.print("Alarm: Disabled");
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSwitchButton = !digitalRead(lightSwitchPin); // invert so that when button pressed, read as true
  //  digitalWrite(LED_BUILTIN, lightSwitch);

  if (lightSwitchButton) {
    if (!lightSwitchPrevPress) {
      // if not previously pressed, start the timer
      t0 = millis();
      
    }
    else if (millis() - t0 > 10) {
      if(!buttonAlreadyPressed){
        
        light = !light;
        Serial.println("Flip!");
        digitalWrite(LED_BUILTIN, light);
        
        if(light){
          servoOn();
        }
        else{
          servoOff();
        }
        buttonAlreadyPressed = true;
      }
      
    }

    lightSwitchPrevPress = true;

  }
  else {
    lightSwitchPrevPress = false;
    buttonAlreadyPressed = false;
  }

  detachServoTimer(1000);
  
}
