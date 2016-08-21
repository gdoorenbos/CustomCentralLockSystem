#ifndef LINXKH3RXMODULE_H
#define LINXKH3RXMODULE_H

#include "LinxRxModule.h"

#define LINX_ADDR_BUS_SIZE  10
#define LINX_DATA_BUS_SIZE  5
// typedef int LinxAddrBus [LINX_ADDR_BUS_SIZE];
// typedef int LinxDataBus [LINX_DATA_BUS_SIZE];
typedef struct LinxAddrBus { int a[LINX_ADDR_BUS_SIZE]; } LinxAddrBus;
typedef struct LinxDataBus { int d[LINX_DATA_BUS_SIZE]; } LinxDataBus;

class LinxKh3RxModule : public LinxRxModule
{
public:
    // LinxKh3RxModule( int a0, int a1, int a2, int a3, int a4
    //                , int a5, int a6, int a7, int a8, int a9
    //                , int d0, int d1, int d2, int d3, int d4
    //                , int vt);
    LinxKh3RxModule(LinxAddrBus addrBus, LinxDataBus dataBus, int vt);
    ~LinxKh3RxModule();


    void setAddress(unsigned short address);
    bool hasValidTransmission();
    bool getDataBit(unsigned char dataBit);

private:
    // intentionally not implemented
    LinxKh3RxModule();

    // members
    LinxAddrBus addrBus;
    LinxDataBus dataBus;
    int vt;
};

#endif
