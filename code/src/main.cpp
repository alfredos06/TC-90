#include <Arduino.h>

int dutyCycle = 0;

int pulseHigh;

int pulseLow;

float freq;

int pulsePin = 12;

bool beenHere;

float rpm;

// volatile byte fast = LOW;




  //NOTE: Use another timer which is creates the 70Hz dither which then trigers fast PWM.




ISR(TIMER1_COMPA_vect) {

  OCR1A += 111;


  //digitalWrite(3, !digitalRead(3));

  if (beenHere) {
    OCR2A = 50;
    OCR2B = 40;

    //digitalWrite(3, LOW);

    beenHere = false;

    //Serial.println("LOW");
  }
  else {
    OCR2A = 0;
    OCR2B = 0;

    //digitalWrite(3, LOW);

    beenHere = true;

    //Serial.println("HIGH");

  }

}

/*

ISR(TIMER1_COMPB_vect) {

  OCR1A += 333;

  OCR2A = 0;
  OCR2B = 0;

  //digitalWrite(3, LOW);
}

*/

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

