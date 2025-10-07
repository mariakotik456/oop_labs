#include <gtest/gtest.h>
#include "../include/quinary_integer.h"

TEST(QuinaryIntegerTest, DefaultConstructor)
{
    QuinaryInteger num;
    EXPECT_EQ(num.toString(), "0");
    EXPECT_EQ(num.size(), 1);
}

TEST(QuinaryIntegerTest, StringConstructor)
{
    QuinaryInteger num("132");
    EXPECT_EQ(num.toString(), "132");
}

TEST(QuinaryIntegerTest, StringConstructorInvalidDigit)
{
    EXPECT_THROW(QuinaryInteger("135"), std::invalid_argument);
}

TEST(QuinaryIntegerTest, SizeConstructor)
{
    QuinaryInteger num(3, 2);
    EXPECT_EQ(num.toString(), "222");
}

TEST(QuinaryIntegerTest, SizeConstructorInvalidValue)
{
    EXPECT_THROW(QuinaryInteger(3, 5), std::invalid_argument);
}

TEST(QuinaryIntegerTest, CopyConstructor)
{
    QuinaryInteger num1("132");
    QuinaryInteger num2(num1);
    EXPECT_EQ(num2.toString(), "132");
    EXPECT_TRUE(num1.equals(num2));
}

TEST(QuinaryIntegerTest, AddOperation)
{
    QuinaryInteger num1("12");
    QuinaryInteger num2("23");
    QuinaryInteger result = num1.add(num2);
    EXPECT_EQ(result.toString(), "40");

    TEST(QuinaryIntegerTest, SubtractOperation)
    {
        QuinaryInteger num1("23");
        QuinaryInteger num2("12");
        QuinaryInteger result = num1.subtract(num2);
        EXPECT_EQ(result.toString(), "11");
    }

    TEST(QuinaryIntegerTest, SubtractNegativeResult)
    {
        QuinaryInteger num1("12");
        QuinaryInteger num2("23");
        EXPECT_THROW(num1.subtract(num2), std::invalid_argument);
    }

    TEST(QuinaryIntegerTest, CompareOperations)
    {
        QuinaryInteger num1("12");
        QuinaryInteger num2("23");

        EXPECT_TRUE(num1.lessThan(num2));
        EXPECT_TRUE(num2.greaterThan(num1));
        EXPECT_TRUE(num1.equals(num1));
    }

    TEST(QuinaryIntegerTest, RemoveLeadingZeros)
    {
        QuinaryInteger num("000132");
        EXPECT_EQ(num.toString(), "132");
    }

    TEST(QuinaryIntegerTest, LargeNumbers)
    {
        QuinaryInteger num1("123401234012340");
        QuinaryInteger num2("432104321043210");
        QuinaryInteger sum = num1.add(num2);
        EXPECT_FALSE(sum.toString().empty());
    }

    TEST(QuinaryIntegerTest, CopyMethod)
    {
        QuinaryInteger num1("132");
        QuinaryInteger num2 = num1.copy();
        EXPECT_EQ(num2.toString(), "132");
        EXPECT_TRUE(num1.equals(num2));
    }

    TEST(QuinaryIntegerTest, AddAssignMethod)
    {
        QuinaryInteger num1("12");
        QuinaryInteger num2("23");
        QuinaryInteger result = num1.addAssign(num2);
        EXPECT_EQ(result.toString(), "40");
    }