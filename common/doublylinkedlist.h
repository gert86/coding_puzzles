#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>


using namespace std;

class DoublyLinkedListNode
{
private:
    int                   m_data;
    DoublyLinkedListNode *m_next;
    DoublyLinkedListNode *m_prev;

public:
    DoublyLinkedListNode(int val) : m_data(val), m_next(nullptr), m_prev(nullptr)
    {
    }

    virtual ~DoublyLinkedListNode()  {}

    int getData() const
    {
        return m_data;
    }

    void setData(int val)
    {
        m_data = val;
    }

    DoublyLinkedListNode* getNext() const
    {
        return m_next;
    }

    void setNext(DoublyLinkedListNode *next)
    {
        m_next = next;
    }

    bool hasNext() const
    {
        return (m_next!=nullptr);
    }

    DoublyLinkedListNode* getPrev() const
    {
        return m_prev;
    }

    void setPrev(DoublyLinkedListNode *prev)
    {
        m_prev = prev;
    }

    bool hasPrev() const
    {
        return (m_prev!=nullptr);
    }

    // Info: appendLast() and appendNext() were removed.
    // In contrast to singly-linked list these methods potentially modify m_last now, even if list is not empty.
    // Thus, the push methods from the DoublyLinkedList class take care of this now.

};

class DoublyLinkedList
{
private:
    DoublyLinkedListNode *m_first;
    DoublyLinkedListNode *m_last;

public:
    DoublyLinkedList() : m_first(nullptr), m_last(nullptr)
    {
    }

    virtual ~DoublyLinkedList()  {}

    DoublyLinkedListNode* getFirst() const
    {
        return m_first;
    }

    // only for doubly-linked list
    DoublyLinkedListNode* getLast() const
    {
        return m_last;
    }


    void removeFirst()
    {        
        DoublyLinkedListNode* node = m_first;
        if (node != nullptr)
        {
            m_first = node->getNext();
            if (m_first)
                m_first->setPrev(nullptr);
            else
                m_last = nullptr; // list is now empty

            delete node;
        }
    }

    // only for doubly-linked list
    void removeLast()
    {
        DoublyLinkedListNode* node = m_last;
        if (node != nullptr)
        {
            m_last = node->getPrev();
            if (m_last)
                m_last->setNext(nullptr);
            else
                m_first = nullptr; // list is now empty

            delete node;
        }
    }

    void pushLast(int val)
    {
        auto *node = new DoublyLinkedListNode(val);
        node->setPrev(m_last);
        if (m_last)
            m_last->setNext(node);
        else
            m_first = node;   // this is the only node

        m_last = node;
    }


    void pushFirst(int val)
    {
        auto *node = new DoublyLinkedListNode(val);
        node->setNext(m_first);
        if (m_first)
            m_first->setPrev(node);
        else
            m_last = node;   // this is the only node

        m_first = node;
    }



    // In contrast to singly-linked list, we must update m_last now
    void pushNext(int val, DoublyLinkedListNode *predecessor)
    {
        if (predecessor==nullptr)
        {
            cerr << "Cannot pushNext if given predecessor is nullptr. Exit!" << endl;
            exit(-1);
        }

        auto *node = new DoublyLinkedListNode(val);
        node->setNext(predecessor->getNext());   // adopt successor from predecessor
        if (node->hasNext())
            node->getNext()->setPrev(node);      // successor (if exists) points back to this node

        predecessor->setNext(node);              // append to predecessor
        node->setPrev(predecessor);              // point back

        if (predecessor == m_last)
            m_last = node;                       // this is the new last node
    }

    // only for doubly-linked list
    void pushPrev(int val, DoublyLinkedListNode *successor)
    {
        if (successor==nullptr)
        {
            cerr << "Cannot pushPrev if given successor is nullptr. Exit!" << endl;
            exit(-1);
        }

        auto *node = new DoublyLinkedListNode(val);
        node->setPrev(successor->getPrev());   // adopt predecessor from successor
        if (node->hasPrev())
            node->getPrev()->setNext(node);    // predecessor (if exists) points back to this node

        successor->setPrev(node);              // prepend to successor
        node->setNext(successor);              // point back

        if (successor == m_first)
            m_first = node;                    // this is the new first node
    }

    void printList() const
    {
        if (m_first==nullptr)
        {
            cout << "<EMPTY>" << endl;
            return;
        }

        auto *current_node = m_first;
        while (current_node->hasNext()) {
            cout << current_node->getData() << " ";
            current_node = current_node->getNext();
        }
        cout << current_node->getData() << endl;
    }
};

#endif // DOUBLYLINKEDLIST_H
