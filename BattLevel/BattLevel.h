#ifndef BATTLEVEL_H
#define BATTLEVEL_H

#include "mbed.h"

#define BATT_PIN    P0_2



class BattLevel {
public:
    BattLevel(PinName pin = BATT_PIN);

    float getBatteryLevel();
private:
    AnalogIn _ain;
};

#endif