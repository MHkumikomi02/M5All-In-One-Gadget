#include "MdMeasureDistance.h"
#include "M5All-In-One-Gadget.h"
#include "Arduino.h"

double MdMeasureDistance::getDistance()
{
    double t;
    double distance;
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    t = pulseIn(ECHO_PIN, HIGH, 2000000);
    if (t > 0)
    {
        distance = (340.0 / 1000000) * t * 0.5 * 100;
    }
    else
    {
        distance = 0;
    }
    return distance;
    
}