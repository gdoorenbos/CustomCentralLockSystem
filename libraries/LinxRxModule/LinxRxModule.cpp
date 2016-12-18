#include "LinxRxModule.h"
#include "GpioHandler.h"

LinxRxModule::LinxRxModule(GpioHandler* _pinHandler, LinxAddrBus _addrBus, LinxDataBus _dataBus, int _vtPin)
    : pinHandler(_pinHandler)
    , addrBus(_addrBus)
    , dataBus(_dataBus)
    , vtPin(_vtPin)
{
    initializePins();
}

LinxRxModule::~LinxRxModule()
{
    delete pinHandler;
}

void LinxRxModule::configureAddrBusForOutput()
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        pinHandler->configurePinForOutput(addrBus.a[i]);
}

void LinxRxModule::configureDataBusForInput()
{
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        pinHandler->configurePinForInput(dataBus.d[i]);
}

void LinxRxModule::configureValidTransmissionPinForInput()
{
    pinHandler->configurePinForInput(vtPin);
}

void LinxRxModule::initializePins()
{
    configureAddrBusForOutput();
    configureDataBusForInput();
    configureValidTransmissionPinForInput();
}

bool LinxRxModule::hasValidTransmission()
{
    return pinHandler->isPinHigh(vtPin);
}

bool LinxRxModule::getDataBit(unsigned char dataBit)
{
    return pinHandler->isPinHigh(dataBus.d[dataBit]);
}

bool LinxRxModule::getBitFromNumber(unsigned short bit, unsigned short number)
{
    return ( number & (1 << bit) );
}

void LinxRxModule::setAddress(unsigned short address)
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        pinHandler->setPin(addrBus.a[i], getBitFromNumber(i, address));
}
