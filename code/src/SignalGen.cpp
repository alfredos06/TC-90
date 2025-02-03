#include <Arduino.h>

int input;


void setup() {

    pinMode(3, OUTPUT);

    pinMode(A0, INPUT);

    TCCR2A = B00100011;
    TCCR2B = B00001011;

    //min 79


    OCR2A = 255;
    OCR2B = OCR2A / 2;

    //max 255


}

void loop() {


    input = analogRead(A0);

    int signal =  map(input, 0, 1023, 79, 255);

    OCR2A = signal;
    OCR2B = signal / 2;



}


