#pragma once
#include "M5All-In-One-Gadget.h"

class MdWBGTMonitor {
private:
    // privateはクラス内からしかアクセスできない

public:
    void init();
    void getWBGT(double* temperature, double* humidity, WbgtIndex* index);
    double calculateHeatstrokeAlert(double temperature, double humidity);
    // publicはどこからでもアクセス可能
};
