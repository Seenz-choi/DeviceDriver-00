#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD/test_03.cpp"
#include "windows.h"
using namespace testing;
using namespace std;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long addr), (override));
	MOCK_METHOD(void, write, (long addr, unsigned char data), (override));
};

TEST(MockTest, TCREAD_00)
{
	FlashMemoryDeviceMock fmdm;
	DeviceDriver dd(&fmdm);
	EXPECT_CALL(fmdm, read(_))
		.WillRepeatedly(Return(0x0A));
	EXPECT_THAT(0x0A, dd.read(0X00));
}
TEST(MockTest, TCREAD_01)
{
	FlashMemoryDeviceMock fmdm;
	DeviceDriver dd(&fmdm);
	EXPECT_CALL(fmdm, read(_))
		.WillOnce(Return(0x0B))
		.WillRepeatedly(Return(0x0A));
	
	EXPECT_THROW(dd.read(0X00), ReadFailException);
}

TEST(MockTest, TCWRITE_00)
{
	FlashMemoryDeviceMock fmdm;
	DeviceDriver dd(&fmdm);
	EXPECT_CALL(fmdm, read(_))
		.WillRepeatedly(Return(0x0A));

	EXPECT_THROW(dd.write(0X00, 0x0B), WriteFailException);
}

TEST(MockTest, TCWRITE_01)
{
	FlashMemoryDeviceMock fmdm;
	DeviceDriver dd(&fmdm);
	EXPECT_CALL(fmdm, read(_))
		.WillRepeatedly(Return(0xFF));

	EXPECT_THROW(dd.write(0X00, 0x0B), WriteFailException);
}