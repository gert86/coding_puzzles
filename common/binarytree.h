#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>

// For daily 50
#include "stack.h"
#include <QString>

#include "gtest/gtest.h"

using namespace std;

template <class T=int>
class BinaryTreeNode
{
private:
    T m_data;
    BinaryTreeNode *m_left;
    BinaryTreeNode *m_right;

public:
    BinaryTreeNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr)  {}

    virtual ~BinaryTreeNode()  {}

    T getData() const
    {
        return m_data;
    }

    void setData(T val)
    {
        m_data = val;
    }

    BinaryTreeNode* getLeft() const
    {
        return m_left;
    }

    void setLeft(BinaryTreeNode *left)
    {
        m_left = left;
    }

    bool hasLeft() const
    {
        return (m_left!=nullptr);
    }

    BinaryTreeNode* getRight() const
    {
        return m_right;
    }

    void setRight(BinaryTreeNode *right)
    {
        m_right = right;
    }

    bool hasRight() const
    {
        return (m_right!=nullptr);
    }

    void print() const
    {
        cout << m_data << " ";
    }

    // current, left, right
    void printPreOrder() const
    {
        print();
        if (m_left)   m_left->printPreOrder();
        if (m_right)  m_right->printPreOrder();
    }

    // left, current, right
    void printInOrder() const
    {
        if (m_left)   m_left->printInOrder();
        print();
        if (m_right)  m_right->printInOrder();
    }

    // left, right, current
    void printPostOrder() const
    {
        if (m_left)   m_left->printPostOrder();
        if (m_right)  m_right->printPostOrder();
        print();
    }

    // level after level
    void printLevelOrder() const
    {
        std::queue<const BinaryTreeNode*> queue;
        queue.push(this);

        while (!queue.empty())
        {
            const BinaryTreeNode* node = queue.front();
            queue.pop();

            // Attention: Do not use m_left, m_right here because this method is NOT recursive!
            node->print();
            if (node->hasLeft())   queue.push(node->getLeft());
            if (node->hasRight())  queue.push(node->getRight());
        }
    }


    // For Daily 50
    void calculateResultPostOrder(Stack<string> &parsed_values) const
    {
        if (m_left)   m_left->calculateResultPostOrder(parsed_values);
        if (m_right)  m_right->calculateResultPostOrder(parsed_values);

        // Do the magic
        bool ok;
        int num = QString::fromStdString(m_data).toInt(&ok, 10);

        if (ok)
        {
            // Parsed a numeric, add to stack
            parsed_values.push(m_data);
        }
        else
        {
           // parsed operator, apply it to last two elements on stack
           bool ok_prev_1;
           QString str_prev_1 = QString::fromStdString(parsed_values.pop());
           int num_prev_1 = str_prev_1.toInt(&ok_prev_1);
           if (!ok_prev_1)
           {
               cerr << "Error. Expected first to be numeric but got " << str_prev_1.toStdString() << endl;
               exit (-1);
           }

           bool ok_prev_2;
           QString str_prev_2 = QString::fromStdString(parsed_values.pop());
           int num_prev_2 = str_prev_2.toInt(&ok_prev_2);
            if (!ok_prev_2)
            {
                cerr << "Error. Expected second to be numeric but got " << str_prev_2.toStdString() << endl;
                exit (-1);
            }

            if (strcmp(m_data.c_str(), "+")==0)
                parsed_values.push( QString::number(num_prev_2 + num_prev_1).toStdString() );
            else if (strcmp(m_data.c_str(), "-")==0)
                parsed_values.push( QString::number(num_prev_2 - num_prev_1).toStdString()  );
            else if (strcmp(m_data.c_str(), "*")==0)
                parsed_values.push( QString::number(num_prev_2 * num_prev_1).toStdString()  );
            else if (strcmp(m_data.c_str(), "/")==0)
                parsed_values.push( QString::number(num_prev_2 / num_prev_1).toStdString()  );
            else
            {
                cerr << "Error. Expected operator but got " << m_data << endl;
                exit (-1);
            }
        }
    }
};

template <class T=int>
class BinaryTree
{
private:
    BinaryTreeNode<T> *m_root;

public:
    BinaryTree() : m_root(nullptr) {}

    virtual ~BinaryTree()  {}

    BinaryTreeNode<T>* getRoot() const
    {
        return m_root;
    }

    void setRoot(BinaryTreeNode<T> *root)
    {
        m_root = root;
    }

    bool hasRoot() const
    {
        return (m_root!=nullptr);
    }

    // convenience method to call on tree's root
    void printTreePreOrder()
    {
        if (m_root==nullptr)
        {
            cout << "<EMPTY TREE>" << endl;
            return;
        }

        m_root->printPreOrder();
    }

    // convenience method to call on tree's root
    void printTreeInOrder()
    {
        if (m_root==nullptr)
        {
            cout << "<EMPTY TREE>";
            return;
        }

        m_root->printInOrder();
    }

    // convenience method to call on tree's root
    void printTreePostOrder()
    {
        if (m_root==nullptr)
        {
            cout << "<EMPTY TREE>" << endl;
            return;
        }

        m_root->printPostOrder();
    }

    // convenience method to call on tree's root
    void printTreeLevelOrder()
    {
        if (m_root==nullptr)
        {
            cout << "<EMPTY TREE>" << endl;
            return;
        }

        m_root->printLevelOrder();
    }


    // For Daily 50
    int calculateResultPostOrder(Stack<string> &parsed_values)
    {
        if (m_root==nullptr)
        {
            return -1;
        }

        m_root->calculateResultPostOrder(parsed_values);


        // Fetch the result and return it
        bool ok_result;
        QString str_result = QString::fromStdString(parsed_values.pop());
        int num_result = str_result.toInt(&ok_result);

        if (!ok_result)
        {
            cerr << "Error. Result should be a number but is " << str_result.toStdString() << endl;
            return -1;
        }

        if (!parsed_values.isEmpty())
        {
            cerr << "Error. Stack should eventually be empty but is not. " << endl;
            return -1;
        }

        return num_result;
    }


};


TEST(LibBinaryTree, Test1)
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

    Stack<string> parsed_values;
    cout << "The post-order result is: " << tree.calculateResultPostOrder(parsed_values) << endl;
}

#endif // BINARYTREE_H
