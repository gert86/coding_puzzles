#pragma once

#include <iostream>
#include <queue>

using namespace std;

template <class T=int>    // note: omitting type and using default type does not work on all compilers!
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
};
