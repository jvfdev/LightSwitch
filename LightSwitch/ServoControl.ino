#include <Servo.h>

Servo myServo;
const int angleWhenOn = 135;
const int angleWhenOff = 45;

const int servoPin = 9;
long servoTimer;

void servoOn() {
  myServo.attach(servoPin);
  servoTimer = millis();
  myServo.write(angleWhenOn);
}

void servoOff() {
  myServo.attach(servoPin);
  servoTimer = millis();
  myServo.write(angleWhenOff);
}

void detachServoTimer(int waitTimeMs) {
  if (myServo.attached()) {
    if (millis() - servoTimer > waitTimeMs) {
      myServo.detach();
      Serial.println("detaching");

    }
  }
}
