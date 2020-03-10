#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <string>

using namespace std;

bool isStringPermutationQtString(QString str1, QString str2)
{
    if (str1.length() != str2.length())
        return false;

    std::sort(str1.begin(), str1.end());
    std::sort(str2.begin(), str2.end());

    //cout << "|Str1 = " << str1.toStdString() << " and str2 = " << str2.toStdString() << "|";

    return ( str1.compare(str2, Qt::CaseSensitive) == 0);
}

bool isStringPermutationStdString(string str1, string str2)
{
    if (str1.size() != str2.size())
        return false;

    std::sort(str1.begin(), str1.end());
    std::sort(str2.begin(), str2.end());

    //cout << "|Str1 = " << str1 << " and str2 = " << str2 << "|";

    return ( str1.compare(str2) == 0 );
}



int main()
{

    QString str_ref = "aabbbaa";
    QString str1    = "aabbbAa";
    QString str2    = "aaaabba";
    QString str3    = "aabbaac";
    QString str4    = "aaabbab";

    std::cout << "Qt Comparison #1 is " << isStringPermutationQtString(str_ref, str1) << std::endl;  // expected: true (when case-insensitive)
    std::cout << "Qt Comparison #2 is " << isStringPermutationQtString(str_ref, str2) << std::endl;  // expected: false
    std::cout << "Qt Comparison #3 is " << isStringPermutationQtString(str_ref, str3) << std::endl;  // expected: false
    std::cout << "Qt Comparison #4 is " << isStringPermutationQtString(str_ref, str4) << std::endl;  // expected: true



    string str_ref_std = str_ref.toStdString();
    string str1_std    = str1.toStdString();
    string str2_std    = str2.toStdString();
    string str3_std    = str3.toStdString();
    string str4_std    = str4.toStdString();


    std::cout << "STL Comparison #1 is " << isStringPermutationStdString(str_ref_std, str1_std) << std::endl;  // expected: false
    std::cout << "STL Comparison #2 is " << isStringPermutationStdString(str_ref_std, str2_std) << std::endl;  // expected: false
    std::cout << "STL Comparison #3 is " << isStringPermutationStdString(str_ref_std, str3_std) << std::endl;  // expected: false
    std::cout << "STL Comparison #4 is " << isStringPermutationStdString(str_ref_std, str4_std) << std::endl;  // expected: true


    return 0;
}
