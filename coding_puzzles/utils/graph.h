#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>

using namespace std;

class GraphNode
{
private:
    int m_data;
    bool m_visited;  // Node: In real applications, this information must be stored externally! Otherwise it must be reset after each traversal.
    std::vector<GraphNode*> m_children;
public:
    GraphNode(int data) : m_data(data), m_visited(false) {}

    virtual ~GraphNode() {}

    int getData() const
    {
        return m_data;
    }

    void setData(int val)
    {
        m_data = val;
    }

    bool isVisited() const
    {
        return m_visited;
    }

    void setVisited(bool val)
    {
        m_visited = val;
    }

    const std::vector<GraphNode*>& getChildren() const
    {
        return m_children;
    }

    void setChildren(std::vector<GraphNode*> children)
    {
        m_children = children;
    }

    void print() const
    {
        cout << m_data << " ";
    }

    void printDepthFirstSearch()
    {
        print();
        setVisited(true);

        for(auto it=m_children.begin(); it != m_children.end(); ++it)
        {
            if( !(*it)->isVisited())
            {
                (*it)->printDepthFirstSearch();
            }
        }
    }

    void printBreadthFirstSearch()
    {
        std::queue<GraphNode*> queue;

        // Important: Set visited before adding to queue and NOT after popping from queue! Otherwise it might be added multiple times!!!
        this->setVisited(true);
        queue.push(this);

        while( !queue.empty() )
        {
            GraphNode *node = queue.front();
            queue.pop();

            node->print();

            const std::vector<GraphNode*>& children = node->getChildren();

            for(auto it=children.begin(); it != children.end(); ++it)
            {
                if( !(*it)->isVisited())
                {
                    (*it)->setVisited(true);
                    queue.push(*it);
                }
            }
        }
    }
};



class Graph
{
private:
    std::vector<GraphNode*> m_nodes;

public:
    Graph() {}

    virtual ~Graph() {}

    std::vector<GraphNode*> getNodes() const
    {
        return m_nodes;
    }

    void setNodes(std::vector<GraphNode*> nodes)
    {
        m_nodes = nodes;
    }
};

#endif // GRAPH_H
