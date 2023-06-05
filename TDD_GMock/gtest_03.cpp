#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD/test_03.cpp"
using namespace testing;
using namespace std;

TEST(MockTest, TC00)
{
	EXPECT_THAT(1, Eq(1));
}