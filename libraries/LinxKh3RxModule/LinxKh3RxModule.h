#ifndef LINXKH3RXMODULE_H
#define LINXKH3RXMODULE_H

#include "LinxRxModule.h"

const unsigned int LINX_ADDR_BUS_SIZE = 10;
const unsigned int LINX_DATA_BUS_SIZE = 5;

class LinxKh3RxModule : public LinxRxModule
{
public:
    LinxKh3RxModule(int addrBus[LINX_ADDR_BUS_SIZE], int dataBus[LINX_DATA_BUS_SIZE], int vt);
    ~LinxKh3RxModule();


    void setAddress(unsigned short address);
    bool getDataBit(unsigned char dataBit);
    bool hasValidTransmission();

private:
    // intentionally not implemented
    LinxKh3RxModule();

    // members
    int addrBus[LINX_ADDR_BUS_SIZE];
    int dataBus[LINX_DATA_BUS_SIZE];
    int vt;
};

#endif
