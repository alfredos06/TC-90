#include <Arduino.h>

int dutyCycle = 0;
// volatile byte fast = LOW;




  //NOTE: Use another timer which is creates the 70Hz dither which then trigers fast PWM.


void fast() {

  if (digitalRead(3) == LOW) {
    OCR2A = 222;
    OCR2B = 111;
  }
  else {
    OCR2A = 50;
    OCR2B = 25; 
  }
  
}

void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);   //Drive signal
  pinMode(10, OUTPUT);  //Dither

  attachInterrupt(digitalPinToInterrupt(3), fast, CHANGE);



  //TCCR1A = B10100011;
  //TCCR1B = B00010101;


  //OCR1A = 222; //FREQ
  //OCR1B = 22; //Duty-Cycle
  
 
  TCCR2A = B00100011;
  TCCR2B = B00001111;

  //OCR2A = 222;
  //OCR2B = 111;

  OCR2A = 222;
  OCR2B = 111;
}

void loop() {

  /*

  int x = analogRead(A0);

  dutyCycle = map(x, 0, 1023, 0, 255);

  Serial.println(dutyCycle);
  //OCR2B = dutyCycle;

  */
 
  /*
  digitalWrite(3, HIGH);
  analogWrite(3, dutyCycle);
  delay(10);
  digitalWrite(3, LOW);
  delay(10);
  */

    OCR2A = 222;
    OCR2B = 111;

}

