/*
This software is using following MIT license library.
Library WS2812 /users/bridadan/code/WS2812/
*/
#include "WS2812.h"

WS2812 *WS2812::__blinkobj = NULL;
Ticker WS2812::__tick;

WS2812::WS2812(PinName pin, int zeroHigh, int zeroLow, int oneHigh, int oneLow): __gpo(pin)
{
    __outPin = pin;
    // Default values designed for K64f. Assumes GPIO toggle takes ~0.4us
    setDelays(zeroHigh, zeroLow, oneHigh, oneLow);
}

void WS2812::setDelays(int zeroHigh, int zeroLow, int oneHigh, int oneLow)
{
    __zeroHigh = zeroHigh;
    __zeroLow = zeroLow;
    __oneHigh = oneHigh;
    __oneLow = oneLow;
}

//color is 0xAARRGGBB
//AA is brightness
void WS2812::write(int color)
{
    //pc.printf("colorcode = 0x%x\n",color);
    int i, j, c;
    char r,b,g,a;
    char buf[3];
    // Load the transmit buffer

    a = color >> 24;
    r = (((color & 0x00FF0000) >> 16)*a)>>8;
    g = (((color & 0x0000FF00) >> 8) *a)>>8;
    b =  ((color & 0x000000FF)       *a)>>8;

    buf[0] = g;
    buf[1] = r;
    buf[2] = b;

    // Entering timing critical section, so disabling interrupts
    __disable_irq();
    // Begin bit-banging
    for (c = 0; c < 3; c++) {
        for (i = 7; i >= 0; i--) {
            j = 0;

            if ((buf[c]>>i)&0x01) {
                __gpo = 1;
                for (; j < __oneHigh; j++) {
                    __nop();
                }
                __gpo = 0;
                for (; j < __oneLow; j++) {
                    __nop();
                }

            } else {
                __gpo = 1;
                for (; j < __zeroHigh; j++) {
                    __nop();
                }
                __gpo = 0;
                for (; j < __zeroLow; j++) {
                    __nop();
                }
            }
        }
    }


    // Exiting timing critical section, so enabling interrutps
    __enable_irq();
}

void WS2812::light(int color,int brightness)
{
    if (__blinkobj != NULL) __tick.detach();
    __blinkobj = NULL;
    int dat = color;
    dat &= 0xFFFFFF;
    dat |= (brightness & 0xFF)<<24;
    write(dat);
}

void WS2812::lightBlink(int color, int brightness,float interval)
{
    __blinkobj = this;
    __color = color;
    __brightness = brightness;
    __tick.attach(&WS2812::__blinks,interval);
}

void WS2812::lightOff()
{
    if (__blinkobj != NULL) __tick.detach();
    __blinkobj = NULL;
    write(0x00000000);
}

void WS2812::__blink()
{
    if (__blinkflg) {
        write(0x00000000);
    } else {
        int dat = __color;
        dat &= 0xFFFFFF;
        dat |= (__brightness & 0xFF)<<24;

        write(dat);
    }
    __blinkflg = !__blinkflg;
}


void WS2812::__blinks()
{
    if (__blinkobj == NULL) return;
    __blinkobj->__blink();
}