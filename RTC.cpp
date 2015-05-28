#include "RTC.h"

//Public Methods
RTC::RTC(byte sck,byte mosi,byte miso,byte cs) : spi(sck,mosi,miso,cs) {
    spi.begin();
    setUseExternalOscillator(true);
    enableOscillator(true);
}

void RTC::setUseExternalOscillator(boolean val) {
    setRegBit(ADDR_CONTROL,CONTROL_EXTOSC,val);
}

void RTC::enableOscillator(boolean val) {
    setRegBit(ADDR_SECONDS,SECONDS_ST,val);
}

byte RTC::getSeconds() {
    return readReg(ADDR_SECONDS);
}

byte RTC::getControlByte() {
    return readReg(ADDR_CONTROL);
}

//Private Methods
void RTC::setRegBit(byte reg, byte n, boolean set) {
    byte value = readReg(reg);
    value = ((~(1 << n)) & value) | (set << n);
    writeReg(reg,value);
}

byte RTC::writeReg(byte reg, byte value) {
    spi.select();
    spi.transfer(WRITE);
    spi.transfer(reg);
    spi.transfer(value);
    spi.deselect();
    return value;
}

byte RTC::readReg(byte reg) {
    spi.select();
    spi.transfer(READ);
    spi.transfer(reg);
    byte value = spi.transfer(0);
    spi.deselect();
    return value;
}
