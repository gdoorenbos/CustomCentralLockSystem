#include "MockLinxRxModule.h"
#include "MockGpioHandler.h"

MockLinxRxModule::MockLinxRxModule(MockGpioHandler* _pinHandler, int _addrBus[LINX_ADDR_BUS_SIZE], int _dataBus[LINX_DATA_BUS_SIZE], int _vtPin)
    : LinxRxModule(_pinHandler, _addrBus, _dataBus, _vtPin)
{
}

MockLinxRxModule::MockLinxRxModule()
    : LinxRxModule(new MockGpioHandler())
{
    // default addr bus
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        addrBus[i] = i + 1;

    // default data bus
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        dataBus[i] = i + 1 + LINX_ADDR_BUS_SIZE;

    // valid transmission pin
    vtPin = LINX_ADDR_BUS_SIZE + LINX_DATA_BUS_SIZE + 1;

    // configure pins
    initializePins();
}

MockLinxRxModule::~MockLinxRxModule()
{
}

unsigned short MockLinxRxModule::getAddress() const
{
    unsigned short address = 0;
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        address |= (pinHandler->isPinHigh(addrBus[i]) ? 1 : 0) << i;

    return address;
}

void MockLinxRxModule::clearDataBits()
{
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        pinHandler->setPinLow(dataBus[i]);
}

bool MockLinxRxModule::isFobButtonValid(unsigned char fobButton)
{
    if( fobButton >= 1 && fobButton <= 5 )
        return true;

    return false;
}

void MockLinxRxModule::setDataBusAccordingToFobButton(unsigned char fobButton)
{
    clearDataBits();
    if( isFobButtonValid(fobButton) )
        pinHandler->setPinHigh(dataBus[fobButton-1]);
}

void MockLinxRxModule::setVtPinAccordingToFobButton(unsigned char fobButton)
{
    if( isFobButtonValid(fobButton) )
        pinHandler->setPinHigh(vtPin);
    else
        pinHandler->setPinLow(vtPin);
}

void MockLinxRxModule::pushFobButton(unsigned char fobButton)
{
    setVtPinAccordingToFobButton(fobButton);
    setDataBusAccordingToFobButton(fobButton);
}
