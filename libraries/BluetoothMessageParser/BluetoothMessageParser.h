#ifndef BLUETOOTH_MESSAGE_PARSER
#define BLUETOOTH_MESSAGE_PARSER

/* This class is intended to help BluetoothDrivers build up client messages one character at a time.
 * Separating this logic from the hardware specific BluetoothDriver class makes this unit-testable.
 */
class BluetoothMessageParser
{
public:
	BluetoothMessageParser();
	~BluetoothMessageParser();

	void giveCharacter(const char inputChar);
	bool hasMessage() const;
	const char* getMessage();	// consumes the message
	const char* peekMessage();	// returns the message without consuming it

	bool isClientConnected();

private:
	// methods
	void appendCharacterToInputBufferIfNotWhitespace(const char inputChar);
	void appendCharacterToInputBuffer(const char inputChar);
	void copyInputBufferToFinishedMessageIfEmpty();
	void copyInputBufferToFinishedMessage();
	void clearInputBuffer();

	// utility method for creating strings on the heap
	char* makeCopyOfStringOnHeap(const char* inputStr);

	// members
	char* finishedMessage;
	char* inputBuffer;
	bool hasMessageFlag;
	bool clientIsConnected;
	unsigned int ignoreChars;
};

#endif BLUETOOTH_MESSAGE_PARSER
