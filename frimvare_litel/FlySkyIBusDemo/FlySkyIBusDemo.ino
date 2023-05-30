/*
   Test FlySky IBus interface on an Arduino Mega.
    Connect FS-iA6B receiver to Serial1.
*/
#include "DxlMaster.h"
#include "FlySkyIBus.h"
// id of the motor
const uint8_t id3 = 2;
const uint8_t id2 = 1;
const uint8_t id1 = 8;
// speed, between 0 and 1023
int16_t speed = 512;
// communication baudrate
const long unsigned int baudrate = 1000000;
DynamixelMotor motor3(id3);
DynamixelMotor motor2(id2);
DynamixelMotor motor1(id1);
int x = 0;
int y = 0;
int r = 0;
int l = 0;
int j = 0;
int sw = 0;
int grip = 0;
void setup()
{
  DxlMaster.begin(baudrate);
  delay(100);

  // check if we can communicate with the motor
  // if not, we stop here
  uint8_t status = motor2.init();
  if (status != DYN_STATUS_OK)
  {
    while (1);
  }

  motor2.enableTorque();
  motor1.enableTorque();
  motor3.enableTorque();

  // set to joint mode, with a 180° angle range
  // see robotis doc to compute angle values
  motor2.jointMode(204, 820);
  motor2.speed(speed);

  motor1.jointMode(204, 820);
  motor1.speed(speed);

  motor3.jointMode(204, 820);
  motor3.speed(speed);


  Serial.begin(115200);
  IBus.begin(Serial3);
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  delay(2000);
  motor2.goalPosition(712);
  motor1.goalPosition(712);
  motor3.goalPosition(800);
  delay(500);
}

void loop()
{
  IBus.loop();
  j = IBus.readChannel(2);
  sw = IBus.readChannel(4);
  grip = IBus.readChannel(5);
  
  x = IBus.readChannel(0);
  x = map(x, 1000, 2000, -255, 255);
  if ((x < 50) && (x > -50)) {
    x = 0;
  }
  if (x > 150) {
    x = 255;
  }
  if (x < -150) {
    x = -255;
  }
  y = IBus.readChannel(1);
  y = map(y, 1000, 2000, -255, 255);
  if ((y < 50) && (y > -50)) {
    y = 0;
  }
  if (y > 150) {
    y = 255;
  }
  if (y < -150) {
    y = -255;
  }
  l = x + y;
  r = y - x;
  if ((r < 50) && (r > -50)) {
    r = 0;
  }
  if (r > 150) {
    r = 255;
  }
  if (r < -150) {
    r = -255;
  }
  if ((l < 50) && (l > -50)) {
    l = 0;
  }
  if (l > 150) {
    l = 255;
  }
  if (l < -150) {
    l = -255;
  }

  if (l > 0) {
    digitalWrite(6, 1);
    analogWrite(7, l);
    digitalWrite(2, 1);
    analogWrite(3, l);
  }
  else {
    digitalWrite(6, 0);
    analogWrite(7, -l);
    digitalWrite(2, 0);
    analogWrite(3, -l);

  }
  if (l == 0) {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 0);

  }

  if (r > 0) {
    digitalWrite(4, 0);
    digitalWrite(8, 0);
    analogWrite(5, r);
    analogWrite(9, r);
  }
  else {
    digitalWrite(4, 1);
    digitalWrite(8, 1);
    analogWrite(5, -r);
    analogWrite(9, -r);
  }
  //  if(r==0){
  //    digitalWrite(6,0);
  //    digitalWrite(7,0);
  //    digitalWrite(8,0);
  //    digitalWrite(9,0);
  //  }


  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.print("  ");
  Serial.print(l);
  Serial.print("  ");
  Serial.print(r);
  Serial.print("  ");
  Serial.print(j);
  Serial.print("  ");
  Serial.print(sw);
  Serial.print("  ");
  Serial.print(grip);
  Serial.println();
}
