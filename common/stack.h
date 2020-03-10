#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <class T=int>
class StackNode
{
private:
    T        m_data;
    StackNode *m_next;

public:
    StackNode(T val) : m_data(val), m_next(nullptr)  {}

    virtual ~StackNode() {}

    T getData() const
    {
        return m_data;
    }

    void setData(T val)
    {
        m_data = val;
    }

    StackNode* getNext() const
    {
        return m_next;
    }

    void setNext(StackNode *next)
    {
        m_next = next;
    }

    bool hasNext() const
    {
        return (m_next!=nullptr);
    }
};

template <class T=int>
class Stack
{
private:
    StackNode<T> *m_top;

public:
    Stack() : m_top(nullptr)  {}

    void push(T val)
    {
        // create new node and prepend it to top
        auto *node = new StackNode<T>(val);
        node->setNext(m_top);
        m_top = node;
    }

    T pop()
    {
        if (m_top==nullptr)
        {
            cerr << "Cannot pop() on empty stack. Exit!" << endl;
            exit(-1);
        }

        // remove top and set top to the next node
        auto *node = m_top;
        m_top = m_top->getNext();  // new top (can be nullptr)

        T val = node->getData();
        delete node;
        return val;
    }

    T peek() const
    {
        if (m_top==nullptr)
        {
            cerr << "Cannot peek() on empty stack. Exit!" << endl;
            exit(-1);
        }

        return m_top->getData();
    }

    bool isEmpty() const
    {
        return (m_top==nullptr);
    }
};

#endif // STACK_H
