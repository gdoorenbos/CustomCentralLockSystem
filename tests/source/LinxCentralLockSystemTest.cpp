#include "gtest/gtest.h"
#include "MockLinxRxModule.h"
#include "MockPowerLocksDriver.h"
#include "LinxCentralLockSystem.h"

#define KEYFOB_LOCK_BUTTON      4
#define KEYFOB_UNLOCK_BUTTON    2

TEST(LinxCentralLockSystem, rxModuleWorksGoldenScenario)
{
    MockLinxRxModule rxer;
    MockPowerLocksDriver locksDriver;
    LinxCentralLockSystem cls(&rxer, &locksDriver);

    rxer.giveTransmission(KEYFOB_LOCK_BUTTON);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    rxer.giveTransmission(KEYFOB_UNLOCK_BUTTON);
    cls.run();
    ASSERT_FALSE(locksDriver.areDoorsLocked());

    rxer.giveTransmission(KEYFOB_LOCK_BUTTON);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());
}

TEST(LinxCentralLockSystem, rxModuleGracefullyHandlesBadTransmissions)
{
    MockLinxRxModule rxer;
    MockPowerLocksDriver locksDriver;
    LinxCentralLockSystem cls(&rxer, &locksDriver);

    // lock doors
    locksDriver.lockDoors();

    // send errant messages
    rxer.giveTransmission(0);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    rxer.giveTransmission(100);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    // send valid message
    rxer.giveTransmission(KEYFOB_UNLOCK_BUTTON);
    cls.run();
    ASSERT_FALSE(locksDriver.areDoorsLocked());
}
