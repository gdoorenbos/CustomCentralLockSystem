#ifndef DRIVER_FACTORY_IMPL_H
#define DRIVER_FACTORY_IMPL_H

#include <DriverFactory.h>

class DriverFactoryImpl : public DriverFactory
{
protected:
    // don't instantiate this class directly
    DriverFactoryImpl();
    ~DriverFactoryImpl();

public:
    static DriverFactory* getInstance();

    //driver getters
    LinxRxModule* getLinxRxModule();
    PowerLocksDriver* getPowerLocksDriver();

private:
    LinxRxModule* rxModule;
    PowerLocksDriver* powerLocksDriver;
};

#endif

