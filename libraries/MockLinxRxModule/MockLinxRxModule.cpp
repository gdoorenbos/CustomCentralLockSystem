#include "MockLinxRxModule.h"
#include "MockGpioHandler.h"

MockLinxRxModule::MockLinxRxModule(MockGpioHandler* pinHandler)
    : LinxRxModule(pinHandler, getTestAddrBus(), getTestDataBus(), getTestVtPin())
{
}

MockLinxRxModule::MockLinxRxModule()
    : LinxRxModule(new MockGpioHandler(), getTestAddrBus(), getTestDataBus(), getTestVtPin())
{
}

MockLinxRxModule::~MockLinxRxModule()
{
}

LinxAddrBus MockLinxRxModule::getTestAddrBus()
{
    LinxAddrBus addrBus;
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        addrBus.a[i] = i+1;

    return addrBus;
}

LinxDataBus MockLinxRxModule::getTestDataBus()
{
    LinxDataBus dataBus;
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        dataBus.d[i] = i+1+LINX_ADDR_BUS_SIZE;

    return dataBus;
}

int MockLinxRxModule::getTestVtPin()
{
    return LINX_ADDR_BUS_SIZE + LINX_DATA_BUS_SIZE + 1;
}

unsigned short MockLinxRxModule::getAddress() const
{
    unsigned short address = 0;
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        address |= (pinHandler->isPinHigh(addrBus.a[i]) ? 1 : 0) << i;

    return address;
}

void MockLinxRxModule::clearDataBits()
{
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        pinHandler->setPinLow(dataBus.d[i]);
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
        pinHandler->setPinHigh(dataBus.d[fobButton-1]);
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
