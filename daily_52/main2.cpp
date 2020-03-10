//Implement an LRU (Least Recently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:

//    set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item, then it should also remove the least recently used item.
//    get(key): gets the value at key. If no such key exists, return null.

//Each operation should run in O(1) time.


#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <unordered_map>
#include <list>
#include <assert.h>


using namespace std;

template <class K, class V>
class LRUCache
{
    typedef typename std::list<K>::iterator ListIterator;
    typedef std::pair<V, ListIterator> Vplus;

private:
    int m_size;
    std::unordered_map<K, Vplus> m_hash_map;
    std::list<K> m_last_used_keys;

public:
    LRUCache(int size) : m_size(size) {}

    void set(K key, V value);
    V* get(K key);
};


template <class K, class V>
void LRUCache<K,V>::set(K key, V value)
{
    if (m_hash_map.size() < m_size)
    {
        // enough space, no deletion from hash map necessary
        if (m_hash_map.find(key)==m_hash_map.end())
        {
            m_last_used_keys.push_back(key);                      // add to back of list
            m_hash_map[key] = make_pair<V, ListIterator>((V)value, (ListIterator)m_last_used_keys.end()--);   // ADD
            cout << "SET(1a): Added " << key << " with value " << value << endl;
        }
        else
        {
            m_last_used_keys.erase( m_hash_map[key].second );        // move to...
            m_last_used_keys.push_back(key);                          // ...end of queue
            m_hash_map[key].first = value;                            // UPDATE
            m_hash_map[key].second = m_last_used_keys.end()--;
            cout << "SET(1b): Updated " << key << " with value " << value << endl;
        }
    }
    else
    {
        // cache already full
        if (m_hash_map.find(key)==m_hash_map.end())
        {
            // key does not exist yet, we must therefore erase the least used element
            cout << "VORHER: m_hash_map.size() is " << m_hash_map.size() << "  -  m_last_used_keys.size() is " << m_last_used_keys.size() << endl;

            K key_to_remove = m_last_used_keys.front();
            m_last_used_keys.pop_front();     // remove from front of list
            m_hash_map.erase(key);            // REMOVE

            cout << "NACHHER: m_hash_map.size() is " << m_hash_map.size() << "  -  m_last_used_keys.size() is " << m_last_used_keys.size() << endl;

            assert(m_hash_map.size() == m_last_used_keys.size());

            m_last_used_keys.push_back(key);                      // add to back of list
            m_hash_map[key] = make_pair<V, ListIterator>((V)value, (ListIterator)m_last_used_keys.end()--);   // ADD

            cout << "SET(2a): Added " << key << " with value " << value << " but deleted least recently used key " << key_to_remove << endl;
        }
        else
        {                       
            m_last_used_keys.erase( m_hash_map[key].second );        // move to...
            m_last_used_keys.push_back(key);                          // ...end of queue
            m_hash_map[key].first = value;                            // UPDATE
            m_hash_map[key].second = m_last_used_keys.end()--;

            cout << "SET(2b): Updated " << key << " with value " << value << endl;
        }
    }

     cout << "IN THE END: m_hash_map.size() is " << m_hash_map.size() << "  -  m_last_used_keys.size() is " << m_last_used_keys.size() << endl;

    //assert(m_hash_map.size() == m_last_used_keys.size());

}

template <class K, class V>
V* LRUCache<K,V>::get(K key)
{
    if (m_hash_map.find(key)==m_hash_map.end())
    {
        cout << "GET(1): Key " << key << " does not exist. Nullptr returned." << endl;
        return nullptr;
    }
    else
    {
        V &val = m_hash_map[key].first;     // GET
        m_last_used_keys.erase( m_hash_map[key].second );        // move to...
        m_last_used_keys.push_back(key);                          // ...end of queue

        cout << "GET(2): Key " << key << " has value " << val << endl;
        return &val;
    }
}

int main(int argc, char *argv[])
{    

    LRUCache<string,int> my_cache(3);

    my_cache.set("Apple",    0);
    my_cache.set("Apple",    1);
    my_cache.set("Apple",    2);
    my_cache.set("Bee",     11);
    my_cache.set("Crayon", 101);

    int *result = my_cache.get("Apple");
    result = my_cache.get("Bee");
    result = my_cache.get("Crayon");
    result = my_cache.get("Drum");
    result = my_cache.get("Echo");
    cout << "------------------------------------------------------" << endl;


//    my_cache.set("Apple",     3);
//    result = my_cache.get("Apple");
//    cout << "------------------------------------------------------" << endl;


    my_cache.set("Drum",     1000);
//    result = my_cache.get("Drum");
//    result = my_cache.get("Apple");
//    cout << "------------------------------------------------------" << endl;

    return 0;
}
