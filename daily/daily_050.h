#pragma once

#define CLASSNAME Daily_050

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Suppose an arithmetic expression is given as a binary tree. Each leaf is an integer and each internal node is one of '+', '−', '∗', or '/'.
// Given the root to such a tree, write a function to evaluate it.
// For example, given the following tree:

//     *
//    / \
//   +    +
//  / \  / \
// 3  2  4  5

// You should return 45, as it is (3 + 2) * (4 + 5).

#include "utils/binarytree.h"
#include "utils/stack.h"


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Helper method
    int convertToStringOrExit(string str, string error_msg)
    {
        const string c_str(str);

        bool conversion_ok;
        int converted_num = QString::fromStdString(c_str).toInt(&conversion_ok);
        if (!conversion_ok)
        {
            cerr << error_msg << endl;
            exit (-1);
        }
        return converted_num;
    }

    // Creates and returns the tree from the task description
    BinaryTree<string> createTestTree()
    {
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
        return tree;
    }

    int calculateResultPostOrder(const BinaryTree<string> *tree)
    {
        if (!tree->hasRoot())
        {
            cerr << "Invalid tree (has no root). Returning -1." << endl;
            return -1;
        }

        // calculate result starting from the root
        Stack<string> parsed_value_stack;
        calculateResultPostOrderNode(tree->getRoot(), parsed_value_stack);

        // stack must contain the final result
        string result_str = parsed_value_stack.pop();
        assert(parsed_value_stack.isEmpty());

        // convert and return it
        int num_result = convertToStringOrExit(result_str, "Error. Result is not a number.");
        return num_result;
    }

    void calculateResultPostOrderNode(BinaryTreeNode<string> *tree_node, Stack<string> &stack)
    {
        // calls itself recursively until we are at the leaves
        if (tree_node->hasLeft())   calculateResultPostOrderNode(tree_node->getLeft(), stack);
        if (tree_node->hasRight())  calculateResultPostOrderNode(tree_node->getRight(), stack);

        // Here comes the magic...
        string data = tree_node->getData();
        bool digit_conversion_ok;
        int dummy = QString::fromStdString(data).toInt(&digit_conversion_ok, 10);

        if (digit_conversion_ok)
        {
            // parsed a numeric, add to stack
            stack.push(data);
        }
        else
        {
           // parsed an operator, apply it to last two elements from stack and push result again onto stack
           int num_prev_right = convertToStringOrExit(stack.pop(), "Failed to convert value #1 to digit. Exit.");
           int num_prev_left = convertToStringOrExit(stack.pop(), "Failed to convert value #2 to digit. Exit.");

            if (data.compare("+")==0)
                stack.push( QString::number(num_prev_left + num_prev_right).toStdString() );
            else if (data.compare("-")==0)
                stack.push( QString::number(num_prev_left - num_prev_right).toStdString()  );
            else if (data.compare("*")==0)
                stack.push( QString::number(num_prev_left * num_prev_right).toStdString()  );
            else if (data.compare("/")==0)
                stack.push( QString::number(num_prev_left / num_prev_right).toStdString()  );
            else
            {
                cerr << "Error. Expected operator but got " << data << endl;
                exit (-1);
            }
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    BinaryTree<string> tree = instance.createTestTree();
    int result = instance.calculateResultPostOrder(&tree);
    cout << "The result is: " << result << endl << endl;
    ASSERT_EQ(45, result);
}

#undef CLASSNAME
