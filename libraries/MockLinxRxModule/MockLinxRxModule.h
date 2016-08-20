#ifndef MOCKLINXRXMODULE_H
#define MOCKLINXRXMODULE_H

#include "LinxRxModule.h"

class MockLinxRxModule : public LinxRxModule
{
public:
    MockLinxRxModule();
    ~MockLinxRxModule();

    void setAddress(unsigned short address);
    unsigned short getAddress() const;

    // Valid button presses are 1-5. 2-button keyfob only has buttons 2 and 4. 
    void giveTransmission(unsigned char buttonPressed);
    bool hasValidTransmission();

    // dataLine is buttonPress-1. To see if button2 was pressed, check dataBit==1.
    bool getDataBit(unsigned char dataBit);

private:
    unsigned short address;
    bool validTransmission;
    unsigned char dataBit;
};

#endif
