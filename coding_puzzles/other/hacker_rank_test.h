#pragma once

#define CLASSNAME Hacker_Rank_Test

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Consider an undirected graph where each edge weighs 6 units. Each of the nodes is labeled consecutively
// from 1 to n.
// You will be given a number of queries. For each query, you will be given a list of edges describing an
// undirected graph. After you create a representation of the graph, you must determine and report the
// shortest distance to each of the other nodes from a given starting position using the breadth-first search
// algorithm (BFS). Return an array of distances from the start node in node number order. If a node is
// unreachable, return -1 for that node.
//
// Example:
// The following graph is based on the listed inputs:
//        1 (Start)     5
//      /   \
//     2     3
//           |
//           4
//
// n = 5 // number of nodes
// m = 3 // number of edges
// edges = [1,2], [1,3], [3,4]
// s = 1 // starting node
//
// All distances are from the start node 1.
// Outputs are calculated for distances to nodes 2 through 5: [6, 6, 12, -1].
// Each edge is units, and the unreachable node has the required return distance of -1.

class SeGraphNode
{
  private:
    int m_data;
    bool m_visited;
    //std::vector<MyGraphNode*> m_children;  // this only works good for directed graphs
public:
    SeGraphNode(int data) : m_data(data), m_visited(false) {}

    virtual ~SeGraphNode() {}

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
};

class SeGraphNodeCollection
{
  private:
    std::map<int, SeGraphNode*> m_node_map;

  public:
    SeGraphNodeCollection(int numNodes)
    {
      for (int i=1; i<=numNodes; i++)
        m_node_map[i] = new SeGraphNode(i);
    }

    SeGraphNode* getNode(int i)
    {
      return m_node_map[i];
    }

    bool isNodeVisited(int i)
    {
      return m_node_map[i]->isVisited();
    }

    void setNodeVisited(int i)
    {
        m_node_map[i]->setVisited(true);
    }
};

class SeGraph
{
  private:
    SeGraphNodeCollection m_nodes;
    std::vector<std::vector<bool>> m_adjacency;


  public:
    SeGraph(int numNodes) : m_nodes(numNodes)
    {
      auto inner = std::vector<bool>(numNodes, false);
      m_adjacency = std::vector<std::vector<bool>> (numNodes, inner);
    }

    void addAdjacencies(const std::vector<vector<int>> &edges)
    {
      for (size_t i=0; i<edges.size(); i++) {
        int idx0 = edges[i][0] - 1;  // internally we work zero-based
        int idx1 = edges[i][1] - 1;

        m_adjacency[idx0][idx1] = true;
        m_adjacency[idx1][idx0] = true;
      }
    }

    std::vector<int> getAdjacentNodes(int num)
    {
      std::vector<int> result;
      for(size_t i=0; i<m_adjacency.size(); i++) {
        if (m_adjacency[i][num-1]) {
          result.push_back(i + 1);
        }
      }
      return result;
    }

    SeGraphNodeCollection& nodes()
    {
      return m_nodes;
    }
};

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    vector<int> bfs(int n, int m, vector<vector<int>> edges, int s)
    {
      // n = number of nodes
      // m = number of edges
      // edges
      // s = starting node

      std::vector<int> distances(n, -1);

      SeGraph g(n);
      g.addAdjacencies(edges);

      // direct neighbours
      int distance = 6;
      g.nodes().setNodeVisited(s);
      auto directNeighbours = g.getAdjacentNodes(s);
      std::set<int> nextAdjacentNodes;
      for (const auto& adj : directNeighbours) {
        if (!g.nodes().isNodeVisited(adj)) {
          nextAdjacentNodes.insert(adj);
          distances[adj-1] = distance;
          //std::cout << "Direct neighbour " << adj << " has distance " << distance << std::endl;
          g.nodes().setNodeVisited(adj);
        }
      }

      // neighbours of neighbours until there are no more
      while(!nextAdjacentNodes.empty()) {
        distance += 6;
        //std::cout << "NEXT DIST: " << distance << std::endl;

        std::set<int> next;
        for (const auto &curr : nextAdjacentNodes)
        {
          auto neighbours = g.getAdjacentNodes(curr);
          for (const auto& adj : neighbours) {
            if (!g.nodes().isNodeVisited(adj)) {
              next.insert(adj);
              distances[adj-1] = distance;
              //std::cout << "neighbour " << adj << " of " << curr <<  " has distance " << distance << std::endl;
              g.nodes().setNodeVisited(adj);
            }
          }
        }
        nextAdjacentNodes = next;
      }

      distances.erase(distances.begin() + s - 1);
      return distances;
    }

};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    int numNodes = 5;
    int numEdges = 3;
    std::vector<std::vector<int>> edges;
    edges.push_back({1,2});
    edges.push_back({1,3});
    edges.push_back({3,4});
    int startNode = 1;

    auto distances = instance.bfs(numNodes, numEdges, edges, startNode);
    std::cout << "Distances are: " << std::endl;
    for (const auto& d : distances)
      std::cout << d << " ";
    std:cout << std::endl;
    std::vector<int> expectedResult{6, 6, 12, -1};
    ASSERT_EQ(distances, expectedResult);
}

#undef CLASSNAME
