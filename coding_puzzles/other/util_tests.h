#pragma once

#define CLASSNAME Util_Tests

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// This program tests all utility classes in folder utils, such as BinaryTree, etc... .

#include "utils/binarytree.h"
#include "utils/doublylinkedlist.h"
#include "utils/graph.h"
#include "utils/linkedlist.h"
#include "utils/queue.h"
#include "utils/stack.h"


// TODO: Verify all things automatically with ASSERT_EQ. Requires enhancments in utils too.


TEST(CLASSNAME, BinaryTree)
{        
    cout << "----- BINARY TREE -----" << endl;
    auto *left_sub = new BinaryTreeNode<int>(4);
    left_sub->setLeft( new BinaryTreeNode<int>(2) );
    left_sub->setRight( new BinaryTreeNode<int>(6) );

    auto *right_sub = new BinaryTreeNode<int>(10);
    right_sub->setRight( new BinaryTreeNode<int>(20) );

    auto *root = new BinaryTreeNode<int>(8);
    root->setLeft(left_sub);
    root->setRight(right_sub);

    BinaryTree<int> tree;
    cout << "The in-order traversal of an empty tree is: "; tree.printTreeInOrder(); cout << endl;

    tree.setRoot(root);
    cout << "The in-order traversal is: "; tree.printTreeInOrder(); cout << endl;
    cout << "The pre-order traversal is: "; tree.printTreePreOrder(); cout << endl;
    cout << "The post-order traversal is: "; tree.printTreePostOrder(); cout << endl;
    cout << "The level-order traversal is: "; tree.printTreeLevelOrder(); cout << endl;
}


TEST(CLASSNAME, DoubleLinkedList)
{
    cout << "----- DOUBLY-LINKED LIST -----" << endl;
    DoublyLinkedList doubly_list;
    doubly_list.printList();    // <EMPTY>

    doubly_list.pushFirst(3);
    doubly_list.pushFirst(1);
    doubly_list.pushLast(4);
    doubly_list.pushLast(6);
    doubly_list.pushNext(2, doubly_list.getFirst());
    doubly_list.pushPrev(5, doubly_list.getLast());
    doubly_list.printList();  // 1, 2, 3, 4, 5, 6

    doubly_list.removeFirst();
    doubly_list.printList();    // 2, 3, 4, 5, 6

    doubly_list.removeLast();
    doubly_list.printList();    // 2, 3, 4, 5

    doubly_list.pushFirst(1);
    doubly_list.pushPrev(0, doubly_list.getFirst());
    doubly_list.pushLast(6);
    doubly_list.pushNext(7, doubly_list.getLast());
    doubly_list.printList();    // 0, 1, 2, 3, 4, 5, 6, 7

    doubly_list.removeFirst();
    doubly_list.removeFirst();
    doubly_list.removeFirst();
    doubly_list.removeFirst();
    doubly_list.printList();    // 4, 5, 6, 7

    doubly_list.removeLast();
    doubly_list.removeLast();
    doubly_list.removeLast();
    doubly_list.removeLast();
    doubly_list.printList();    // <EMPTY>


    doubly_list.removeLast();
    doubly_list.removeFirst();
    doubly_list.printList();    // <EMPTY>
}


TEST(CLASSNAME, Graph)
{
    cout << "----- GRAPH -----" << endl;
    Graph graph;

    // define nodes
    std::vector<GraphNode*> all_nodes;
    all_nodes.push_back(new GraphNode(0));
    all_nodes.push_back(new GraphNode(1));
    all_nodes.push_back(new GraphNode(2));
    all_nodes.push_back(new GraphNode(3));
    all_nodes.push_back(new GraphNode(4));
    all_nodes.push_back(new GraphNode(5));
    graph.setNodes(all_nodes);

    // define adjacencies
    std::vector<GraphNode*> node0_neighbours = {all_nodes[1], all_nodes[4], all_nodes[5]};
    all_nodes[0]->setChildren( node0_neighbours );

    std::vector<GraphNode*> node1_neighbours = {all_nodes[3], all_nodes[4]};
    all_nodes[1]->setChildren( node1_neighbours );

    std::vector<GraphNode*> node2_neighbours = {all_nodes[1]};
    all_nodes[2]->setChildren( node2_neighbours );

    std::vector<GraphNode*> node3_neighbours = {all_nodes[2], all_nodes[4]};
    all_nodes[3]->setChildren( node3_neighbours );

    std::vector<GraphNode*> node4_neighbours = {};
    all_nodes[4]->setChildren( node4_neighbours );

    std::vector<GraphNode*> node5_neighbours = {};
    all_nodes[5]->setChildren( node5_neighbours );


    // currently either the one or the other can be caled, because visited is stored within GraphNode
    //cout << "The depth-first search gives: ";   graph.getNodes().at(0)->printDepthFirstSearch(); cout << endl;
    cout << "The breadth-first search gives: "; graph.getNodes().at(0)->printBreadthFirstSearch(); cout << endl;
}


TEST(CLASSNAME, SinglyLinkedList)
{
    cout << "----- SINGLY-LINKED LIST -----" << endl;
    LinkedList list;
    list.printList();    // <EMPTY>

    list.pushFirst(3);
    list.pushFirst(1);
    list.pushLast(4);
    list.pushNext(2, list.getFirst());
    list.printList();  // 1, 2, 3, 4

    list.removeFirst();
    list.printList();    // 2, 3, 4

    list.removeFirst();
    list.printList();    // 3, 4

    list.removeFirst();
    list.removeFirst();
    list.removeFirst();
    list.removeFirst();
    list.printList();    // <EMPTY>
}


TEST(CLASSNAME, Queue)
{
    cout << "----- QUEUE -----" << endl;
    Queue queue;
    for (int i=0; i<10; i++)
        queue.push(i);

    while(!queue.isEmpty())
    {
        cout << "queue.peek() is " << queue.peek() << endl;
        cout << "queue.pop()  is " << queue.pop() << endl;
    }
    cout << "Queue is now empty --> queue.isEmpty() returns " << queue.isEmpty() << endl;
}


TEST(CLASSNAME, Stack)
{
    cout << "----- STACK -----" << endl;
    Stack<int> stack;
    for (int i=0; i<10; i++)
        stack.push(i);

    while(!stack.isEmpty())
    {
        cout << "stack.peek() is " << stack.peek() << endl;
        cout << "stack.pop()  is " << stack.pop() << endl;
    }
    cout << "Stack is now empty --> stack.isEmpty() returns " << stack.isEmpty() << endl;
}

#undef CLASSNAME
