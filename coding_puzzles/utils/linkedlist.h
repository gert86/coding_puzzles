#pragma once

#include <iostream>

using namespace std;

class LinkedListNode
{
private:
    int             m_data;
    LinkedListNode *m_next;

public:
    LinkedListNode(int val) : m_data(val), m_next(nullptr)
    {
    }

    virtual ~LinkedListNode()  {}

    int getData() const
    {
        return m_data;
    }

    void setData(int val)
    {
        m_data = val;
    }

    LinkedListNode* getNext() const
    {
        return m_next;
    }

    void setNext(LinkedListNode *next)
    {
        m_next = next;
    }

    bool hasNext() const
    {
        return (m_next!=nullptr);
    }

    virtual void appendLast(int val)
    {
        auto *node = new LinkedListNode(val);

        // find last node (without successor)
        auto *current = this;
        while(current->hasNext())
        {
            current = current->getNext();
        }
        current->setNext(node);   // append to last node        
    }

    virtual void appendNext(int val)
    {
        auto *node = new LinkedListNode(val);

        node->setNext(this->getNext());  // adopt successor from this
        this->setNext(node);             // append to this        
    }
};


class LinkedList
{
    friend class Daily_073;

private:
    LinkedListNode *m_first;

public:   

    LinkedList() : m_first(nullptr)
    {
    }

    virtual ~LinkedList()  {}

    LinkedListNode* getFirst() const
    {
        return m_first;
    }

    virtual void removeFirst()
    {
        LinkedListNode* node = m_first;
        if (node != nullptr)
        {
            m_first = node->getNext();
            delete node;
        }
    }

    void pushLast(int val)
    {
        if (m_first==nullptr)
        {
            // Insert manually since m_first is not yet initialized
            m_first = new LinkedListNode(val);
        }
        else
        {
            m_first->appendLast(val);  // takes O(N)
        }
    }

    virtual void pushFirst(int val)
    {
        auto *node = new LinkedListNode(val);
        node->setNext(m_first);
        m_first = node;
    }

    void pushNext(int val, LinkedListNode *predecessor)
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
