#include "LinxKh3RxModule.h"
#include "Arduino.h"

LinxKh3RxModule::LinxKh3RxModule(int _addrBus[LINX_ADDR_BUS_SIZE], int _dataBus[LINX_DATA_BUS_SIZE], int _vt)
    : vt(_vt)
{
    // address pins
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
    {
        addrBus[i] = _addrBus[i];
        pinMode(addrBus[i], OUTPUT);
    }

    // data lines
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
    {
        dataBus[i] = _dataBus[i];
        pinMode(dataBus[i], INPUT);
    }

    // valid transmission pin
    pinMode(vt, INPUT);
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}

void LinxKh3RxModule::setAddress(unsigned short address)
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        digitalWrite(addrBus[i], (address & (1 << i)) ? HIGH : LOW);
}

bool LinxKh3RxModule::hasValidTransmission()
{
    return digitalRead(vt) == HIGH;
}

bool LinxKh3RxModule::getDataBit(unsigned char dataBit)
{
    return digitalRead(dataBus[dataBit]) == HIGH;
}
