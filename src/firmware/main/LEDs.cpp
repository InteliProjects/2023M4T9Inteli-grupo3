#include "LEDs.h"

LEDs::LEDs(int redLED, int rgbRed, int rgbGreen, int rgbBlue){
  this->redLED    = redLED;
  this->rgbRed    = rgbRed;
  this->rgbGreen  = rgbGreen;
  this->rgbBlue   = rgbBlue;
}

void LEDs::iniciar(){
  pinMode(redLED, OUTPUT);
  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
}


void LEDs::ligarRedLED(){
  digitalWrite(redLED, HIGH);

}

void LEDs::desligarLED(){
  digitalWrite(redLED, LOW);
}

void LEDs::rgbVermelho(){
  digitalWrite(rgbRed, HIGH);
  digitalWrite(rgbGreen, LOW);
  digitalWrite(rgbBlue, LOW);
}

void LEDs::rgbVerde(){
  digitalWrite(rgbGreen, HIGH);
  digitalWrite(rgbRed, LOW);
  digitalWrite(rgbBlue, LOW);
}

void LEDs::rgbAzul(){
  digitalWrite(rgbBlue, HIGH);
  digitalWrite(rgbRed, LOW);
  digitalWrite(rgbGreen, LOW);
}

void LEDs::rgbBranco(){
  digitalWrite(rgbRed, HIGH);
  digitalWrite(rgbGreen, HIGH);
  digitalWrite(rgbBlue, HIGH);
}

void LEDs::rgbMagenta(){
  digitalWrite(rgbRed, HIGH);
  digitalWrite(rgbBlue, HIGH);
  digitalWrite(rgbGreen, LOW);
}

void LEDs::rgbAmarelo(){
  digitalWrite(rgbRed, HIGH);
  digitalWrite(rgbGreen, HIGH);
  digitalWrite(rgbBlue, LOW);
}

void LEDs::rgbCiano(){
  digitalWrite(rgbGreen, HIGH);
  digitalWrite(rgbBlue, HIGH);
  digitalWrite(rgbRed, LOW);
}

void LEDs::rgbOff(){
  digitalWrite(rgbRed, LOW);
  digitalWrite(rgbGreen, LOW);
  digitalWrite(rgbBlue, LOW);
}