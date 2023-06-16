#include "MdWBGTMonitor.h"  


double MdWBGTMonitor::calculateHeatstrokeAlert(double temperature, double humidity) {
    double heatstrokealert = 0.68 * temperature + 0.12 * humidity;
    return heatstrokealert;
}

void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index) {
    double heatstrokealert = calculateHeatstrokeAlert(*temperature, *humidity);

    if (heatstrokealert <= 15) {
        *index = SAFE;
    } else if (heatstrokealert >= 15 && heatstrokealert <= 24) {
        *index = ATTENTION;
    } else if (heatstrokealert >= 24 && heatstrokealert <= 27) {
        *index = ALERT;
    } else if (heatstrokealert >= 27 && heatstrokealert <= 30) {
        *index = HIGH_ALERT;
    } else if (heatstrokealert >= 31) {
        *index = DANGER;
    }
}
