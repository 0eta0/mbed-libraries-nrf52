#include "BattLevel.h"

BattLevel::BattLevel(PinName pin):_ain(pin){}

float BattLevel::getBatteryLevel(){
    return _ain.read()*100.0f;
}