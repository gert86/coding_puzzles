#pragma once

#define CLASSNAME Daily_052

#include "base_header.h"

#include <optional>

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Implement an LRU (Least Recently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:
//     set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item, then it should also remove the least recently used item.
//     get(key): gets the value at key. If no such key exists, return null.
//
// Each operation should run in O(1) time.

class CLASSNAME
{
public:
  CLASSNAME()
  {
    cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
  }

  // modified and simplified copy from doublylinkedlist.h
  class MyDoublyLinkedListNode
  {
  public:
    int                     m_data;
    MyDoublyLinkedListNode *m_next;
    MyDoublyLinkedListNode *m_prev;

    MyDoublyLinkedListNode(int val) : m_data(val), m_next(nullptr), m_prev(nullptr)
    {
    }
  };

  // modified and simplified copy from doublylinkedlist.h
  class MyDoublyLinkedList
  {
  public:
    MyDoublyLinkedListNode *m_first;
    MyDoublyLinkedListNode *m_last;

    MyDoublyLinkedList() : m_first(nullptr), m_last(nullptr)
    {
    }


    void popLast()
    {
      MyDoublyLinkedListNode* node = m_last;
      if (node != nullptr)
      {
        m_last = node->m_prev;
        if (m_last)
          m_last->m_next = nullptr;
        else
          m_first = nullptr; // list is now empty

        delete node;
      }
    }

    void pushFirst(MyDoublyLinkedListNode* node)
    {
      if (node == nullptr)
        return;

      node->m_prev = nullptr;
      node->m_next = m_first;

      if (m_first)
        m_first->m_prev = node;
      else
        m_last = node;   // this is the only node

      m_first = node;
    }

    void erase(MyDoublyLinkedListNode *node)
    {
      auto myPrev = node->m_prev;
      auto myNext = node->m_next;

      if (myPrev == nullptr)
        m_first = myNext;
      if (myNext == nullptr)
        m_last = myPrev;

      if (myPrev != nullptr)
        myPrev->m_next = myNext;
      if (myNext != nullptr)
        myNext->m_prev = myPrev;
    }
  };

  class LRUCache
  {
  private:
    size_t _cacheSize;
    std::unordered_map<int, std::pair<int, MyDoublyLinkedListNode*>> _map;
    mutable MyDoublyLinkedList _lruList;

  public:
    LRUCache(size_t n) :
      _cacheSize(n)
    {}

    bool isFull() const
    {
      return _map.size() == _cacheSize;
    }

    void removeLeastRecentlyUsed()
    {
      int leastUsedKey = _lruList.m_last->m_data;
      _lruList.popLast();
      _map.erase(leastUsedKey);
    }

    void setMostRecent(MyDoublyLinkedListNode* node, int key, bool nodeExisted) const
    {
      if (_lruList.m_first == node) {
        return;  // already most recent
      }

      if (nodeExisted)
        _lruList.erase(node);
      _lruList.pushFirst(node);
    }


    void set(int key, int value)
    {
      if (isFull()) {
        removeLeastRecentlyUsed();
      }

      bool nodeExisted;
      MyDoublyLinkedListNode* node;
      if (_map.find(key) != _map.end()) {
        nodeExisted = true;
        node = _map.at(key).second;
      }
      else {
        nodeExisted = false;
        node = new MyDoublyLinkedListNode(key);
      }

      setMostRecent(node, key, nodeExisted);
      _map[key] = std::make_pair(value, node);
    }

    std::optional<int> get(int key) const
    {
      if (_map.find(key) == _map.end())
        return nullopt;

      MyDoublyLinkedListNode* node = _map.at(key).second;
      setMostRecent(node, key, true);
      return _map.at(key).first;
    }

    void printMap() const
    {
      std::cout << std::endl << "MAP: " << std::endl;
      for (const auto &[key, val] : _map)
        std::cout << " map[" << key << "] = " << val.first << std::endl;
    }

    void printList() const
    {
      std::cout << "LIST: " << std::endl;
      auto *current_node = _lruList.m_first;
      while (current_node != nullptr) {
        std::cout << " " << current_node->m_data;
        current_node = current_node->m_next;
      }
      std::cout << std::endl;
    }
  };
};

TEST(CLASSNAME, Test1)
{
  CLASSNAME instance;

  CLASSNAME::LRUCache cache(3);
  ASSERT_EQ(cache.get(1), nullopt);

  cache.set(1, 100);
  ASSERT_EQ(*cache.get(1), 100);
  cache.printMap();
  cache.printList();


  cache.set(2, 200);
  ASSERT_EQ(*cache.get(2), 200);
  cache.printMap();
  cache.printList();


  cache.set(2, 201);
  ASSERT_EQ(*cache.get(2), 201);
  cache.printMap();
  cache.printList();


  cache.set(3, 300);
  ASSERT_EQ(*cache.get(3), 300);
  cache.printMap();
  cache.printList();


  cache.set(4, 400);
  ASSERT_EQ(*cache.get(4), 400);
  cache.printMap();
  cache.printList();

  ASSERT_EQ(cache.get(1), nullopt);   // 1 was the least recently used and got dropped
  cache.printMap();
  cache.printList();

  ASSERT_EQ(*cache.get(3), 300);
  ASSERT_EQ(*cache.get(2), 201);
  ASSERT_EQ(*cache.get(4), 400);
  cache.printMap();
  cache.printList();

  cache.set(5, 500);
  ASSERT_EQ(*cache.get(5), 500);
  cache.printMap();
  cache.printList();

  ASSERT_EQ(cache.get(3), nullopt);   // 3 was the least recently used and got dropped
  ASSERT_EQ(*cache.get(2), 201);
  ASSERT_EQ(*cache.get(4), 400);
  ASSERT_EQ(*cache.get(5), 500);

}


TEST(CLASSNAME, Test2)
{
  CLASSNAME instance;
  CLASSNAME::LRUCache cache(3);

  cache.set(1001,    0);
  cache.set(1001,    1);
  cache.set(1001,    2);
  cache.set(1002,   11);
  cache.set(1003,  101);

  ASSERT_EQ(2,       *cache.get(1001));
  ASSERT_EQ(11,      *cache.get(1002));
  ASSERT_EQ(101,     *cache.get(1003));
  ASSERT_EQ(nullopt,  cache.get(1004));
  ASSERT_EQ(nullopt,  cache.get(1005));
  cache.printMap();
  cache.printList();
  cout << "------------------------------------------------------" << endl;


  cache.set(1001,     3);
  cache.set(1002,      12);
  cache.set(1003,  102);

  ASSERT_EQ(3,       *cache.get(1001));
  cache.printMap();
  cache.printList();
  cout << "------------------------------------------------------" << endl;


  cache.set(1004,     1000);  // 1002 falls out

  ASSERT_EQ(1000,     *cache.get(1004));
  ASSERT_EQ(3,        *cache.get(1001));
  ASSERT_EQ(nullopt,   cache.get(1002));
  ASSERT_EQ(102,      *cache.get(1003));
  cache.printMap();
  cache.printList();
  cout << "------------------------------------------------------" << endl;
}

#undef CLASSNAME
