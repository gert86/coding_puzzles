#pragma once

#define CLASSNAME Cracking_8_7

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Permutations without Dups: Write a method to compute all permutations of a string of unique
// characters.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Helper function
    QString insertCharAtIndex(QString str, QChar ch, int index)
    {
        if (index < 0 || index > str.length())
        {
            cerr << "insertCharAtIndex called out-of-bounds (index=" << index << ")" << endl;
            return str;
        }

        return str.left(index) + ch + str.mid(index);
    }

    // Helper function
    QString removeCharAtIndex(QString str, int index)
    {
        if (index < 0 || index >= str.length())
        {
            cerr << "removeCharAtIndex called out-of-bounds (index=" << index << ")" << endl;
            return str;
        }

        QString before = str.left(index);
        QString after = str.mid(index+1);
        return before.append(after);
    }


    // Variant 1: Build permutation of N chars by
    //  * removing first char
    //  * create permutations of trailing (N-1) chars
    //  * placing first char at every possible position in each of the "trailing permutations".
    vector< QString > permutations1(QString str)
    {
        vector< QString > perms;

        // Base cases
        if(str.length() == 0)
        {
            return perms;
        }
        if(str.length() == 1)
        {
            perms.push_back(str);
            return perms;
        }

        // remove first char and find permutations of remaining chars
        QChar first_char = str.at(0);    // conversion to QString would be str.left(1) !!!
        QString remainder_str = str.mid(1);
        auto remainder_perms = permutations1(remainder_str);

        // place char i at every possible position of each remainder permutation
        for (auto remainder_perm : remainder_perms)
        {
            for (int i=0; i<=remainder_perm.length(); i++)
            {
                perms.push_back( insertCharAtIndex(remainder_perm, first_char, i) );
            }
        }

        return perms;
    }


    // Variant 2: Build permutation of N chars by
    //  * for i=0:N-1: remove i-th char
    //  *              create permutations of remaining (N-1) chars
    //  *              place i-th char at first position in each of the "remaining permutations".
    vector< QString > permutations2(QString str)
    {
        vector< QString > perms;

        // Base cases
        if(str.length() == 0)
        {
            return perms;
        }
        if(str.length() == 1)
        {
            perms.push_back(str);
            return perms;
        }


        for (int i=0; i<str.length(); i++)
        {
            // remove char i and find permutations of remaining chars
            QChar ith_char = str.at(i);
            QString remainder_str = removeCharAtIndex(str, i);
            auto remainder_perms = permutations2(remainder_str);

            // prepend char i to each permutation
            for (auto remainder_perm : remainder_perms)
            {
                perms.push_back( remainder_perm.prepend(ith_char) );
            }
        }
        return perms;
    }


    // Variant 3: Use STL functionality
    vector< QString > permutations3(QString str)
    {
        vector< QString > perms;

        // This is a question of definition. The do/while would output 1 otherwise for empty string!
        if (str.size()==0)
            return perms;

        string std_str = str.toStdString();
        std::sort(std_str.begin(), std_str.end());
        do
        {
            perms.push_back( QString(std_str.c_str()) );
        } while ( std::next_permutation(std_str.begin(), std_str.end()) );

        return perms;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< QString > test_vector;      vector<size_t>  result_vector;
    test_vector.push_back( "" );        result_vector.push_back(0);
    test_vector.push_back( "a" );       result_vector.push_back(1);
    test_vector.push_back( "ab" );      result_vector.push_back(2);
    test_vector.push_back( "abc" );     result_vector.push_back(6);
    test_vector.push_back( "abcd" );    result_vector.push_back(24);
    test_vector.push_back( "abcde" );   result_vector.push_back(120);

    for(int i=0; i<test_vector.size(); i++)
    {
        vector< QString >  permutations_mode1 = instance.permutations1(test_vector[i]);
        cout << "String " << test_vector[i].toStdString() << " has " << permutations_mode1.size() << " permutations: " << endl;
        ASSERT_EQ(result_vector[i], permutations_mode1.size());

        vector< QString >  permutations_mode2 = instance.permutations2(test_vector[i]);
        cout << "--> Same for calculation method #2." << endl;

        vector< QString >  permutations_mode3 = instance.permutations3(test_vector[i]);
        cout << "--> Same for calculation method #3." << endl << endl;
    }
}

#undef CLASSNAME
