#ifndef MOCKLINXRXMODULE_H
#define MOCKLINXRXMODULE_H

#include "LinxRxModule.h"
#include <set>

class MockGpioHandler;

class MockLinxRxModule : public LinxRxModule
{
public:
    MockLinxRxModule(MockGpioHandler* pinHandler);
    MockLinxRxModule();
    ~MockLinxRxModule();

    // void setAddress(unsigned short address);
    unsigned short getAddress() const;

    // Valid button presses are 1-5. 2-button keyfob only has buttons 2 and 4. 
    void pushFobButton(unsigned char buttonPressed);

    // sets all pins in the data bus low
    void clearDataBits();

    // returns a mock LinxAddrBus used for testing.
    LinxAddrBus getTestAddrBus();

    // returns a mock LinxDataBus used for testing.
    LinxDataBus getTestDataBus();

    // returns a mock vtPin used for testing
    int getTestVtPin();

private:
    bool isFobButtonValid(unsigned char fobButton);
    void setDataBusAccordingToFobButton(unsigned char fobButton);
    void setVtPinAccordingToFobButton(unsigned char fobButton);
};

#endif
