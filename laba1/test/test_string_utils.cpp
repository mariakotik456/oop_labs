#include <gtest/gtest.h>
#include "../include/string_utils.h"

TEST(StringUtilsTest, ExtractNumbersFromMixedString)
{
    std::string input = "a1b23c456d";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "123456");
}

TEST(StringUtilsTest, ExtractNumbersOnlyLetters)
{
    std::string input = "abcdef";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "");
}

TEST(StringUtilsTest, ExtractNumbersOnlyDigits)
{
    std::string input = "123456";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "123456");
}

TEST(StringUtilsTest, ExtractNumbersEmptyString)
{
    std::string input = "";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "");
}

TEST(StringUtilsTest, ExtractNumbersWithSpacesAndSymbols)
{
    std::string input = "a1 b2!c3@";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "123");
}

TEST(StringUtilsTest, ExtractNumbersUnicodeCharacters)
{
    std::string input = "тест123тест";
    std::string result = extractNumbers(input);
    EXPECT_EQ(result, "123");
}