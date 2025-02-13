#include <Arduino.h>

int dutyCycle = 0;

int pulseHigh;

int pulseLow;

float freq;

int pulsePin = 12;

bool beenHere;

float rpm;


ISR(TIMER1_COMPA_vect) {

  OCR1A += 111;

  if (beenHere) {
    OCR2A = 50;
    OCR2B = 50;

    beenHere = false;

  }

  
  else {
    OCR2A = 255;
    OCR2B = 0;

    beenHere = true;

  }
  

}



void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);   //Drive signal
  

  pinMode(12, INPUT);



  /*
  TCCR1A = B10100011;
  TCCR1B = B00010101;


  OCR1A = 222; //FREQ
  OCR1B = 22; //Duty-Cycle
  */


  TCCR2A = B00100011;
  TCCR2B = B00001110;

  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000101;  // Prescaler = 1024
  OCR1A = 111;        // Timer Compare1A Register
  //OCR1B = 333;
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt

}

void loop() {

  pulseHigh = pulseIn(pulsePin, HIGH);
  pulseLow = pulseIn(pulsePin, LOW);
  freq = 1000000/(pulseHigh + pulseLow);

  rpm = (freq * 60)/174;

  Serial.print(freq);
  Serial.print(" : ");
  Serial.print(rpm);
  Serial.println();


  


}

