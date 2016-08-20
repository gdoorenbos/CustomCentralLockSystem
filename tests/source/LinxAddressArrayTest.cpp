#include "gtest/gtest.h"
#include "LinxAddressArray.h"

TEST(LinxAddressArray, verifyAddress500)
{
    LinxAddressArray array(500);

    // ‭0001 1111 0100‬
    ASSERT_FALSE(array.getAddressBit(0));
    ASSERT_FALSE(array.getAddressBit(1));
    ASSERT_TRUE(array.getAddressBit(2));
    ASSERT_FALSE(array.getAddressBit(3));

    ASSERT_TRUE(array.getAddressBit(4));
    ASSERT_TRUE(array.getAddressBit(5));
    ASSERT_TRUE(array.getAddressBit(6));
    ASSERT_TRUE(array.getAddressBit(7));

    ASSERT_TRUE(array.getAddressBit(8));
    ASSERT_FALSE(array.getAddressBit(9));
    ASSERT_FALSE(array.getAddressBit(10));
    ASSERT_FALSE(array.getAddressBit(11));
}

TEST(LinxAddressArray, verifyAddress523)
{
    LinxAddressArray array(523);

    // ‭0010 0000 1011
    ASSERT_TRUE(array.getAddressBit(0));
    ASSERT_TRUE(array.getAddressBit(1));
    ASSERT_FALSE(array.getAddressBit(2));
    ASSERT_TRUE(array.getAddressBit(3));
    
    ASSERT_FALSE(array.getAddressBit(4));
    ASSERT_FALSE(array.getAddressBit(5));
    ASSERT_FALSE(array.getAddressBit(6));
    ASSERT_FALSE(array.getAddressBit(7));

    ASSERT_FALSE(array.getAddressBit(8));
    ASSERT_TRUE(array.getAddressBit(9));
    ASSERT_FALSE(array.getAddressBit(10));
    ASSERT_FALSE(array.getAddressBit(11));
}

/* The Linx address is only 10 bits long. If the LinxAddressArray object receives an address longer than 10 bits, 
 * it should throw the upper bits away.
 */
TEST(LinxAddressArray, invalidAddressGiven)
{
    LinxAddressArray array(1050);

    // ‭0100 0001 1010‬
    //  ^this bit should get thrown away
    ASSERT_FALSE(array.getAddressBit(0));
    ASSERT_TRUE(array.getAddressBit(1));
    ASSERT_FALSE(array.getAddressBit(2));
    ASSERT_TRUE(array.getAddressBit(3));

    ASSERT_TRUE(array.getAddressBit(4));
    ASSERT_FALSE(array.getAddressBit(5));
    ASSERT_FALSE(array.getAddressBit(6));
    ASSERT_FALSE(array.getAddressBit(7));

    ASSERT_FALSE(array.getAddressBit(8));
    ASSERT_FALSE(array.getAddressBit(9));
    ASSERT_FALSE(array.getAddressBit(10));
    ASSERT_FALSE(array.getAddressBit(11));
}
