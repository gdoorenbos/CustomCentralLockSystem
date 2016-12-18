#include "MockLinxRxModule.h"
#include "MockGpioHandler.h"
#include "gtest/gtest.h"

void assertFobButtonPress(MockLinxRxModule &rxer, unsigned int button)
{
    rxer.pushFobButton(button);
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
    {
        if( i == button-1 )
            ASSERT_TRUE(rxer.getDataBit(i));
        else
            ASSERT_FALSE(rxer.getDataBit(i));
    }
}

TEST(MockLinxRxModule, setAddress)
{
	MockLinxRxModule rxer;

	rxer.setAddress(500);
    ASSERT_EQ(500, rxer.getAddress());

	rxer.setAddress(750);
    ASSERT_EQ(750, rxer.getAddress());
}

TEST(MockLinxRxModule, validTransmissionSetOnValidTransmission)
{
    MockLinxRxModule rxer;

    rxer.pushFobButton(1);
    ASSERT_TRUE(rxer.hasValidTransmission());

    rxer.pushFobButton(0);
    ASSERT_FALSE(rxer.hasValidTransmission());

    rxer.pushFobButton(2);
    ASSERT_TRUE(rxer.hasValidTransmission());

    rxer.pushFobButton(10);
    ASSERT_FALSE(rxer.hasValidTransmission());

    rxer.pushFobButton(4);
    ASSERT_TRUE(rxer.hasValidTransmission());
}

TEST(MockLinxRxModule, checkingDataBits)
{
    MockLinxRxModule rxer;

    // invalid button press
    rxer.pushFobButton(0);
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        ASSERT_FALSE(rxer.getDataBit(i));

    for( unsigned int i=1; i<=5; ++i )
        assertFobButtonPress(rxer, i);
}

TEST(MockLinxRxModule, initializePins)
{
    MockGpioHandler* pinHandler = new MockGpioHandler();
    MockLinxRxModule rxer(pinHandler);
    LinxAddrBus addrBus = rxer.getTestAddrBus();
    LinxDataBus dataBus = rxer.getTestDataBus();
    int vtPin = rxer.getTestVtPin();

    // verify addr bus configured for output
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        ASSERT_TRUE(pinHandler->isPinConfiguredForOutput(addrBus.a[i]));

    // verify data bus configured for input
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        ASSERT_TRUE(pinHandler->isPinConfiguredForInput(dataBus.d[i]));

    // verify vtPin configured for input
    ASSERT_TRUE(pinHandler->isPinConfiguredForInput(vtPin));
}

TEST(MockLinxRxModule, getBitFromNumber)
{
    MockLinxRxModule rxer;
    
    ASSERT_FALSE(rxer.getBitFromNumber(0, 0b10100110));
    ASSERT_TRUE(rxer.getBitFromNumber(1, 0b10100110));
    ASSERT_TRUE(rxer.getBitFromNumber(2, 0b10100110));
    ASSERT_FALSE(rxer.getBitFromNumber(3, 0b10100110));
    ASSERT_FALSE(rxer.getBitFromNumber(4, 0b10100110));
    ASSERT_TRUE(rxer.getBitFromNumber(5, 0b10100110));
    ASSERT_FALSE(rxer.getBitFromNumber(6, 0b10100110));
    ASSERT_TRUE(rxer.getBitFromNumber(7, 0b10100110));
}

TEST(MockLinxRxModule, setAddressAndCheckPins)
{
    MockGpioHandler* pinHandler = new MockGpioHandler();
    MockLinxRxModule rxer(pinHandler);
    LinxAddrBus addrBus = rxer.getTestAddrBus();

    rxer.setAddress(0b1010101010);
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus.a[0]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus.a[1]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus.a[2]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus.a[3]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus.a[4]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus.a[5]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus.a[6]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus.a[7]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus.a[8]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus.a[9]));
}
