#ifndef RTC_h
#define RTC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SoftwareSPI.h"


//Instructions
#define EEREAD             0b00000011
#define READ               0b00010011
#define WRITE              0b00010010
#define SRREAD             0b00000101

//Addresses
#define ADDR_SECONDS       0x01
#define SECONDS_ST         7

#define ADDR_CONTROL       0x08
#define CONTROL_EXTOSC     3


class RTC {
public:
    RTC(byte, byte, byte, byte);
    void setUseExternalOscillator(boolean);
    void enableOscillator(boolean);
    byte getSeconds();
    byte getControlByte();

private:
    SoftwareSPI spi;

    void setRegBit(byte, byte, boolean);
    byte writeReg(byte, byte);
    byte readReg(byte);
};

#endif

