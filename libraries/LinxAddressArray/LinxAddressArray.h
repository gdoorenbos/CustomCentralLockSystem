#ifndef LINXADDRESSARRAY_H
#define LINXADDRESSARRAY_H

class LinxAddressArray
{
public:
	LinxAddressArray(unsigned short address);
	~LinxAddressArray();

	bool getAddressBit(unsigned char addrBit);

private:
	// intentionally not implemented
	LinxAddressArray();

	unsigned short address;
};

#endif