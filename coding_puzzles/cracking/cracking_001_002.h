#pragma once

#define CLASSNAME Cracking_1_2

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Check Permutation: Given two strings, write a method to decide if one is a permutation of the other

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

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
};

TEST(CLASSNAME, TestQString)
{    
    CLASSNAME instance;

    QString str_ref = "aabbbaa";

    vector<QString>  test_vector;       vector<int>  result_vector;
    test_vector.push_back("aabbbAa");   result_vector.push_back(false);  // Note: only when case-sensitive, otherwise true
    test_vector.push_back("aaaabba");   result_vector.push_back(false);
    test_vector.push_back("aabbaac");   result_vector.push_back(false);
    test_vector.push_back("aaabbab");   result_vector.push_back(true);

    for (int i=0; i<test_vector.size(); i++)
    {
        bool is_permutation = instance.isStringPermutationQtString( str_ref, test_vector[i] );
        cout << "QString Comparison of " << str_ref.toStdString() << " and " << test_vector[i].toStdString() << " is " << is_permutation << std::endl;
        ASSERT_EQ(result_vector[i], is_permutation);
    }
}

TEST(CLASSNAME, TestStdString)
{
    CLASSNAME instance;

    string str_ref = "aabbbaa";

    vector<string>  test_vector;        vector<int>  result_vector;
    test_vector.push_back("aabbbAa");   result_vector.push_back(false);
    test_vector.push_back("aaaabba");   result_vector.push_back(false);
    test_vector.push_back("aabbaac");   result_vector.push_back(false);
    test_vector.push_back("aaabbab");   result_vector.push_back(true);

    for (int i=0; i<test_vector.size(); i++)
    {
        bool is_permutation = instance.isStringPermutationStdString( str_ref, test_vector[i] );
        cout << "std::string comparison of " << str_ref << " and " << test_vector[i] << " is " << is_permutation << std::endl;
        ASSERT_EQ(result_vector[i], is_permutation);
    }
}

#undef CLASSNAME
