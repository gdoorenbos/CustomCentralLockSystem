#ifndef LINXKH3RXMODULE_H
#define LINXKH3RXMODULE_H

#include "LinxRxModule.h"

class LinxKh3RxModule : public LinxRxModule
{
public:
    LinxKh3RxModule(LinxAddrBus addrBus, LinxDataBus dataBus, int vtPin);
    ~LinxKh3RxModule();

private:
    // intentionally not implemented
    LinxKh3RxModule();
};

#endif
