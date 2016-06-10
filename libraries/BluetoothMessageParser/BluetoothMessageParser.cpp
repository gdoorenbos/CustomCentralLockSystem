#include "BluetoothMessageParser.h"
#include <string.h>

BluetoothMessageParser::BluetoothMessageParser()
	: inputBuffer(0)
	, finishedMessage(0)
	, hasMessageFlag(false)
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
	if( inputChar == '\n' )
	{
		// have a full message - need to set flag
		hasMessageFlag = true;

		// copy input buffer to finished message, but only if finishedMessage is empty
		if( finishedMessage == 0 )
		{
			if( inputBuffer != 0 )
			{
				finishedMessage = new char[strlen(inputBuffer)+1];
				strncpy(finishedMessage, inputBuffer, strlen(inputBuffer)+1);
				delete[] inputBuffer;
				inputBuffer = 0;
			}
			else
			{
				// inputBuffer is empty, so put empty string in finishedMessage. 
				finishedMessage = new char[1];
				finishedMessage[0] = '\0';
			}
		}
	}
	else
	{
		if( inputBuffer == 0 )
		{
			inputBuffer = new char[2];
			memset(inputBuffer, 0, 2);
			inputBuffer[0] = inputChar;
		}
		else
		{
			int newStringSize = strlen(inputBuffer) + 1 + 1;	// +1 for inputChar and +1 for terminating null char
			char* newString = new char[newStringSize];
			memset(newString, 0, newStringSize);
			strncpy(newString, inputBuffer, strlen(inputBuffer));
			newString[strlen(inputBuffer)] = inputChar;
			delete[] inputBuffer;
			inputBuffer = newString;
		}

	}
}

bool BluetoothMessageParser::hasMessage() const
{
	return hasMessageFlag;
}

const char* BluetoothMessageParser::getMessage()
{
	hasMessageFlag = false;
	if( finishedMessage != 0 )
	{
		// make copy on heap and return
		char* messageCopy = new char[strlen(finishedMessage)+1];
		strncpy(messageCopy, finishedMessage, strlen(finishedMessage)+1);
		delete[] finishedMessage;
		finishedMessage = 0;

		return messageCopy;
	}
	else
	{
		char* emptyStr = new char[1];
		emptyStr[0] = '\0';
		return emptyStr;
	}
}
