#ifndef DRV8830_H
#define DRV8830_H

#include "mbed.h"

#define DEFAULT_ADDR    0x64

#define SADDR_CTRL      0x00
#define SADDR_ERR       0x01

#define M_STANDBY       0b00
#define M_REVERSE       0b01
#define M_FORWARD       0b10
#define M_BRAKE         0b11

class DRV8830 {
public:
    DRV8830(PinName sda,PinName scl,int addr = DEFAULT_ADDR);

//power is 1~100
    void neutral();
    void forward(int power);
    void back(int power);
    void brake();
private:
    I2C _i2c;
    int _addr;
};

#endif