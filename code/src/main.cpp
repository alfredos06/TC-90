#include <Arduino.h>

int dutyCycle = 0;

void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(11, OUTPUT);

  
  TCCR1A = B10100011;
  TCCR1B = B00010101;


  OCR1A = 222; //FREQ
  OCR1B = 22; //Duty-Cycle
  
 
  TCCR2A = B00100011;
  TCCR2B = B00001111;

  OCR2A = 222;
  OCR2B = 20;
 

  

}

void loop() {

  int x = analogRead(A0);

  dutyCycle = map(x, 0, 1023, 0, 222);

  OCR2B = dutyCycle;


}

