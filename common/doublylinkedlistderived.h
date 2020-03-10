#ifndef DOUBLYLINKEDLISTDERIVED_H
#define DOUBLYLINKEDLISTDERIVED_H

#include <iostream>

#include "linkedlist.h"

using namespace std;

class DerivedDoublyLinkedListNode : public LinkedListNode
{
private:
    LinkedListNode *m_prev;

public:
    DerivedDoublyLinkedListNode(int val) : LinkedListNode(val), m_prev(nullptr)
    {
    }

    virtual ~DerivedDoublyLinkedListNode()  {}

    LinkedListNode* getPrev() const
    {
        return m_prev;
    }

    void setPrev(LinkedListNode *prev)
    {
        m_prev = prev;
    }

    bool hasPrev() const
    {
        return (m_prev!=nullptr);
    }

    virtual void appendLast(int val) override
    {
        // TODO: Also set prev pointer to old last element
    }

    virtual void appendNext(int val) override
    {
        // Also set prev pointer of new node to this
    }

    // new counterpart method
    void prependFirst(int val)
    {
    }

    // new counterpart method
    void prependBefore(int val)
    {
    }
};

class DerivedDoublyLinkedList : public LinkedList
{
private:
    LinkedListNode *m_last;  // TODO: Base or Derived?

public:
    DerivedDoublyLinkedList() : LinkedList(), m_last(nullptr)
    {
    }

    virtual ~DerivedDoublyLinkedList()  {}

    // getFirst() remains unmodified

    // new counterpart method
    LinkedListNode* getLast() const   // TODO: Base or Derived?
    {
        return m_last;
    }


    virtual void removeFirst() override
    {
        // TODO: Also invalidate prev pointer of new first element
    }

    // new counterpart method
    void removeLast()
    {
        // TODO: Invalidate next pointer of new last element (if exists)
    }



    // pushLast() - Can remain unmodified if DoublyLinkedListNode::appendLast() is modified accordingly

    virtual void pushFirst(int val) override
    {
        // TODO: Also add prev pointer of now second element        
    }



    // pushNext() - Can remain unmodified if DoublyLinkedListNode::appendNext() is modified accordingly

    // new counterpart method
    void pushPrev(int val, LinkedListNode *successor)
    {
        // TODO
    }
};

#endif // DOUBLYLINKEDLISTDERIVED_H
