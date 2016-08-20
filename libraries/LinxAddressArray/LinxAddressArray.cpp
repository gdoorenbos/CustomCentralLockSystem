#include "LinxAddressArray.h"

LinxAddressArray::LinxAddressArray(unsigned short address)
	: address(address)
{
}

LinxAddressArray::~LinxAddressArray()
{
}

bool LinxAddressArray::getAddressBit(unsigned char addrBit)
{
    // Linx address is only 10 bits long. Return 0 for any bits out of range. 
    if (addrBit > 9)
        return false;

	return address & (1 << addrBit);
}
