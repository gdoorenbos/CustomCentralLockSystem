#include "BluetoothMessageParser.h"
#include <string.h>

BluetoothMessageParser::BluetoothMessageParser()
	: finishedMessage(makeCopyOfStringOnHeap(""))
	, inputBuffer(makeCopyOfStringOnHeap(""))
	, hasMessageFlag(false)
	, clientIsConnected(false)
	, ignoreChars(0)
{
}

BluetoothMessageParser::~BluetoothMessageParser()
{
	if( inputBuffer != 0 )
		delete[] inputBuffer;

	if( finishedMessage != 0 )
		delete[] finishedMessage;
}

void BluetoothMessageParser::giveCharacter(const char inputChar)
{
	if( ignoreChars == 0 )
	{
		if( inputChar == '\n' )
			copyInputBufferToFinishedMessage();
		else
		{
			appendCharacterToInputBufferIfNotWhitespace(inputChar);

			// check for connect or disconnect
			if(strstr(inputBuffer, "DISCONNECT") != 0)
			{
				clientIsConnected = false;
				clearInputBuffer();
			}
			else if(strstr(inputBuffer, "CONNECT") != 0)
			{
				clientIsConnected = true;
				clearInputBuffer();

				// after the CONNECT string, there are some characters we don't care about. Let's ignore them.
				ignoreChars = 9;
			}
		}
	}
	else
	{
		--ignoreChars;
	}
}

bool BluetoothMessageParser::hasMessage() const
{
	return hasMessageFlag;
}

const char* BluetoothMessageParser::getMessage()
{
	const char* message = peekMessage();
	hasMessageFlag = false;
	return message;
}

const char* BluetoothMessageParser::peekMessage() 
{
	if( hasMessage() )
		return makeCopyOfStringOnHeap(finishedMessage);
	else
		return makeCopyOfStringOnHeap("");
}

bool BluetoothMessageParser::isClientConnected()
{
	return clientIsConnected;
}

void BluetoothMessageParser::appendCharacterToInputBufferIfNotWhitespace(const char inputChar)
{
	// update comparison if needed
	if( inputChar != '\r' )
		appendCharacterToInputBuffer(inputChar);
}

void BluetoothMessageParser::appendCharacterToInputBuffer(const char inputChar)
{
	int newStringSize = strlen(inputBuffer) + 1 + 1;	// +1 for inputChar and +1 for terminating null char
	char* newString = new char[newStringSize];
	memset(newString, 0, newStringSize);
	strncpy(newString, inputBuffer, strlen(inputBuffer));
	newString[strlen(inputBuffer)] = inputChar;
	delete[] inputBuffer;
	inputBuffer = newString;
}

void BluetoothMessageParser::copyInputBufferToFinishedMessageIfEmpty()
{
	// don't want to overwrite a message before the user can read it. 
	if( !hasMessage() )
		copyInputBufferToFinishedMessage();
}

void BluetoothMessageParser::copyInputBufferToFinishedMessage()
{
	delete[] finishedMessage;
	finishedMessage = makeCopyOfStringOnHeap(inputBuffer);
	clearInputBuffer();
	hasMessageFlag = true;
}

void BluetoothMessageParser::clearInputBuffer()
{
	delete[] inputBuffer;
	inputBuffer = makeCopyOfStringOnHeap("");
}

char* BluetoothMessageParser::makeCopyOfStringOnHeap(const char* inputStr)
{
	char* messageCopy = new char[strlen(inputStr)+1];
	strncpy(messageCopy, inputStr, strlen(inputStr)+1);
	return messageCopy;
}
