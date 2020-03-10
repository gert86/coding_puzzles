// Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.
//
//For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.
//
//You can assume that the messages are decodable. For example, '001' is not allowed.

#include<QString>
#include<QChar>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;


// Notes:
// The problem can be tackled recursively. Without any restriction on the message characters, there would be two ways to get to
// the N-th character, i.e. from (N-1) and decoding a single character or from (N-2) and decoding two characters.
// So this is the same as the staircase problem where the number of possibilities is the N-th fibonacci number.
// In this case the N-th Fibonacci number is the upper bound of possibilities because of two restrictions:
//
// 1: Decoding a single character is only possible if it is [1-9] (not 0)
// 2: Decoding two characters is only possible if they are [10-26]


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



int main()
{    
    QString test01 = "";                // 0
    QString test02 = "1";               // 1
    QString test03 = "11";              // 2
    QString test04 = "10";              // 1
    QString test05 = "29";              // 1
    QString test06 = "90";              // 0
    QString test07 = "09";              // 0
    QString test08 = "20";              // 1
    QString test09 = "1227";            // 3
    QString test10 = "11010";           // 1


    vector< QString>  test_vector;
    test_vector.push_back(test01);
    test_vector.push_back(test02);
    test_vector.push_back(test03);
    test_vector.push_back(test04);
    test_vector.push_back(test05);
    test_vector.push_back(test06);
    test_vector.push_back(test07);
    test_vector.push_back(test08);
    test_vector.push_back(test09);
    test_vector.push_back(test10);


    for (int i=0; i<test_vector.size(); i++)
    {
        int num_possibiliies = countPossibilities( test_vector[i] );
        cout << "Test #" << (i+1) << " results in " << num_possibiliies << endl;
    }

    return 0;
}

