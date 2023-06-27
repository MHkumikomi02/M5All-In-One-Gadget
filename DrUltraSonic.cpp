#include "DrUltraSonic.h"

DrUltraSonic::DrUltraSonic(int echo_pin, int trig_pin)
{
  ECHO_PIN = echo_pin;
  TRIG_PIN = trig_pin;
  
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

double DrUltraSonic::measureReturnTime()
{
    double t;
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    t = pulseIn(ECHO_PIN, HIGH, 2000000);
    return t;
}

