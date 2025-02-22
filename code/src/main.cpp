#include <Arduino.h>

const int toothCount = 174;

const int minRPM = 600;

const int maxRPM = 2200;

const int minPWR = 0;

const int maxPWR = 100;

int pulseHigh;

int pulseLow;

int dutyCycleRatio;

float freq;

int pulsePin = 12;

int val1 = 0;

bool beenHere;

float rpm;

int pwr = 0;

unsigned long previousMillis = 0;


ISR(TIMER1_COMPA_vect) {

  OCR1A += 111;

  if (beenHere) {

    TCCR2A = B00100011;
    TCCR2B = B00001100;

    OCR2A = 200;
    OCR2B = dutyCycleRatio;

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

int controlCurve(int rpm, int dragVarv, long accelerationTime)  {

  unsigned long currentMillis = millis();

  //TODO: make an actual accelerationTime
  unsigned long interval = 10;

  int pwrTarget;

  if (rpm >= dragVarv) {
  
    pwrTarget = map(rpm, dragVarv, maxRPM, minPWR, maxPWR);

  }
  else {
    pwrTarget = 0;
  }

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    if (pwr < pwrTarget) {
      pwr++;
    }
    else if (pwr > pwrTarget) {
      pwr--;
    }
  }

  return pwr;

}

int getRpm() {  //Fetches the engine RPM on pin 12

  float rpm; 

  pulseHigh = pulseIn(pulsePin, HIGH);
  pulseLow = pulseIn(pulsePin, LOW);
  freq = 1000000/(pulseHigh + pulseLow);

  rpm = (freq * 60) / toothCount;

  return rpm;
 
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

  rpm = getRpm();

  dutyCycleRatio = controlCurve(rpm, 1000, 1000);

  Serial.print(" RPM: "); 
  Serial.print(rpm);
  Serial.print( " Power: ");
  Serial.print(dutyCycleRatio);
  Serial.println();


}



