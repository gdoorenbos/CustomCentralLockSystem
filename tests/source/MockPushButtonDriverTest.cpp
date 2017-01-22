#include "gtest/gtest.h"
#include "MockPushButtonDriver.h"

// helper functions
void assertPressed(MockPushButtonDriver &pushButton)
{
	ASSERT_TRUE(pushButton.isPressed());
}

void assertReleased(MockPushButtonDriver &pushButton)
{
	ASSERT_FALSE(pushButton.isPressed());
}

// tests
TEST(MockPushButtonDriver, initializedUnpressed)
{
	MockPushButtonDriver pushButton;
	assertReleased(pushButton);
}

TEST(MockPushButtonDriver, properBehaviorWhenPressed)
{
	MockPushButtonDriver pushButton;
	pushButton.press();
	assertPressed(pushButton);
}

TEST(MockPushButtonDriver, properBehaviorWhenReleased)
{
	MockPushButtonDriver pushButton;
	pushButton.press();
	pushButton.release();
	assertReleased(pushButton);
}

TEST(MockPushButtonDriver, repetitivePresses)
{
	MockPushButtonDriver pushButton;
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.press();
	assertPressed(pushButton);
}

TEST(MockPushButtonDriver, repetitiveReleases)
{
	MockPushButtonDriver pushButton;
	assertReleased(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.release();
	assertReleased(pushButton);
}

TEST(MockPushButtonDriver, repetitivePressAndReleaseCycles)
{
	MockPushButtonDriver pushButton;
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.release();
	assertReleased(pushButton);
	pushButton.press();
	assertPressed(pushButton);
	pushButton.release();
	assertReleased(pushButton);
}
