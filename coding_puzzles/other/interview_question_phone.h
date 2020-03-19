#pragma once

#define CLASSNAME Interview_Question_Phone

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Write a function to convert a given number into a string that gives you the Roman number.
// You can assume that the number is between 1 and 3999
//
// I = 1
// V = 5
// X = 10
// L = 50
// C = 100
// D = 500
// M = 1000

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    QString convertDigit(int digit, QString low, QString mid, QString high)
    {
        QString str;

        if (digit < 0 || digit > 9)
        {
            cerr << "convertDigit expects digit from 0 - 9" << endl;
            exit(-1);
        }

        if (digit == 0)
            return str;

        if (digit <= 3)
        {
            for (int i=0; i<digit; i++)
                str.append(low);
        }
        else if (digit <= 5)
        {
            for (int i=0; i<5-digit; i++)
                str.append(low);
            str.append(mid);
        }
        else if (digit <= 8)
        {
            str.append(mid);
            for (int i=0; i<digit-5; i++)
                str.append(low);
        }
        else
        {
            str.append(low);
            str.append(high);
        }

        return str;
    }


    QString convertToRoman(int number)
    {
        QString str = "";

        if (number <= 0 || number > 3999)
        {
            cerr << "Out of bounds." << endl;
            return str;
        }

        int digit_one = number % 10;
        int digit_ten = (number % 100) / 10;
        int digit_hundred = (number % 1000) / 100;
        int digit_thousand = (number % 10000) / 1000;

        QString part_one =      convertDigit(digit_one, "I", "V", "X");
        QString part_ten =      convertDigit(digit_ten, "X", "L", "C");
        QString part_hundred =  convertDigit(digit_hundred, "C", "D", "M");
        QString part_thousand = convertDigit(digit_thousand, "M", "---", "---");

        str.append(part_thousand).append(part_hundred).append(part_ten).append(part_one);

        return str;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<int>  test_vector;         vector<QString>  result_vector;
    test_vector.push_back(1);         result_vector.push_back(QString("I"));
    test_vector.push_back(2);         result_vector.push_back(QString("II"));
    test_vector.push_back(3);         result_vector.push_back(QString("III"));
    test_vector.push_back(4);         result_vector.push_back(QString("IV"));
    test_vector.push_back(5);         result_vector.push_back(QString("V"));
    test_vector.push_back(9);         result_vector.push_back(QString("IX"));
    test_vector.push_back(10);        result_vector.push_back(QString("X"));
    test_vector.push_back(20);        result_vector.push_back(QString("XX"));
    test_vector.push_back(34);        result_vector.push_back(QString("XXXIV"));
    test_vector.push_back(47);        result_vector.push_back(QString("XLVII"));
    test_vector.push_back(66);        result_vector.push_back(QString("LXVI"));
    test_vector.push_back(89);        result_vector.push_back(QString("LXXXIX"));
    test_vector.push_back(99);        result_vector.push_back(QString("XCIX"));
    test_vector.push_back(100);       result_vector.push_back(QString("C"));
    test_vector.push_back(230);       result_vector.push_back(QString("CCXXX"));
    test_vector.push_back(355);       result_vector.push_back(QString("CCCLV"));
    test_vector.push_back(491);       result_vector.push_back(QString("CDXCI"));
    test_vector.push_back(500);       result_vector.push_back(QString("D"));
    test_vector.push_back(505);       result_vector.push_back(QString("DV"));
    test_vector.push_back(762);       result_vector.push_back(QString("DCCLXII"));
    test_vector.push_back(999);       result_vector.push_back(QString("CMXCIX"));
    test_vector.push_back(1000);      result_vector.push_back(QString("M"));
    test_vector.push_back(1001);      result_vector.push_back(QString("MI"));
    test_vector.push_back(1010);      result_vector.push_back(QString("MX"));
    test_vector.push_back(1500);      result_vector.push_back(QString("MD"));
    test_vector.push_back(1898);      result_vector.push_back(QString("MDCCCXCVIII"));
    test_vector.push_back(2000);      result_vector.push_back(QString("MM"));
    test_vector.push_back(2020);      result_vector.push_back(QString("MMXX"));
    test_vector.push_back(2999);      result_vector.push_back(QString("MMCMXCIX"));
    test_vector.push_back(3000);      result_vector.push_back(QString("MMM"));
    test_vector.push_back(3333);      result_vector.push_back(QString("MMMCCCXXXIII"));
    test_vector.push_back(3997);      result_vector.push_back(QString("MMMCMXCVII"));
    test_vector.push_back(3998);      result_vector.push_back(QString("MMMCMXCVIII"));
    test_vector.push_back(3999);      result_vector.push_back(QString("MMMCMXCIX"));

    for (int i=0; i<test_vector.size(); i++)
    {
        QString converted_num = instance.convertToRoman(test_vector[i]);
        cout << "Number " << test_vector[i] << " converts to " << converted_num.toStdString() << endl;
        ASSERT_EQ(result_vector[i], converted_num);
    }
}

#undef CLASSNAME
