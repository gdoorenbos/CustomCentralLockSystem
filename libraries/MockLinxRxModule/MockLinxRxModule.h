#ifndef MOCKLINXRXMODULE_H
#define MOCKLINXRXMODULE_H

#include "LinxRxModule.h"
#include <set>

class MockGpioHandler;

class MockLinxRxModule : public LinxRxModule
{
public:
    MockLinxRxModule(MockGpioHandler* pinHandler, int _addrBus[LINX_ADDR_BUS_SIZE], int _dataBus[LINX_DATA_BUS_SIZE], int _vtPin);
    MockLinxRxModule();
    ~MockLinxRxModule();

    // void setAddress(unsigned short address);
    unsigned short getAddress() const;

    // Valid button presses are 1-5. 2-button keyfob only has buttons 2 and 4. 
    void pushFobButton(unsigned char buttonPressed);

    // sets all pins in the data bus low
    void clearDataBits();

private:
    bool isFobButtonValid(unsigned char fobButton);
    void setDataBusAccordingToFobButton(unsigned char fobButton);
    void setVtPinAccordingToFobButton(unsigned char fobButton);
};

#endif
