//Suppose an arithmetic expression is given as a binary tree. Each leaf is an integer and each internal node is one of '+', '−', '∗', or '/'.

//Given the root to such a tree, write a function to evaluate it.

//For example, given the following tree:

//    *
//   / \
//  +    +
// / \  / \
//3  2  4  5

//You should return 45, as it is (3 + 2) * (4 + 5).



// Questions to ask:
//
// Can we expect that the given tree is a perfect tree with 2^N - 1 leafs?


// Note: Solution works, but is a mess due to conversions between "QString", "std::string" and "const char *" formats.




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
    // Test the binary tree
    auto *left_sub = new BinaryTreeNode<string>("+");
    left_sub->setLeft( new BinaryTreeNode<string>("3") );
    left_sub->setRight( new BinaryTreeNode<string>("2") );

    auto *right_sub = new BinaryTreeNode<string>("+");
    right_sub->setLeft( new BinaryTreeNode<string>("4") );
    right_sub->setRight( new BinaryTreeNode<string>("5") );

    auto *root = new BinaryTreeNode<string>("*");
    root->setLeft(left_sub);
    root->setRight(right_sub);

    BinaryTree<string> tree;
    tree.setRoot(root);

    Stack<string> parsed_values;
    cout << "The post-order result is: " << tree.calculateResultPostOrder(parsed_values) << endl;

    return 0;
}
