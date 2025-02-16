#include <Arduino.h>

int pulseHigh;

int pulseLow;

float freq;

int pulsePin = 12;

int val1 = 0;

bool beenHere;

float rpm;


ISR(TIMER1_COMPA_vect) {

  OCR1A += 111;

  if (beenHere) {

    TCCR2A = B00100011;
    TCCR2B = B00001100;

    int val2 = ((val1 / 100) * 200);

    OCR2A = 200;
    OCR2B = val2;

    beenHere = false;
  }

  else {

    /*
    For two different PWM signals

    OCR2A = 255;
    OCR2B = 1;
    */

    TCCR2A = 0;
    TCCR2B = 0;

    beenHere = true;
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(3, OUTPUT);   //Drive signal
  

  pinMode(12, INPUT);


  TCCR2A = B00100011;   //Clear OC2B on compare match, set OC2B at BOTTOM
  TCCR2B = B00001100;   //Prescaler = 64, Fast PWM (Mode 7, se datasheet)

  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B = B00000101;  // Prescaler = 1024
  OCR1A = 111;        // Timer Compare1A Register
  //OCR1B = 333;
  TIMSK1 = B00000010;  // Enable Timer COMPA Interrupt

}

void loop() {

  /*

  pulseHigh = pulseIn(pulsePin, HIGH);
  pulseLow = pulseIn(pulsePin, LOW);
  freq = 1000000/(pulseHigh + pulseLow);

  rpm = (freq * 60)/174;

  Serial.print(freq);
  Serial.print(" : ");
  Serial.print(rpm);
  Serial.println();
  */

  val1 = 100;


}



