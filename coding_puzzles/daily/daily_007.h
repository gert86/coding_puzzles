#pragma once

#define CLASSNAME Daily_007

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.
//
//For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.
//
//You can assume that the messages are decodable. For example, '001' is not allowed.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool isValidSingleDigit(QChar character)
    {
        if (character.isDigit() && character!='0')
        {
            return true;
        }
        return false;
    }

    bool isValidDoubleDigit(QStringRef characters)
    {
        if (characters.length() != 2)
        {
            return false;
        }

        bool conversion_ok = false;
        int converted_int = characters.toInt(&conversion_ok);

        if (!conversion_ok)
        {
            return false;
        }

        return (converted_int>=10 && converted_int<=26);
    }


    int countPossibilities(QString encoded_message)
    {
        int num_chars = encoded_message.length();

        vector<int> possibilities;
        possibilities.resize(num_chars + 1);

        // base cases
        if (num_chars == 0)
            return 0;

        if (num_chars == 1)
            return (isValidSingleDigit(encoded_message.at(0)) ? (1) : (0));

        possibilities[0] = 1;  // per definition
        possibilities[1] = (int)isValidSingleDigit(encoded_message.at(0));

        for (int i=2; i<=num_chars; i++)
        {
            int num_pos = 0;
            QChar single_digit(encoded_message.at(i-1));
            if( isValidSingleDigit(single_digit) )
                num_pos += possibilities[i-1];

            QStringRef double_digit(&encoded_message, i-2, 2);
            if( isValidDoubleDigit(double_digit) )
                num_pos += possibilities[i-2];

            possibilities[i] = num_pos;
        }

        return possibilities[num_chars];
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< QString >  test_vector;     vector<int>  result_vector;
    test_vector.push_back("");          result_vector.push_back(0);
    test_vector.push_back("1");         result_vector.push_back(1);
    test_vector.push_back("11");        result_vector.push_back(2);
    test_vector.push_back("10");        result_vector.push_back(1);
    test_vector.push_back("29");        result_vector.push_back(1);
    test_vector.push_back("90");        result_vector.push_back(0);
    test_vector.push_back("09");        result_vector.push_back(0);
    test_vector.push_back("20");        result_vector.push_back(1);
    test_vector.push_back("1227");      result_vector.push_back(3);
    test_vector.push_back("11010");     result_vector.push_back(1);

    for (int i=0; i<test_vector.size(); i++)
    {
        int num_possibilities = instance.countPossibilities( test_vector[i] );
        cout << "Test #" << (i+1) << " results in " << num_possibilities << endl;
        ASSERT_EQ(result_vector[i], num_possibilities);
    }
}

#undef CLASSNAME
