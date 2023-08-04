#pragma once

#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define VERSION_STRING(x) (TO_STR(x))

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <list>
#include <stack>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <math.h>
#include <chrono>

#include <QString>
#include <QStringList>
#include <QSet>
#include <QPair>
#include <QVector>

#include "gtest/gtest.h"

using namespace std;

namespace Helper
{
    template <typename T>
    string printVec(const vector<T> &vec)
    {
        stringstream ss;
        ss << "[";
        for (int i=0; i<vec.size(); i++)
        {
            ss << vec[i];
            if (i != vec.size()-1)
            {
                ss << ", ";
            }
        }
        ss << "]";

        return ss.str();
    }

    template <typename T>
    string printSet(const set<T> &elements)
    {
        stringstream ss;
        for (auto it = elements.begin(); it != elements.end(); it++)
        {
            ss << *it;
            ss << " ";

        }
        return ss.str();
    }

    template <typename T>
    string printDeque(const deque<T> &elements)
    {
        stringstream ss;
        for (auto it = elements.begin(); it != elements.end(); it++)
        {
            ss << *it;
            ss << " ";

        }
        return ss.str();
    }

    template <typename T>
    string printQueue(std::queue<T> elements)
    {
        stringstream ss;
        while (!elements.empty()) {
            ss << elements.front() << " ";
            elements.pop();
        }
        return ss.str();
    }

    template <typename K, typename V>
    void printMap(const std::map<K, V> &myMap)
    {
      for (const auto &[key,val] : myMap) {
        std::cout << "map[" << key << "] = " << val << std::endl;
      }
    }
}
