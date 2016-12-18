#include "MockLinxRxModule.h"
#include "MockGpioHandler.h"
#include "gtest/gtest.h"

void getTestAddrBus(int addrBus[LINX_ADDR_BUS_SIZE])
{
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        addrBus[i] = i+1;
}

void getTestDataBus(int dataBus[LINX_DATA_BUS_SIZE])
{
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        dataBus[i] = i+1+LINX_ADDR_BUS_SIZE;
}

int getTestVtPin()
{
    return LINX_ADDR_BUS_SIZE + LINX_DATA_BUS_SIZE + 1;
}

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

TEST(MockLinxRxModule, copyAddrBus)
{
    MockLinxRxModule rxer;
    int srcAddrBus[LINX_ADDR_BUS_SIZE];
    int dstAddrBus[LINX_ADDR_BUS_SIZE];
    
    // fill source bus array
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        srcAddrBus[i] = i+1;

    // copy the bus
    rxer.copyAddrBus(dstAddrBus, srcAddrBus);

    // verify dest bus array
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        ASSERT_EQ(srcAddrBus[i], dstAddrBus[i]);
}

TEST(MockLinxRxModule, copyDataBus)
{
    MockLinxRxModule rxer;
    int srcDataBus[LINX_DATA_BUS_SIZE];
    int dstDataBus[LINX_DATA_BUS_SIZE];
    
    // fill source bus array
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        srcDataBus[i] = i+1;

    // copy the bus
    rxer.copyDataBus(dstDataBus, srcDataBus);

    // verify dest bus array
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        ASSERT_EQ(srcDataBus[i], dstDataBus[i]);   
}

TEST(MockLinxRxModule, initializePins)
{
    MockGpioHandler* pinHandler = new MockGpioHandler();
    int addrBus[LINX_ADDR_BUS_SIZE];
    int dataBus[LINX_DATA_BUS_SIZE];
    int vtPin = getTestVtPin();
    getTestAddrBus(addrBus);
    getTestDataBus(dataBus);
    MockLinxRxModule rxer(pinHandler, addrBus, dataBus, vtPin);

    // verify addr bus configured for output
    for( unsigned int i=0; i<LINX_ADDR_BUS_SIZE; ++i )
        ASSERT_TRUE(pinHandler->isPinConfiguredForOutput(addrBus[i]));

    // verify data bus configured for input
    for( unsigned int i=0; i<LINX_DATA_BUS_SIZE; ++i )
        ASSERT_TRUE(pinHandler->isPinConfiguredForInput(dataBus[i]));

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
    int addrBus[LINX_ADDR_BUS_SIZE];
    int dataBus[LINX_DATA_BUS_SIZE];
    int vtPin = getTestVtPin();
    getTestAddrBus(addrBus);
    getTestDataBus(dataBus);
    MockLinxRxModule rxer(pinHandler, addrBus, dataBus, vtPin);

    rxer.setAddress(0b1010101010);
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus[0]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus[1]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus[2]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus[3]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus[4]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus[5]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus[6]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus[7]));
    ASSERT_FALSE(pinHandler->isPinHigh(addrBus[8]));
    ASSERT_TRUE(pinHandler->isPinHigh(addrBus[9]));
}
