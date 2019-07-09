#include "DRV8830.h"

DRV8830::DRV8830(PinName sda,PinName scl,int addr):_i2c(sda,scl),_addr(addr){
}

//0x00~0x39
void DRV8830::neutral(){
    char dat[2]={SADDR_CTRL,(0x06<<2)|M_STANDBY};
    _i2c.write((_addr<<1),dat,2);
}

void DRV8830::forward(int power){
    int vset = (power * 0x39 / 100)+0x06;
    char dat[2]={SADDR_CTRL,(vset<<2)|M_FORWARD};
    _i2c.write((_addr<<1),dat,2);
}
void DRV8830::back(int power){
    int vset = (power * 0x39 / 100)+0x06;
    char dat[2]={SADDR_CTRL,(vset<<2)|M_REVERSE};
    _i2c.write((_addr<<1),dat,2);
}
void DRV8830::brake(){
    char dat[2]={SADDR_CTRL,(0x06<<2)|M_BRAKE};
    _i2c.write((_addr<<1),dat,2);
}