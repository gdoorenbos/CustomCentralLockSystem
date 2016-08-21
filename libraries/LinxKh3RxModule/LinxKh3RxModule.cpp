#include "LinxKh3RxModule.h"
#include "LinxAddressArray.h"
#include "Arduino.h"

// LinxKh3RxModule::LinxKh3RxModule( int a0, int a1, int a2, int a3, int a4
//                                 , int a5, int a6, int a7, int a8, int a9
//                                 , int d0, int d1, int d2, int d3, int d4
//                                 , int vt)
LinxKh3RxModule::LinxKh3RxModule(LinxAddrBus _addrBus, LinxDataBus _dataBus, int _vt)
    : addrBus(_addrBus)
    , dataBus(_dataBus)
    , vt(_vt)
{
    // address pins
    for( int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        pinMode(addrBus[i], OUTPUT);

    // data lines
    for( int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        pinMode(dataBus[i], INPUT);

    // valid transmission pin
    pinMode(vt, INPUT);
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}

void LinxKh3RxModule::setAddress(unsigned short address)
{
    LinxAddressArray addrArray(address);

    for( int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        digitalWrite(addrBus[i], addrArray.getAddressBit(i) ? HIGH : LOW);
}

bool LinxKh3RxModule::hasValidTransmission()
{
    return digitalRead(vt) == HIGH;
}

bool LinxKh3RxModule::getDataBit(unsigned char dataBit)
{
    if( dataBit >= 0 && dataBit < LINX_DATA_BUS_SIZE )
        return digitalRead(dataBus[i]) == HIGH;
    else
        return false;
}
