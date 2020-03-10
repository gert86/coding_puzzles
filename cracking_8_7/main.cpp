#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>
#include <cmath>

// common includes
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "doublylinkedlist.h"
#include "binarytree.h"
#include "graph.h"

using namespace std;


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


int main(int argc, char *argv[])
{    
    vector< QString > test_vector;
    test_vector.push_back( "" );        // 0
    test_vector.push_back( "a" );       // 1
    test_vector.push_back( "ab" );      // 2
    test_vector.push_back( "abc" );     // 6
    test_vector.push_back( "abcd" );    // 24
    test_vector.push_back( "abcde" );   // 120

    int mode = 3;  // 1, 2, 3
    cout << "Mode = " << mode << endl << endl;

    for(int i=0; i<test_vector.size(); i++)
    {
        // choose variant 1 or 2
        vector< QString > curr_permutations;
        if (mode == 1)  curr_permutations = permutations1(test_vector[i]);
        if (mode == 2)  curr_permutations = permutations2(test_vector[i]);
        if (mode == 3)  curr_permutations = permutations3(test_vector[i]);

        cout << "For string " << test_vector[i].toStdString() << " there are " << curr_permutations.size() << " permutations: " << endl;
        for (int j=0; j<curr_permutations.size(); j++)
        {
            //cout << "####  " << curr_permutations[j].toStdString() << endl;
        }
        //cout << endl << endl;
    }
    return 0;
}
