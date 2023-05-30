/*
   Test FlySky IBus interface on an Arduino Mega.
    Connect FS-iA6B receiver to Serial1.
*/

#include "FlySkyIBus.h"
int x = 0;
int y = 0;
int r = 0;
int l = 0;
void setup()
{
  Serial.begin(115200);
  IBus.begin(Serial3);
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  delay(2000);
}

void loop()
{
  IBus.loop();
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

    if(r>0){
      digitalWrite(4,0);
      digitalWrite(8,0);
      analogWrite(5,r);
      analogWrite(9,r);
    }
    else{
      digitalWrite(4,1);
      digitalWrite(8,1);
      analogWrite(5,-r);
      analogWrite(9,-r);
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
  Serial.println();
}
