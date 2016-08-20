#include "MockLinxRxModule.h"
#include "cstdio"

MockLinxRxModule::MockLinxRxModule()
	: address(0)
    , validTransmission(false)
    , dataBit(99)
{
}

MockLinxRxModule::~MockLinxRxModule()
{
}

void MockLinxRxModule::setAddress(unsigned short address)
{
	this->address = address;
}

unsigned short MockLinxRxModule::getAddress() const
{
	return address;
}

void MockLinxRxModule::giveTransmission(unsigned char buttonPressed)
{
    if(buttonPressed >= 1 && buttonPressed <= 5)
    {
        validTransmission = true;
        dataBit = buttonPressed - 1;
    }
    else
    {
        validTransmission = false;
        dataBit = 99;
    }
}

bool MockLinxRxModule::hasValidTransmission()
{
    return validTransmission;
}

bool MockLinxRxModule::getDataBit(unsigned char dataBit)
{
    return (this->dataBit == dataBit);
}
