#pragma once

#include <iostream>

using namespace std;

template <class T>
class DoublyLinkedListNode
{
private:
    T                   m_data;
    DoublyLinkedListNode *m_next;
    DoublyLinkedListNode *m_prev;

public:
    DoublyLinkedListNode(T val) : m_data(val), m_next(nullptr), m_prev(nullptr)
    {
    }

    virtual ~DoublyLinkedListNode()  {}

    T getData() const
    {
        return m_data;
    }

    void setData(T val)
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

template <class T>
class DoublyLinkedList
{
private:
    DoublyLinkedListNode<T> *m_first;
    DoublyLinkedListNode<T> *m_last;

public:
    DoublyLinkedList() : m_first(nullptr), m_last(nullptr)
    {
    }

    virtual ~DoublyLinkedList()  {}

    DoublyLinkedListNode<T>* getFirst() const
    {
        return m_first;
    }

    // only for doubly-linked list
    DoublyLinkedListNode<T>* getLast() const
    {
        return m_last;
    }


    void removeFirst()
    {        
        DoublyLinkedListNode<T>* node = m_first;
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
        DoublyLinkedListNode<T>* node = m_last;
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

    void pushLast(T val)
    {
        auto *node = new DoublyLinkedListNode<T>(val);
        node->setPrev(m_last);
        if (m_last)
            m_last->setNext(node);
        else
            m_first = node;   // this is the only node

        m_last = node;
    }


    void pushFirst(T val)
    {
        auto *node = new DoublyLinkedListNode<T>(val);
        node->setNext(m_first);
        if (m_first)
            m_first->setPrev(node);
        else
            m_last = node;   // this is the only node

        m_first = node;
    }



    // In contrast to singly-linked list, we must update m_last now
    void pushNext(T val, DoublyLinkedListNode<T> *predecessor)
    {
        if (predecessor==nullptr)
        {
            cerr << "Cannot pushNext if given predecessor is nullptr. Exit!" << endl;
            exit(-1);
        }

        auto *node = new DoublyLinkedListNode<T>(val);
        node->setNext(predecessor->getNext());   // adopt successor from predecessor
        if (node->hasNext())
            node->getNext()->setPrev(node);      // successor (if exists) points back to this node

        predecessor->setNext(node);              // append to predecessor
        node->setPrev(predecessor);              // point back

        if (predecessor == m_last)
            m_last = node;                       // this is the new last node
    }

    // only for doubly-linked list
    void pushPrev(T val, DoublyLinkedListNode<T> *successor)
    {
        if (successor==nullptr)
        {
            cerr << "Cannot pushPrev if given successor is nullptr. Exit!" << endl;
            exit(-1);
        }

        auto *node = new DoublyLinkedListNode<T>(val);
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
