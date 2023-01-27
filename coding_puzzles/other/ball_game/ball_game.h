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

//TEST(CLASSNAME, TestInteractive)
//{
//    Game g;
//    g.init();
//    int ret = g.mainLoop();
//    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
//}

TEST(CLASSNAME, Test001)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place001_1left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test011)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place011_5left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test043)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place043_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test044)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place044_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test045)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place045_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test046)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place046_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test047)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place047_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test048)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place048_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test049)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place049_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

TEST(CLASSNAME, Test050)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place050_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test051)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place051_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test052)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place052_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test053)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place053_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test054)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place054_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test055)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place055_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}
TEST(CLASSNAME, Test056)
{
    Game g;
    g.init();
    int ret = g.mainLoop("/home/gert/private/workspace/coding_puzzles/coding_puzzles/other/ball_game/place056_10left.txt");
    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
    ASSERT_EQ(ret, 0);
}

#undef CLASSNAME
