// IP Network Calculator: test_cidr.cpp - Vadella and Baker
#include "cidr.h"
#include "ip.h"
#include <iostream>
#include "gtest/gtest.h"

class CIDRTest : public testing::Test
{

    protected:
    cidr c;

    CIDRTest()
    {
        // You can do set-up work for each test here.
        std::string input = "192.168.1.0/24";
        c = cidr(input);
    }

    ~CIDRTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
};


TEST_F(CIDRTest, cidr_setup)
{
    EXPECT_EQ( c.nm_to_uint(24), 0xffffff00 );
    EXPECT_EQ( c.nm_to_uint(20), 0xfffff000 );
    EXPECT_NE( c.nm_to_uint(19), 0xfffff000 );
    EXPECT_EQ( c.uint_to_nm(0xffffff00), 24);
    EXPECT_EQ( c.uint_to_nm(0xfffff000), 20);
    EXPECT_NE( c.uint_to_nm(0xfffff000), 19);
    EXPECT_EQ( c.get_network(), 0xc0a80100 );
    EXPECT_EQ( c.get_bcast(), 0xc0a801ff );
}


TEST_F(CIDRTest, CIDR_to_uint32)
{
    EXPECT_EQ( ipv4::ipv4_to_uint("127.0.0.1"), 0x7f000001 );
    EXPECT_NE( ipv4::ipv4_to_uint("127.0.0.1"), 0x7f000002 );
    EXPECT_EQ( ipv4::ipv4_to_uint("10.0.1.255"), 0x0a0001ff );
    EXPECT_NE( ipv4::ipv4_to_uint("10.0.1.1"), 0x0a0001ff );
}

TEST_F(CIDRTest, uint32_to_string)
{
    EXPECT_EQ( ipv4::uint_to_ipv4(0x7f000001), "127.0.0.1" );
    EXPECT_NE( ipv4::uint_to_ipv4(0xc0a80105), "192.168.1.100" );
    EXPECT_EQ( ipv4::uint_to_ipv4(0x0a0001ff), "10.0.1.255" );
}


TEST_F(CIDRTest, CIDR_contains)
{
    EXPECT_EQ(cidr("192.168.1.100/24").contains(0xc0a80105), 24);
    EXPECT_EQ(cidr("10.0.1.0/29").contains(0x0a000105), 29);
    EXPECT_NE(cidr("192.168.1.100/24").contains(0xc0a80205), 24);
    EXPECT_EQ(cidr("192.168.1.100/24").contains(0xc0a80205), -1);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}