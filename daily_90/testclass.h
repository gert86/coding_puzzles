#ifndef TESTCLASS_H
#define TESTCLASS_H


class TestClass
{
public:
    TestClass();

    int getA();
    int getB();
    void printValues();

private:
    int m_a{1};
    int m_b{2};
};



#endif // TESTCLASS_H
