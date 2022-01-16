#include <Wire.h>
#include <RTClib.h>
//

// light switch vars
int lightSwitchPin = 7;
bool lightSwitchButton = false;
bool lightSwitchPrevPress = false;
bool light = false;
bool buttonAlreadyPressed = true;
int t0;


const int servoPin = 9;
long servoTimer;
int servoWaitTimems = 1000; // wait in ms before detaching servo (time to complete motion)

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
  rtc.adjust(DateTime(2022, 1, 15, 18, 25, 0));
  pinMode(lightSwitchPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
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
//        myServo.attach(servoPin);
        
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
