#ifndef LINXKH3RXMODULE_H
#define LINXKH3RXMODULE_H

#include "LinxRxModule.h"

class LinxKh3RxModule : public LinxRxModule
{
public:
    LinxKh3RxModule(int addrBus[LINX_ADDR_BUS_SIZE], int dataBus[LINX_DATA_BUS_SIZE], int vtPin);
    ~LinxKh3RxModule();

private:
    // intentionally not implemented
    LinxKh3RxModule();
};

#endif
