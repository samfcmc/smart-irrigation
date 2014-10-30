#include <Arduino.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 7;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(13, OUTPUT);
}

int delayamount = 1000;

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);
  digitalWrite(13, LOW);
  delay(delayamount);
  digitalWrite(led, LOW);
  digitalWrite(13, HIGH);
  delay(delayamount);
}