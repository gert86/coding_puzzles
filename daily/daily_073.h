#pragma once

#define CLASSNAME Daily_073

#include "base_header.h"

#include "utils/linkedlist.h"


using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given the head of a singly linked list, reverse it in-place.


// Example:
// 0 -> next=1    (head)
// 1 -> next=2
// 2 -> next=3
// 3 -> next=nullptr
//
// 0 -> next = nullptr
// 1 -> next = 0
// 2 -> next = 1
// 3 -> next = 2   (new head -> needs to be set in Linked list)

// Strategy:
// while(currNode != nullptr)
//  auto nextNode = currNode->getNext();  // can be nullptr
//  currNode->setNext(prevNode);          // prevNode initially nullptr
//  prevNode = currNode
//  currNode = nextNode

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    template <class T>
    void reverseLinkedList(LinkedList<T> &list)
    {
      auto currNode = list.getFirst();
      LinkedListNode<T>* prevNode = nullptr;

      while(currNode != nullptr) {
        auto nextNode = currNode->getNext();
        currNode->setNext(prevNode);

        prevNode = currNode;
        currNode = nextNode;
      }
      list.m_first = prevNode;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // Create a linked list (and test its implementation)
    LinkedList<int> list;
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
