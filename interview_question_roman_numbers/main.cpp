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

#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>



using namespace std;


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


int main(int argc, char *argv[])
{    

    int number = 2019;
    QString converted_num = convertToRoman(number);
    cout << "The Roman representation of " << number << " is " << converted_num.toStdString() << endl;

    return 0;
}
