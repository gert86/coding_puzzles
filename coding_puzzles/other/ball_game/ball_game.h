#pragma once

#define CLASSNAME Ball_Game

#include "base_header.h"
#include "Game.h"

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }
};

TEST(CLASSNAME, Test1)
{    
    Game g;
    g.init();
    int ret = g.mainLoop();

    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
}

#undef CLASSNAME
