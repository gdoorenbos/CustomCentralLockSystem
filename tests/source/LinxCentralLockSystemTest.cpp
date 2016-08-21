#include "gtest/gtest.h"
#include "MockLinxRxModule.h"
#include "MockPowerLocksDriver.h"
#include "MockPushButtonDriver.h"
#include "LinxCentralLockSystem.h"

#define KEYFOB_LOCK_BUTTON      4
#define KEYFOB_UNLOCK_BUTTON    2

TEST(LinxCentralLockSystem, pushButtonsWork)
{
    MockLinxRxModule rxer;
    MockPowerLocksDriver locksDriver;
    MockPushButtonDriver lockButton;
    MockPushButtonDriver unlockButton;
    LinxCentralLockSystem cls(&rxer, &locksDriver, &lockButton, &unlockButton);

    lockButton.press();
    cls.run();
    lockButton.release();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

    unlockButton.press();
    cls.run();
    unlockButton.release();
    ASSERT_FALSE(locksDriver.areDoorsLocked());

    // if both lock button and unlock button are pressed at the same time, lock the doors. 
    lockButton.press();
    unlockButton.press();
    cls.run();
    lockButton.release();
    unlockButton.release();
    ASSERT_TRUE(locksDriver.areDoorsLocked());
}

TEST(LinxCentralLockSystem, rxModuleWorksGoldenScenario)
{
    MockLinxRxModule rxer;
    MockPowerLocksDriver locksDriver;
    MockPushButtonDriver lockButton;
    MockPushButtonDriver unlockButton;
    LinxCentralLockSystem cls(&rxer, &locksDriver, &lockButton, &unlockButton);

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
    MockPushButtonDriver lockButton;
    MockPushButtonDriver unlockButton;
    LinxCentralLockSystem cls(&rxer, &locksDriver, &lockButton, &unlockButton);

    // put locks in known state by pressing lock button
    lockButton.press();
    cls.run();
    lockButton.release();
    ASSERT_TRUE(locksDriver.areDoorsLocked());

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
