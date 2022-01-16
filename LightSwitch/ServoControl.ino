const int angleWhenOn = 135;
const int angleWhenOff = 45;

void servoOn(){
  myServo.attach(servoPin);
  myServo.write(angleWhenOn);
}

void servoOff(){
  myServo.write(angleWhenOff);
}
