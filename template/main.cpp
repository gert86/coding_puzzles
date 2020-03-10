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
    // Test the stack
    cout << "----- STACK -----" << endl;
    Stack stack;
    for (int i=0; i<10; i++)
        stack.push(i);

    while(!stack.isEmpty())
    {
        cout << "stack.peek() is " << stack.peek() << endl;
        cout << "stack.pop()  is " << stack.pop() << endl;
    }
    cout << "Stack is now empty --> stack.isEmpty() returns " << stack.isEmpty() << endl;



    // Test the queue
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



    // Test the singly-linked list
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

    // Test the doubly-linked list
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

    // Test the binary tree
    cout << "----- BINARY TREE -----" << endl;
    auto *left_sub = new BinaryTreeNode(4);
    left_sub->setLeft( new BinaryTreeNode(2) );
    left_sub->setRight( new BinaryTreeNode(6) );

    auto *right_sub = new BinaryTreeNode(10);
    right_sub->setRight( new BinaryTreeNode(20) );

    auto *root = new BinaryTreeNode(8);
    root->setLeft(left_sub);
    root->setRight(right_sub);

    BinaryTree tree;
    cout << "The in-order traversal of an empty tree is: "; tree.printTreeInOrder(); cout << endl;

    tree.setRoot(root);
    cout << "The in-order traversal is: "; tree.printTreeInOrder(); cout << endl;
    cout << "The pre-order traversal is: "; tree.printTreePreOrder(); cout << endl;
    cout << "The post-order traversal is: "; tree.printTreePostOrder(); cout << endl;
    cout << "The level-order traversal is: "; tree.printTreeLevelOrder(); cout << endl;

    // Test the graph
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

    return 0;
}
