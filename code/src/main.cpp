#include <Arduino.h>

int dutyCycle = 0;

void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  //TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2A = B01100011;
  //TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20);
  TCCR2B = B00001111;
  OCR2A = 200;
  OCR2B = 50;
  
}

void loop() {

  int x = analogRead(A0);

  dutyCycle = map(x, 0, 1023, 0, 219);

  //OCR2B = dutyCycle;


}

