/* 
This software is using following MIT license library.
Library WS2812 /users/bridadan/code/WS2812/
*/
#ifndef WS2812_H
#define WS2812_H

#include "mbed.h"

//#define FRAME_SIZE 24
#define ZEROHIGH 0
#define ZEROLOW 5
#define ONEHIGH 5
#define ONELOW 0

//!Library for the WS2812 RGB LED with integrated controller
/*!
The WS2812 is controller that is built into a range of LEDs
*/
class WS2812
{
public:
    /**
    *   Constructor
    *
    * @param pin Output pin. Connect to "Din" on the first WS2812 in the strip
    * @param size Number of LEDs in your strip
    * @param zeroHigh How many NOPs to insert to ensure TOH is properly generated. See library description for more information.
    * @param zeroLow How many NOPs to insert to ensure TOL is properly generated. See library description for more information.
    * @param oneHigh How many NOPs to insert to ensure T1H is properly generated. See library description for more information.
    * @param oneLow How many NOPs to insert to ensure T1L is properly generated. See library description for more information.
    *
    */
    WS2812(PinName pin, int zeroHigh = ZEROHIGH, int zeroLow = ZEROLOW, int oneHigh = ONEHIGH, int oneLow = ONELOW);

    
    /**
    *   Sets the timing parameters for the bit-banged signal
    *
    * @param zeroHigh How many NOPs to insert to ensure TOH is properly generated. See library description for more information.
    * @param zeroLow How many NOPs to insert to ensure TOL is properly generated. See library description for more information.
    * @param oneHigh How many NOPs to insert to ensure T1H is properly generated. See library description for more information.
    * @param oneLow How many NOPs to insert to ensure T1L is properly generated. See library description for more information.
    *
    */
    void setDelays(int zeroHigh, int zeroLow, int oneHigh, int oneLow);

    /**
    *   Writes the given buffer to the LED strip with the given offsets.
    *   NOTE: This function is timing critical, therefore interrupts are disabled during the transmission section.
    *
    * @param color color code 0xAARRGGBB (AA is brightness)
    *
    */
    void write(int color);

    void light(int color, int brightness);
    void lightBlink(int color, int brightness,float interval);
    void lightOff();

    void __blink();
    static void __blinks();

private:
    int __zeroHigh, __zeroLow, __oneHigh, __oneLow;
    int __color,__brightness;
    PinName __outPin;
    DigitalOut __gpo;
    static Ticker __tick;
    bool __blinkflg;
    static WS2812 *__blinkobj;
};

#endif
