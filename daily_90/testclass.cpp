#include "testclass.h"

#include "gtest/gtest.h"

TestClass::TestClass()
{

}

int TestClass::getA()
{
    return m_a;
}

int TestClass::getB()
{
    return m_b;
}

void TestClass::printValues()
{
    std::cout << "a = " << m_a << " and b=" << m_b << std::endl;
}

TEST(TestClass, Test1)
{
    std::cout << "Test1 started..." << std::endl;
    TestClass tc1;
    tc1.printValues();

    ASSERT_EQ(1, tc1.getA());
    ASSERT_EQ(2, tc1.getB());
}
