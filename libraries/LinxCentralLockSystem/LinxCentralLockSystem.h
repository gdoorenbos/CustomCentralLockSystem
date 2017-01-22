#ifndef LINXCENTRALLOCKSYSTEM_H
#define LINXCENTRALLOCKSYSTEM_H

class LinxRxModule;
class PowerLocksDriver;

class LinxCentralLockSystem
{
public:
    LinxCentralLockSystem(/*LinxRxModule* rxer,*/ PowerLocksDriver* locksDriver);
    ~LinxCentralLockSystem();

    void run();

private:
    // intentionally not implemented
    LinxCentralLockSystem();

    // helper method
    // void decipherRxModuleTransmission();

    // member variables
    // LinxRxModule* rxer;
    PowerLocksDriver* locksDriver;
};

#endif
