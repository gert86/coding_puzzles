#pragma once

#define CLASSNAME Template                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// TODO: Add description

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // TODO: Add implementation
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // TODO: Add test. Don't forget to include in main.
}

#undef CLASSNAME
