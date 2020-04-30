#pragma once

#define CLASSNAME Daily_123                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a string, return whether it represents a number. Here are the different kinds of numbers:
//    "10", a positive integer
//    "-10", a negative integer
//    "10.1", a positive real number
//    "-10.1", a negative real number
//    "1e5", a number in scientific notation
// And here are examples of non-numbers:
//    "a"
//    "x 1"
//    "a -2"
//    "-"


# include <regex>

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool isConvertibleToNumberRegex(const std::string &str)
    {
        // Inspired from: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
        return std::regex_match( str, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) ) ||
               std::regex_match( str, std::regex( ( "((\\+|-)?[[:digit:]]+)(e(\\+|-)?(([[:digit:]]+)?))?" ) ) );
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("10"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("+10"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("-10"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("10.1"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("-10.1345"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("-10.13245234"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("1e5"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("-56e5"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("9e-5"));
    ASSERT_EQ(true, instance.isConvertibleToNumberRegex("-17e-15"));

    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("a"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("x 1"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("a -2"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("-"));

    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("+-10"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("-+10"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("++10"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10-"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10+"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10 "));

    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10.+1"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10.1-"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10.e1"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10e.1"));

    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10.4e5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("10e6.5"));

    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1..5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1,5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1ee5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1E5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1f5"));
    ASSERT_EQ(false, instance.isConvertibleToNumberRegex("1 5"));
}

#undef CLASSNAME
