#ifndef LINXRXMODULE_H
#define LINXRXMODULE_H

class GpioHandler;

const unsigned int LINX_ADDR_BUS_SIZE = 10;
const unsigned int LINX_DATA_BUS_SIZE = 5;

struct LinxAddrBus
{
    int a[LINX_ADDR_BUS_SIZE];
};

struct LinxDataBus
{
    int d[LINX_DATA_BUS_SIZE];
};

class LinxRxModule
{
public:
    // initializes the object with the given buses and pins
    LinxRxModule(GpioHandler* pinHandler, LinxAddrBus addrBus, LinxDataBus dataBus, int vtPin);

    // virtual dtor. No dynamic objects, so does nothing.
    virtual ~LinxRxModule();

    // configures the pins in addrBus as OUTPUTs
    void configureAddrBusForOutput();

    // configures the pins in dataBus as INPUTs
    void configureDataBusForInput();

    // configures the valid Transmission pin for INPUT
    void configureValidTransmissionPinForInput();

    // configures the addrBus, dataBus, and vtPin.
    void initializePins();

    // returns whether the device has received a valid transmission
    bool hasValidTransmission();

    // returns whether the data bit is high(true) or low(false)
    bool getDataBit(unsigned char dataBit);

    // sets the device address
    void setAddress(unsigned short address);

    // returns true if the bit in the given number is 1. false otherwise. 
    bool getBitFromNumber(unsigned short bit, unsigned short number);

protected:
    GpioHandler* pinHandler;
    LinxAddrBus addrBus;
    LinxDataBus dataBus;
    int vtPin;

private:
    // intentionally not implemented
    LinxRxModule();
};

#endif
