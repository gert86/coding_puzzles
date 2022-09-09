#pragma once

#include <iostream>

using namespace std;

template <class T>
class LinkedListNode
{
private:
    T                 m_data;
    LinkedListNode<T> *m_next;  // <T> is optional within the class

public:
    LinkedListNode<T>(T val) : m_data(val), m_next(nullptr)  // <T> is optional within the class
    {
    }

    virtual ~LinkedListNode<T>()  {}  // <T> is optional within the class

    T getData() const
    {
        return m_data;
    }

    void setData(T val)
    {
        m_data = val;
    }

    LinkedListNode<T>* getNext() const  // <T> is optional within the class
    {
        return m_next;
    }

    void setNext(LinkedListNode<T> *next)  // <T> is optional within the class
    {
        m_next = next;
    }

    bool hasNext() const
    {
        return (m_next!=nullptr);
    }

    virtual void appendLast(T val)
    {
        auto *node = new LinkedListNode<T>(val);  // <T> is optional within the class

        // find last node (without successor)
        auto *current = this;
        while(current->hasNext())
        {
            current = current->getNext();
        }
        current->setNext(node);   // append to last node        
    }

    virtual void appendNext(T val)
    {
        auto *node = new LinkedListNode<T>(val);  // <T> is optional within the class

        node->setNext(this->getNext());  // adopt successor from this
        this->setNext(node);             // append to this        
    }
};

template<class T>
class LinkedList
{
    friend class Daily_073;

private:
    LinkedListNode<T> *m_first;

public:   

    LinkedList() : m_first(nullptr)
    {
    }

    virtual ~LinkedList()  {}

    LinkedListNode<T>* getFirst() const
    {
        return m_first;
    }

    virtual void removeFirst()
    {
        LinkedListNode<T>* node = m_first;
        if (node != nullptr)
        {
            m_first = node->getNext();
            delete node;
        }
    }

    void pushLast(T val)
    {
        if (m_first==nullptr)
        {
            // Insert manually since m_first is not yet initialized
            m_first = new LinkedListNode<T>(val);
        }
        else
        {
            m_first->appendLast(val);  // takes O(N)
        }
    }

    virtual void pushFirst(T val)
    {
        auto *node = new LinkedListNode<T>(val);
        node->setNext(m_first);
        m_first = node;
    }

    void pushNext(T val, LinkedListNode<T> *predecessor)
    {
        if (predecessor==nullptr)
        {
            cerr << "Cannot pushNext if given predecessor is nullptr. Exit!" << endl;
            exit(-1);
        }

        predecessor->appendNext(val);
    }

    string toString() const
    {
        if (m_first==nullptr)
            return "<EMPTY>";

        stringstream ss;

        auto *current_node = m_first;
        while (current_node->hasNext()) {
            ss << current_node->getData() << " ";
            current_node = current_node->getNext();
        }
        ss << current_node->getData();

        return ss.str();
    }

    void printList() const
    {
        cout << this->toString() << endl;
    }
};
