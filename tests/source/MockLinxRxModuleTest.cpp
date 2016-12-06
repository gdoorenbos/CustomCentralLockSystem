#include "gtest/gtest.h"
#include "MockLinxRxModule.h"

TEST(MockLinxRxModule, setAddress)
{
	MockLinxRxModule rxer;
    unsigned short assignedAddress;

	rxer.setAddress(500);
	assignedAddress = rxer.getAddress();
	ASSERT_TRUE(assignedAddress == 500);

	rxer.setAddress(750);
	assignedAddress = rxer.getAddress();
	ASSERT_TRUE(assignedAddress == 750);
}

TEST(MockLinxRxModule, validTransmissionSetOnValidTransmission)
{
    MockLinxRxModule rxer;

    rxer.giveTransmission(1);
    ASSERT_TRUE(rxer.hasValidTransmission());

    rxer.giveTransmission(0);
    ASSERT_FALSE(rxer.hasValidTransmission());

    rxer.giveTransmission(2);
    ASSERT_TRUE(rxer.hasValidTransmission());

    rxer.giveTransmission(10);
    ASSERT_FALSE(rxer.hasValidTransmission());

    rxer.giveTransmission(4);
    ASSERT_TRUE(rxer.hasValidTransmission());
}

TEST(MockLinxRxModule, checkingDataBits)
{
    MockLinxRxModule rxer;

    rxer.giveTransmission(0);
    for (unsigned char i = 1; i <+ 5; ++i)
        ASSERT_FALSE(rxer.getDataBit(i));

    rxer.giveTransmission(2);
    for (unsigned char i = 1; i <= 5; ++i)
    {
        if( i == 1 )
            ASSERT_TRUE(rxer.getDataBit(i));
        else
            ASSERT_FALSE(rxer.getDataBit(i));
    }
}
