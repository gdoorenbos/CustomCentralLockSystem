#ifndef LINXKH3RXMODULE_H
#define LINXKH3RXMODULE_H

#include "LinxRxModule.h"

struct LinxAddrBus
{
    int a0;
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    int a6;
    int a7;
    int a8;
    int a9;
};

struct LinxDataBus
{
    int d0;
    int d1;
    int d2;
    int d3;
    int d4;
};

class LinxKh3RxModule : public LinxRxModule
{
public:
    LinxKh3RxModule(LinxAddrBus addrBus, LinxDataBus dataBus, int vt);
    ~LinxKh3RxModule();


    void setAddress(unsigned short address);
    bool getDataBit(unsigned char dataBit);
    bool hasValidTransmission();

private:
    // intentionally not implemented
    LinxKh3RxModule();

    // members
    LinxAddrBus addrBus;
    LinxDataBus dataBus;
    int vt;
};

#endif
