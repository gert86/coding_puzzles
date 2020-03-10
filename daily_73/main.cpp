#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

// common includes
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "doublylinkedlist.h"
// #include "doublylinkedlistderived.h"   // TODO
#include "binarytree.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{

    // Test the singly-linked list
    cout << "----- SINGLY-LINKED LIST -----" << endl;
    LinkedList list;    

    list.pushFirst(3);
    list.pushFirst(1);
    list.pushLast(4);
    list.pushNext(2, list.getFirst());
    list.pushLast(5);
    list.pushLast(6);
    list.printList();  // 1, 2, 3, 4, 5, 6

    // Reverse the list
    LinkedListNode *prev_node = nullptr;
    LinkedListNode *node = list.getFirst();
    while(node != nullptr)
    {
        LinkedListNode *original_next = node->getNext();
        node->setNext(prev_node);

        prev_node = node;
        node = original_next;
    }
    list.m_first = prev_node;   // is normally private


    list.printList();    // 6, 5, 4, 3, 2, 1





    return 0;
}
