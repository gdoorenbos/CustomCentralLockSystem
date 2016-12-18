#include "LinxRxModule.h"
#include "GpioHandler.h"

LinxRxModule::LinxRxModule(GpioHandler* _pinHandler, int _addrBus[LINX_ADDR_BUS_SIZE], int _dataBus[LINX_DATA_BUS_SIZE], int _vtPin)
    : pinHandler(_pinHandler)
    , vtPin(_vtPin)
{
    // copy buses to internal members 
    copyAddrBus(addrBus, _addrBus);
    copyDataBus(dataBus, _dataBus);

    // configure pins for input/output
    initializePins();
}

LinxRxModule::LinxRxModule(GpioHandler* _pinHandler)
    : pinHandler(_pinHandler)
{
}

LinxRxModule::~LinxRxModule()
{
    delete pinHandler;
}

void LinxRxModule::copyAddrBus(int dstAddrBus[LINX_ADDR_BUS_SIZE], int srcAddrBus[LINX_ADDR_BUS_SIZE])
{
    copyIntArray(dstAddrBus, srcAddrBus, LINX_ADDR_BUS_SIZE);
}

void LinxRxModule::copyDataBus(int dstDataBus[LINX_DATA_BUS_SIZE], int srcDataBus[LINX_DATA_BUS_SIZE])
{
    copyIntArray(dstDataBus, srcDataBus, LINX_DATA_BUS_SIZE);
}

void LinxRxModule::copyIntArray(int dstArray[], int srcArray[], unsigned int size)
{
    for( unsigned int i=0; i<size; ++i )
        dstArray[i] = srcArray[i];
}

void LinxRxModule::configureAddrBusForOutput()
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        pinHandler->configurePinForOutput(addrBus[i]);
}

void LinxRxModule::configureDataBusForInput()
{
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        pinHandler->configurePinForInput(dataBus[i]);
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
    return pinHandler->isPinHigh(dataBus[dataBit]);
}

bool LinxRxModule::getBitFromNumber(unsigned short bit, unsigned short number)
{
    return ( number & (1 << bit) );
}

void LinxRxModule::setAddress(unsigned short address)
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        pinHandler->setPin(addrBus[i], getBitFromNumber(i, address));
}
