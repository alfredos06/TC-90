#include <Arduino.h>

int dutyCycle = 0;

int pulseHigh;

int pulseLow;

float freq;

int pulsePin = 12;

// volatile byte fast = LOW;




  //NOTE: Use another timer which is creates the 70Hz dither which then trigers fast PWM.



void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);   //Drive signal
  pinMode(10, OUTPUT);  //Dither

  pinMode(12, INPUT);
  //attachInterrupt(digitalPinToInterrupt(3), fast, CHANGE);


  /*
  TCCR1A = B10100011;
  TCCR1B = B00010101;


  OCR1A = 222; //FREQ
  OCR1B = 22; //Duty-Cycle
  
 
  TCCR2A = B00100011;
  TCCR2B = B00001111;

  OCR2A = 222;
  OCR2B = 111;
*/
}

void loop() {

/*
  pulseHigh = pulseIn(pulsePin, HIGH);
  pulseLow = pulseIn(pulsePin, LOW);
  freq = 1000000/(pulseHigh + pulseLow);
  Serial.println(freq);
*/

  digitalWrite(3, HIGH);
  analogWrite(3, 127);
  delay(10);
  digitalWrite(3, LOW);
  delay(10);

   
}

