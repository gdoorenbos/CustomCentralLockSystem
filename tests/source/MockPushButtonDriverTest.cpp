#include "gtest/gtest.h"
#include "MockPushButtonDriver.h"

// helper functions
void expectPressed(MockPushButtonDriver pushButton)
{
	EXPECT_TRUE(pushButton.isPressed());
}

void expectReleased(MockPushButtonDriver pushButton)
{
	EXPECT_FALSE(pushButton.isPressed());
}

// tests
TEST(MockPushButtonDriver, initializedUnpressed)
{
	MockPushButtonDriver pushButton;
	expectReleased(pushButton);
}

TEST(MockPushButtonDriver, properBehaviorWhenPressed)
{
	MockPushButtonDriver pushButton;
	pushButton.press();
	expectPressed(pushButton);
}

TEST(MockPushButtonDriver, properBehaviorWhenReleased)
{
	MockPushButtonDriver pushButton;
	pushButton.press();
	pushButton.release();
	expectReleased(pushButton);
}

TEST(MockPushButtonDriver, repetitivePresses)
{
	MockPushButtonDriver pushButton;
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.press();
	expectPressed(pushButton);
}

TEST(MockPushButtonDriver, repetitiveReleases)
{
	MockPushButtonDriver pushButton;
	expectReleased(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.release();
	expectReleased(pushButton);
}

TEST(MockPushButtonDriver, repetitivePressAndReleaseCycles)
{
	MockPushButtonDriver pushButton;
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.release();
	expectReleased(pushButton);
	pushButton.press();
	expectPressed(pushButton);
	pushButton.release();
	expectReleased(pushButton);
}
