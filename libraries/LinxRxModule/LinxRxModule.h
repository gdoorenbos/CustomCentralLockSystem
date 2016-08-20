#ifndef LINXRXMODULE_H
#define LINXRXMODULE_H

class LinxRxModule
{
public:
	LinxRxModule();
	virtual ~LinxRxModule();

	virtual void setAddress(unsigned short address) = 0;
	virtual bool hasValidTransmission() = 0;
	virtual bool getDataBit(unsigned char dataBit) = 0;

private:

};

#endif
