#include "MdMeasureDistance.h"
#include "Arduino.h"
#include "DrUltraSonic.h"

DrUltraSonic drul = DrUltraSonic(echo_pin, trig_pin);

double MdMeasureDistance::getDistance()
{
    double t = drul.measureReturnTime();
    double distance;

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
