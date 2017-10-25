#include "gtest/gtest.h"
#include "BluetoothMessageParser.h"

const char* clientConnectString = "CONNECT!!!!!!!!!";
const char* clientDisconnectString = "DISCONNECT";

void verifyParserMessage(const char* expectedMessage, BluetoothMessageParser &parser)
{
	const char* reportedMessage = parser.getMessage();
	EXPECT_FALSE(parser.hasMessage());
	EXPECT_STREQ(expectedMessage, reportedMessage);
	delete[] reportedMessage;
}

void giveCharacterToParserAndVerifyNoMessage(const char inputChar, BluetoothMessageParser &parser)
{
	parser.giveCharacter(inputChar);
	EXPECT_FALSE(parser.hasMessage());
}

void giveBareStringToParserAndVerifyNoMessage(const char* inputStr, BluetoothMessageParser &parser)
{
	for(unsigned int i=0; i<strlen(inputStr); ++i)
		giveCharacterToParserAndVerifyNoMessage(inputStr[i], parser);
}

void giveNewlineToParserAndVerifyHasMessage(BluetoothMessageParser &parser)
{
	parser.giveCharacter('\n');
	EXPECT_TRUE(parser.hasMessage());
}

void sendMessageAndVerify(const char* message, BluetoothMessageParser &parser)
{
	giveBareStringToParserAndVerifyNoMessage(message, parser);
	giveCharacterToParserAndVerifyNoMessage('\r', parser);
	giveNewlineToParserAndVerifyHasMessage(parser);
	verifyParserMessage(message, parser);
}

TEST(BluetoothMessageParser, noMessageAvailableOnInitialization)
{
	BluetoothMessageParser parser;
	EXPECT_FALSE(parser.hasMessage());
}

TEST(BluetoothMessageParser, clientNotConnectedOnInitialization)
{
	BluetoothMessageParser parser;
	EXPECT_FALSE(parser.isClientConnected());
}

TEST(BluetoothMessageParser, hasMessageAfterSingleNewline)
{
	BluetoothMessageParser parser;
	giveNewlineToParserAndVerifyHasMessage(parser);
}

TEST(BluetoothMessageParser, hasMessageTrueAfterFirstMessage)
{
	BluetoothMessageParser parser;
	
	parser.giveCharacter('f');
	parser.giveCharacter('o');
	parser.giveCharacter('o');
	EXPECT_FALSE(parser.hasMessage());
	giveNewlineToParserAndVerifyHasMessage(parser);
}

TEST(BluetoothMessageParser, getMessageClearsHasMessage)
{
	BluetoothMessageParser parser;
	giveNewlineToParserAndVerifyHasMessage(parser);

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

TEST(BluetoothMessageParser, trailingWhitespace)
{
	BluetoothMessageParser parser;
	giveBareStringToParserAndVerifyNoMessage("foo", parser);
	giveCharacterToParserAndVerifyNoMessage('\r', parser);
	giveNewlineToParserAndVerifyHasMessage(parser);
	verifyParserMessage("foo", parser);
}

TEST(BluetoothMessageParser, clientConnectedAfterBasicConnectString)
{
	BluetoothMessageParser parser;
	giveBareStringToParserAndVerifyNoMessage(clientConnectString, parser);
	EXPECT_TRUE(parser.isClientConnected());
}

TEST(BluetoothMessageParser, clientDisconnectedAfterDisconnectString)
{
	BluetoothMessageParser parser;
	giveBareStringToParserAndVerifyNoMessage(clientConnectString, parser);
	EXPECT_TRUE(parser.isClientConnected());
	giveBareStringToParserAndVerifyNoMessage(clientDisconnectString, parser);
	EXPECT_FALSE(parser.isClientConnected());
}

TEST(BluetoothMessageParser, clientConnectsAndDisconnectsMultipleTimes)
{
	BluetoothMessageParser parser;
	for(int i=0; i<5; ++i)
	{
		giveBareStringToParserAndVerifyNoMessage(clientConnectString, parser);
		EXPECT_TRUE(parser.isClientConnected());
		giveBareStringToParserAndVerifyNoMessage(clientDisconnectString, parser);
		EXPECT_FALSE(parser.isClientConnected());		
	}
}

TEST(BluetoothMessageParser, charsAfterConnectStringAreIgnored)
{
	BluetoothMessageParser parser;
	giveBareStringToParserAndVerifyNoMessage(clientConnectString, parser);
	EXPECT_TRUE(parser.isClientConnected());
	sendMessageAndVerify("hello", parser);
}

