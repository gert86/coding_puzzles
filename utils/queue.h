#pragma once

#include <iostream>

using namespace std;

template <class T=int>
class QueueNode
{
private:
    T         m_data;
    QueueNode *m_next;

public:
    QueueNode(T val) : m_data(val), m_next(nullptr) {}

    virtual ~QueueNode() {}

    T getData() const
    {
        return m_data;
    }

    void setData(T val)
    {
        m_data = val;
    }

    QueueNode* getNext() const
    {
        return m_next;
    }

    void setNext(QueueNode *next)
    {
        m_next = next;
    }

    bool hasNext() const
    {
        return (m_next!=nullptr);
    }
};

template <class T=int>
class Queue
{
private:
    QueueNode<T> *m_first;
    QueueNode<T> *m_last;
public:
    Queue() : m_first(nullptr), m_last(nullptr)  {}

    void push(T val)
    {
        // create new node and append it to last
        auto *node = new QueueNode<T>(val);

        if (m_last == nullptr)
        {
            // queue is yet empty, init m_first and m_last
            m_first = m_last = node;
        }
        else
        {
            // append to last
            m_last->setNext(node);
            m_last = node;
        }
    }

    T pop()
    {
        if (m_first==nullptr)
        {
            cerr << "Cannot pop() on empty queue. Exit!" << endl;
            exit(-1);
        }

        // remove first and set first to the next node
        auto *node = m_first;
        m_first = node->getNext();  // new first (can be nullptr)

        // if now empty, also set m_last to nullptr
        if (m_first==nullptr)
        {
            m_last = nullptr;
        }

        T val = node->getData();
        delete node;
        return val;
    }

    T peek() const
    {
        if (m_first==nullptr)
        {
            cerr << "Cannot peek() on empty queue. Exit!" << endl;
            exit(-1);
        }

        return m_first->getData();
    }

    bool isEmpty() const
    {
        return (m_first==nullptr);
    }

};
