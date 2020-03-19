#pragma once

#define CLASSNAME Daily_073

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given the head of a singly linked list, reverse it in-place.

#include "utils/linkedlist.h"

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    void reverseLinkedList(LinkedList &list)
    {
        LinkedListNode *prev_node = nullptr;
        LinkedListNode *node = list.getFirst();
        while(node != nullptr)
        {
            LinkedListNode *original_next = node->getNext();
            node->setNext(prev_node);

            prev_node = node;
            node = original_next;
        }
        list.m_first = prev_node;   // is private, but declared as friend
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // Create a linked list (and test its implementation)
    LinkedList list;
    list.pushFirst(3);
    list.pushFirst(1);
    list.pushLast(4);
    list.pushNext(2, list.getFirst());
    list.pushLast(5);
    list.pushLast(6);
    cout << "Original list is: ";  list.printList();
    ASSERT_EQ("1 2 3 4 5 6", list.toString());

    // Reverse the list
    instance.reverseLinkedList(list);
    cout << "Reversed list is: ";  list.printList();
    ASSERT_EQ("6 5 4 3 2 1", list.toString());
}

#undef CLASSNAME
