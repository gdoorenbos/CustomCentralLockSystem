#include "gtest/gtest.h"
#include "BluetoothMessageParser.h"

void sendMessageAndVerify(const char* message, BluetoothMessageParser &parser)
{
	for(int i=0; i<strlen(message); ++i)
	{
		parser.giveCharacter(message[i]);
		EXPECT_FALSE(parser.hasMessage());
	}

	parser.giveCharacter('\n');
	EXPECT_TRUE(parser.hasMessage());

	const char* reportedMessage = parser.getMessage();
	EXPECT_FALSE(parser.hasMessage());
	EXPECT_STREQ(message, reportedMessage);
	delete[] reportedMessage;
}

TEST(BluetoothMessageParser, noMessageAvailableOnInitialization)
{
	BluetoothMessageParser parser;
	EXPECT_FALSE(parser.hasMessage());
}

TEST(BluetoothMessageParser, hasMessageAfterSingleNewline)
{
	BluetoothMessageParser parser;
	parser.giveCharacter('\n');
	EXPECT_TRUE(parser.hasMessage());
}

TEST(BluetoothMessageParser, hasMessageTrueAfterFirstMessage)
{
	BluetoothMessageParser parser;
	
	parser.giveCharacter('f');
	parser.giveCharacter('o');
	parser.giveCharacter('o');
	EXPECT_FALSE(parser.hasMessage());
	parser.giveCharacter('\n');
	EXPECT_TRUE(parser.hasMessage());
}

TEST(BluetoothMessageParser, getMessageClearsHasMessage)
{
	BluetoothMessageParser parser;
	parser.giveCharacter('\n');
	EXPECT_TRUE(parser.hasMessage());
	const char* message = parser.getMessage();
	EXPECT_FALSE(parser.hasMessage());
	delete[] message;
}

TEST(BluetoothMessageParser, getMessageReturnsProperString)
{
	BluetoothMessageParser parser;
	sendMessageAndVerify("foo", parser);
}

TEST(BluetoothMessageParser, getMessageReturnsEmptyString)
{
	BluetoothMessageParser parser;
	sendMessageAndVerify("", parser);
}

TEST(BluetoothMessageParser, multipleMessages)
{
	BluetoothMessageParser parser;
	sendMessageAndVerify("", parser);
	sendMessageAndVerify("foo", parser);
	sendMessageAndVerify("bar", parser);
	sendMessageAndVerify("", parser);
	sendMessageAndVerify("ded", parser);
	sendMessageAndVerify("", parser);
}

