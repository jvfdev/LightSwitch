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

// alarm button vars
const int alarmButtonPin = 10;
const int LONG_PRESS_TIME  = 1000; // milliseconds

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

// plus button vars
const int plusButtonPin = 11;

// minus button vars
const int minusButtonPin = 12;


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
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);


void setup() {
  rtc.begin();
  //  rtc.adjust(DateTime(2022, 1, 16, 11, 58, 0));
  pinMode(lightSwitchPin, INPUT_PULLUP);
  pinMode(alarmButtonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(16, 2);
  lcd.home();
  lcd.print("YYYY-MM-DD HH:MM");
  lcd.setCursor(0, 1);
  lcd.print("Alarm: Disabled");

  Serial.begin(9600);
  Serial.println("Initialized");
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
      if (!buttonAlreadyPressed) {

        light = !light;
        Serial.println("Flip!");
        digitalWrite(LED_BUILTIN, light);

        if (light) {
          servoOn();
        }
        else {
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

  //update display on LCD
  rtcTime = rtc.now();
  YYYY = rtcTime.year();
  MM = rtcTime.month();
  DD = rtcTime.day();
  hh = rtcTime.hour();
  mm = rtcTime.minute();
  ss = rtcTime.second();

  updateTimeLCD();
  CheckAlarmButtonPress();
}

void CheckAlarmButtonPress() {
  currentState = digitalRead(alarmButtonPin);
  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < 20) {
      Serial.println("Bounce detected");
    }
    else if (pressDuration < LONG_PRESS_TIME) {
      Serial.println("Short press detected");
    }
    else{
      Serial.println("long press detected");
    }
  }

  // save the the last state
  lastState = currentState;

}
