#ifndef LINXRXMODULE_H
#define LINXRXMODULE_H

class GpioHandler;

const unsigned int LINX_ADDR_BUS_SIZE = 10;
const unsigned int LINX_DATA_BUS_SIZE = 5;

// typedef struct _LinxAddrBus
// {
//     int addrPin[LINX_ADDR_BUS_SIZE];
// } LinxAddrBus;

// typedef struct _LinxDataBus
// {
//     int dataPin[LINX_DATA_BUS_SIZE];
// } LinxDataBus;

class LinxRxModule
{
public:
    // initializes the object with the given buses and pins
    LinxRxModule(GpioHandler* pinHandler, int addrBus[LINX_ADDR_BUS_SIZE], int dataBus[LINX_DATA_BUS_SIZE], int vtPin);
    
    // this ctor doesn't initialize any pins. 
    // if you use this ctor, you MUST initialize the pins in the derived ctor. 
    LinxRxModule(GpioHandler* pinHandler);

    // virtual dtor. No dynamic objects, so does nothing.
    virtual ~LinxRxModule();

    // copies an array of ints representing the LinxRxModule Address pins
    void copyAddrBus(int dstAddrBus[LINX_ADDR_BUS_SIZE], int srcAddrBus[LINX_ADDR_BUS_SIZE]);

    // copies an array of ints representing the LinxRxModule Data pins
    void copyDataBus(int dstDataBus[LINX_DATA_BUS_SIZE], int srcDataBus[LINX_DATA_BUS_SIZE]);

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
    int addrBus[LINX_ADDR_BUS_SIZE];
    int dataBus[LINX_DATA_BUS_SIZE];
    int vtPin;

private:
    // copies an array of ints. performs no bounds checking - ensure both arrays are of the given size before calling!
    void copyIntArray(int dstArray[], int srcArray[], unsigned int size);
};

#endif
