#pragma once

#define CLASSNAME Daily_052

#include "base_header.h"

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

    template <class K, class V>
    class LRUCache
    {
    private:
        int m_size;
        std::unordered_map<K, V> m_hash_map;
        std::list<K> m_last_used_keys;

    public:
        LRUCache(int size) : m_size(size) {}

        string set(K key, V value);
        V* get(K key);
    };
};

template <class K, class V>
string CLASSNAME::LRUCache<K,V>::set(K key, V value)
{
    // This string to be returned is only for testing - otherwise method can be void.
    string operation = "";

    if (m_hash_map.size() < m_size)
    {
        // enough space, no deletion from hash map necessary
        if (m_hash_map.find(key)==m_hash_map.end())
        {
            m_last_used_keys.push_back(key);     // add to back of list
            m_hash_map[key] = value;             // ADD
            cout << "SET(NOT_FULL_ADD): Added " << key << " with value " << value << endl;
            operation = "NOT_FULL_ADD";
        }
        else
        {
            m_last_used_keys.remove(key);        // move to...                  TODO: This is not O(1)!
            m_last_used_keys.push_back(key);     // ...end of queue
            m_hash_map[key] = value;             // UPDATE
            cout << "SET(NOT_FULL_UPDATE): Updated " << key << " with value " << value << endl;
            operation = "NOT_FULL_UPDATE";
        }
    }
    else
    {
        // cache already full
        if (m_hash_map.find(key)==m_hash_map.end())
        {
            // key does not exist yet, we must therefore erase the least used element
            K key_to_remove = m_last_used_keys.front();
            m_last_used_keys.pop_front();               // remove from front of list
            m_hash_map.erase(key_to_remove);            // REMOVE

            m_last_used_keys.push_back(key);            // add to back of list
            m_hash_map[key] = value;                    // ADD

            cout << "SET(FULL_REMOVE_ADD): Added " << key << " with value " << value << " but deleted least recently used key " << key_to_remove << endl;
            operation = "FULL_REMOVE_ADD";
        }
        else
        {
            m_last_used_keys.remove(key);        // move to...                  TODO: This is not O(1)!
            m_last_used_keys.push_back(key);     // ...end of queue
            m_hash_map[key] = value;             // UPDATE

            cout << "SET(FULL_UPDATE): Updated " << key << " with value " << value << endl;
            operation = "FULL_UPDATE";
        }
    }

    assert(m_hash_map.size() == m_last_used_keys.size());
    return operation;
}

template <class K, class V>
V* CLASSNAME::LRUCache<K,V>::get(K key)
{
    if (m_hash_map.find(key)==m_hash_map.end())
    {
        cout << "GET(NOT_FOUND): Key " << key << " does not exist. Nullptr returned." << endl;
        return nullptr;
    }
    else
    {
        V &val = m_hash_map[key];            // GET
        m_last_used_keys.remove(key);        // move to...                  TODO: This is not O(1)!
        m_last_used_keys.push_back(key);     // ...end of queue

        cout << "GET(FOUND): Key " << key << " has value " << val << endl;
        return &val;
    }
}

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    CLASSNAME::LRUCache<string,int> my_cache(3);

    ASSERT_EQ("NOT_FULL_ADD",    my_cache.set("Apple",    0));
    ASSERT_EQ("NOT_FULL_UPDATE", my_cache.set("Apple",    1));
    ASSERT_EQ("NOT_FULL_UPDATE", my_cache.set("Apple",    2));
    ASSERT_EQ("NOT_FULL_ADD",    my_cache.set("Bee",     11));
    ASSERT_EQ("NOT_FULL_ADD",    my_cache.set("Crayon", 101));

    ASSERT_EQ(2,       *my_cache.get("Apple"));
    ASSERT_EQ(11,      *my_cache.get("Bee"));
    ASSERT_EQ(101,     *my_cache.get("Crayon"));
    ASSERT_EQ(nullptr,  my_cache.get("Drum"));
    ASSERT_EQ(nullptr,  my_cache.get("Echo"));
    cout << "------------------------------------------------------" << endl;


    ASSERT_EQ("FULL_UPDATE", my_cache.set("Apple",     3));
    ASSERT_EQ("FULL_UPDATE", my_cache.set("Bee",      12));
    ASSERT_EQ("FULL_UPDATE", my_cache.set("Crayon",  102));

    ASSERT_EQ(3,       *my_cache.get("Apple"));
    cout << "------------------------------------------------------" << endl;


    ASSERT_EQ("FULL_REMOVE_ADD", my_cache.set("Drum",     1000));  // Bee falls out
    ASSERT_EQ(1000,     *my_cache.get("Drum"));
    ASSERT_EQ(3,        *my_cache.get("Apple"));
    ASSERT_EQ(nullptr,   my_cache.get("Bee"));
    ASSERT_EQ(102,      *my_cache.get("Crayon"));
    cout << "------------------------------------------------------" << endl;
}

#undef CLASSNAME
