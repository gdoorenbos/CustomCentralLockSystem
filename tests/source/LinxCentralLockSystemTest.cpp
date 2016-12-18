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

    rxer.pushFobButton(KEYFOB_LOCK_BUTTON);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    rxer.pushFobButton(KEYFOB_UNLOCK_BUTTON);
    cls.run();
    ASSERT_FALSE(locksDriver.areDoorsLocked());

    rxer.pushFobButton(KEYFOB_LOCK_BUTTON);
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
    rxer.pushFobButton(0);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    rxer.pushFobButton(100);
    cls.run();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    // send valid message
    rxer.pushFobButton(KEYFOB_UNLOCK_BUTTON);
    cls.run();
    ASSERT_FALSE(locksDriver.areDoorsLocked());
}
