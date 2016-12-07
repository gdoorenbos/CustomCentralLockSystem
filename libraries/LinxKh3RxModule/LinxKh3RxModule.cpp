#include "LinxKh3RxModule.h"
#include "LinxAddressArray.h"
#include "Arduino.h"

LinxKh3RxModule::LinxKh3RxModule(LinxAddrBus _addrBus, LinxDataBus _dataBus, int _vt)
    : addrBus(_addrBus)
    , dataBus(_dataBus)
    , vt(_vt)
{
    // address pins
    pinMode(addrBus.a0, OUTPUT);
    pinMode(addrBus.a1, OUTPUT);
    pinMode(addrBus.a2, OUTPUT);
    pinMode(addrBus.a3, OUTPUT);
    pinMode(addrBus.a4, OUTPUT);
    pinMode(addrBus.a5, OUTPUT);
    pinMode(addrBus.a6, OUTPUT);
    pinMode(addrBus.a7, OUTPUT);
    pinMode(addrBus.a8, OUTPUT);
    pinMode(addrBus.a9, OUTPUT);

    // data lines
    pinMode(dataBus.d0, INPUT);
    pinMode(dataBus.d1, INPUT);
    pinMode(dataBus.d2, INPUT);
    pinMode(dataBus.d3, INPUT);
    pinMode(dataBus.d4, INPUT);

    // valid transmission pin
    pinMode(vt, INPUT);
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}

void LinxKh3RxModule::setAddress(unsigned short address)
{
    digitalWrite(addrBus.a0, (address & (1 << 0)) ? HIGH : LOW);
    digitalWrite(addrBus.a1, (address & (1 << 1)) ? HIGH : LOW);
    digitalWrite(addrBus.a2, (address & (1 << 2)) ? HIGH : LOW);
    digitalWrite(addrBus.a3, (address & (1 << 3)) ? HIGH : LOW);
    digitalWrite(addrBus.a4, (address & (1 << 4)) ? HIGH : LOW);
    digitalWrite(addrBus.a5, (address & (1 << 5)) ? HIGH : LOW);
    digitalWrite(addrBus.a6, (address & (1 << 6)) ? HIGH : LOW);
    digitalWrite(addrBus.a7, (address & (1 << 7)) ? HIGH : LOW);
    digitalWrite(addrBus.a8, (address & (1 << 8)) ? HIGH : LOW);
    digitalWrite(addrBus.a9, (address & (1 << 9)) ? HIGH : LOW);
}

bool LinxKh3RxModule::hasValidTransmission()
{
    return digitalRead(vt) == HIGH;
}

bool LinxKh3RxModule::getDataBit(unsigned char dataBit)
{
    if( dataBit >= 0 && dataBit < LINX_DATA_BUS_SIZE )
        return digitalRead(dataBus.d[dataBit]) == HIGH;
    else
        return false;
}
