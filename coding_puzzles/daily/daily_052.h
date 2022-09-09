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


// Strategy:
// 34, -50, 42, 14, -5, 86
// 34:        -> 34 -> store as max. series: [0,0]
//-50: 34-50  -> <0 forget
//       -50  -> <0 do not consider as new start
// 42:        -> 42 best so far -> store as max. series: [2,2]
// 14:        -> 42+14=56 even better -> store as max. series: [2,3]
// -5:        -> 42+14-5=51 -> not max, but still > 0 so continue with this series
// 86:        -> 42+14-5+86 -> 137 new max
// use an unordered_map as cache -> access in O(1)
// Keep the "least used" info in a (modified) linked list -> push/pop at both ends in O(1), erase in O(1) if node is known!
// We need to store the Node* inside the cache, so that we never need to search the linked list
//
//
// get(): queries the unordered_map
//  if not exists -> return null
//  if exists -> get the node from cache, remove node from list, re-add it to front of list (most recently used)
//  return element
//
// set(): queries the unordered map
//   if not exists -> create a new list node, add it to front of list (most recently used)
//   if exists     -> get the node from cache, remove node from list, re-add it to front of list (most recently used)
//
//   if (cache is full and not exists)
//     remove list node from back of list (least recently used)
//     remove element from cache
//   store element to cache


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

    void printCacheMap() const
    {
      std::cout << std::endl << "Cache: " << std::endl;
      for (const auto &[key, val] : _map)
        std::cout << " map[" << key << "] = " << val.first << std::endl;
    }

    void printLruList() const
    {
      std::cout << "LRU List: " << std::endl;
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
  cache.printCacheMap();
  cache.printLruList();


  cache.set(2, 200);
  ASSERT_EQ(*cache.get(2), 200);
  cache.printCacheMap();
  cache.printLruList();


  cache.set(2, 201);
  ASSERT_EQ(*cache.get(2), 201);
  cache.printCacheMap();
  cache.printLruList();


  cache.set(3, 300);
  ASSERT_EQ(*cache.get(3), 300);
  cache.printCacheMap();
  cache.printLruList();


  cache.set(4, 400);
  ASSERT_EQ(*cache.get(4), 400);
  cache.printCacheMap();
  cache.printLruList();

  ASSERT_EQ(cache.get(1), nullopt);   // 1 was the least recently used and got dropped
  cache.printCacheMap();
  cache.printLruList();

  ASSERT_EQ(*cache.get(3), 300);
  ASSERT_EQ(*cache.get(2), 201);
  ASSERT_EQ(*cache.get(4), 400);
  cache.printCacheMap();
  cache.printLruList();

  cache.set(5, 500);
  ASSERT_EQ(*cache.get(5), 500);
  cache.printCacheMap();
  cache.printLruList();

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
  cache.printCacheMap();
  cache.printLruList();
  cout << "------------------------------------------------------" << endl;


  cache.set(1001,     3);
  cache.set(1002,      12);
  cache.set(1003,  102);

  ASSERT_EQ(3,       *cache.get(1001));
  cache.printCacheMap();
  cache.printLruList();
  cout << "------------------------------------------------------" << endl;


  cache.set(1004,     1000);  // 1002 falls out

  ASSERT_EQ(1000,     *cache.get(1004));
  ASSERT_EQ(3,        *cache.get(1001));
  ASSERT_EQ(nullopt,   cache.get(1002));
  ASSERT_EQ(102,      *cache.get(1003));
  cache.printCacheMap();
  cache.printLruList();
  cout << "------------------------------------------------------" << endl;
}

#undef CLASSNAME
