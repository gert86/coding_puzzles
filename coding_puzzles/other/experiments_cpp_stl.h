#pragma once

#define CLASSNAME Experiments_Cpp_Stl

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------



// Notes to STL:
// -------------

// Iteratoren sind container-spezifisch implementiert aber Zugriff ist einheitlich um Container besser austauschen zu können.

// Die wichtigsten Container:
// --------------------------
// std::vector			--> Array
// std::list            --> Doubly-Linked List
// std::forward_list    --> Singly Linked List
// std::stack			--> Stack (LIFO)
// std::queue			--> Queue (FIFO)
// std::deque			--> Double sided queue

// WICHTIG: Es gibt KEINE Tree containers in STL oder boost! Dies ist nicht nötig, weil std::set und std::map Dinge intern ohnehin als binary tree abspeichern!

// std::set              --> Ordered, implemented as self-balanced tree, Search in logN, Insert/Delete in logN + Rebalance
// std::unordered_set    --> No ordering, implemented as hashmap, Search/Insert/Delete in amortized O(1). Use only if no ordered traversal is needed.
// std::map              --> same as set, but also stores a value to that key
// std::unordered_map	--> same as unordered_set, but also stores a value to that key
// Jede dieser 4 gibt es nochmal als ""multi-Variante", wenn man duplicates erlauben will: multiset, unordered_multiset, multimap, unordered_multimap

// Info: Es gibt auch sowas wie hash_map im std namespace, aber dies ist nicht Teil der STL sondern eine compiler-abhänige Extension (gcc vs msvc). Wenn man Hash Tables
// benutzen will --> std::unordered_set oder std::unordered_map.

// std::priority_queue	--> Adaption von queue, wo das größte (=default) Element in konstanter Zeit accessed werden kann mit top(), dafür dauert Insertion/Deletion logN.
//                           Iteriert man über priority_queue, so sind die Elemente stets geordnet.




// Common member functions for most containers:
// --------------------------------------------
// push_front()    	// nicht für vector
// pop_front()    	// nicht für vector
// at()				// Mit bounding check -> Nur für vector und deque
// []				// Ohne bounding check -> Nur für vector und deque
// push_back()
// pop_back()
// empty()
// size()
// insert()			// at a particular position
// erase()			// at a particular position
// remove()			// a particular value (only for lists). Takes O(N) because it needs to search first.
// clear()			// remove all
// resize()
// front()			// access front element
// back()			// access back element
// top()            // Meist vorhanden, wenn nur von einer Seite accessed werden kann, statt front/back.



// Custom comparator function
bool compare_as_ints (double i,double j)
{
  return (int(i)<int(j));
}



//    Useful functions (Part 1):
//    --------------------------
//    sort(first_iterator, last_iterator) 								// To sort the given vector.
//    reverse(first_iterator, last_iterator) 							// To reverse a vector.
//    *max_element (first_iterator, last_iterator) 						// To find the maximum element of a vector.
//    *min_element (first_iterator, last_iterator) 						// To find the minimum element of a vector.
//    accumulate(first_iterator, last_iterator, initial value of sum) 	// Does the summation of vector elements
//    count(first_iterator, last_iterator,x) 							// To count the occurrences of x in vector.
//    find(first_iterator, last_iterator, x) 							// Points to last address of vector                                                                        // ((name_of_vector).end()) if element is not present
TEST(CLASSNAME, Part1)
{    
    std::cout << std::endl << "##################   PART 1   ##################" << std::endl;

    // init from standard array
    int arr[] = {10, 20, 5, 23, 42, 15, 20};
    int n = sizeof(arr)/sizeof(arr[0]);
    std::vector<int> vect(arr, arr+n);

    // Sorting the Vector in Ascending order
    sort(vect.begin(), vect.end());
    std::cout << std::endl << "The sorted vector is: " << printVec(vect) << std::endl;
    // Reversing the Vector = {3, 2, 3, 1};
    reverse(vect.begin(), vect.end());
    std::cout << std::endl << "The reverse sorted vector is: " << printVec(vect) << std::endl;

    // Max element
    std::cout << "\nMaximum element of vector is: ";
    std::cout << *max_element(vect.begin(), vect.end());

    // Min element
    std::cout << "\nMinimum element of vector is: ";
    std::cout << *min_element(vect.begin(), vect.end());

    // Starting the summation from 0
    std::cout << "\nThe summation of vector elements is: ";
    std::cout << accumulate(vect.begin(), vect.end(), 0);

    // Counts the occurrences of 20 from 1st to last element
    std::cout << "\nNum occurrences of 20: " << count(vect.begin(), vect.end(), 20);

    // find() returns iterator to last address if element not present
    // A VECTOR HAS NO MEMBER FUNCTION FOR FIND!!!!
    find(vect.begin(), vect.end(), 5) != vect.end() ?
                        std::cout << "\nElement 5 found":
                        std::cout << "\nElement 5 not found" << std::endl;

    find(vect.begin(), vect.end(), 44) != vect.end() ?
                        std::cout << "\nElement 44 found":
                        std::cout << "\nElement 44 not found" << std::endl;
}



//    Useful functions (Part 2):
//    --------------------------
//    binary_search(first_iterator, last_iterator, x) 	// Tests whether x exists in sorted vector or not (only returns bool!)
//    lower_bound(first_iterator, last_iterator, x) 	// returns iterator pointing to 1st element in [first,last) which has a value not less than ‘x’.
//    upper_bound(first_iterator, last_iterator, x) 	// returns iterator pointing to 1st element in [first,last) which has a value greater than ‘x’.
//
//    Note: They can be applied to ANY sorted sequence container, but it does not make sense for anything else then a vector
TEST(CLASSNAME, Part2)
{
    std::cout << std::endl << "##################   PART 2   ##################" << std::endl;

    // brace initialization syntax
    std::vector<int> vect{10, 20, 5, 23, 42, 15, 20};

    // NOTE: VECT MUST BE SORTED, OTHERWISE BINARY SEARCH and UPPER/LOWER BOUND DELIVER WRONG RESULTS!!!!
    sort(vect.begin(), vect.end());

    // Check if 20 is present in the vector --> is present
    std::cout << std::endl << "The sorted vector is: " << printVec(vect) << std::endl;
    bool is_present = std::binary_search(vect.begin(), vect.end(), 20);                 // returns bool instead of iterator with find()
    if (is_present)  { std::cout << std::endl << "20 is present." << std::endl; }
    else             { std::cout << std::endl << "20 is NOT present." << std::endl;  }

    // Check if 50 is present in the vector --> is NOT present
    is_present = std::binary_search(vect.begin(), vect.end(), 50);
    if (is_present)  { std::cout << "50 is present." << std::endl; }
    else             { std::cout << "50 is NOT present." << std::endl;  }

    // Returns iterator pointing to the first occurrence that is >= 20 --> Position: 3, Value: 20
    auto Q = lower_bound(vect.begin(), vect.end(), 20);
    std::cout << "First element >= 20 is at position: " << Q-vect.begin() << ". The element value is " << *Q << std::endl;

    // Returns iterator pointing to the first occurrence that is >20 --> Position: 5, Value: 23
    auto P = upper_bound(vect.begin(), vect.end(), 20);
    std::cout << "First element > 20 is at position: " << P-vect.begin() << ". The element value is " << *P << std::endl;
}



//    Useful functions (Part 3):
//    --------------------------
//    arr.erase(position to be deleted) 					// Erases selected element in vector and shifts and resizes the vector elements accordingly.
//    arr.erase(unique(arr.begin(),arr.end()),arr.end()) 	// Erases the duplicate occurrences in sorted vector in a single line.
//    next_permutation(first_iterator, last_iterator) 	    // This modified the vector to its next permutation.
//    prev_permutation(first_iterator, last_iterator) 	    // This modified the vector to its previous permutation.
//    distance(first_iterator,desired_position) 			// Returns distance from first iterator to desired position (useful while finding the index).
TEST(CLASSNAME, Part3)
{
    std::cout << std::endl << "##################   PART 3   ##################" << std::endl;

    std::vector<int> vect{10, 20, 5, 23, 42, 15, 20};
    sort(vect.begin(), vect.end());
    std::cout << std::endl << "The sorted vector is: " << printVec(vect) << std::endl;

    // Delete second element of vector
    vect.erase(vect.begin()+1);
    std::cout << std::endl << "After erasing second element the vector is: " << std::endl;
    for (uint i=0; i<vect.size(); i++)  { std::cout << vect[i] << " "; }

    // Delete all duplicate occurrences
    std::sort(vect.begin(), vect.end());                // 5 15 20 20 23 42
    auto last = unique(vect.begin(), vect.end());       // 5 15 20 23 42 X
    vect.erase(last, vect.end());                       // 5 15 20 23 42

    //vect.erase( unique(vect.begin(),vect.end()), vect.end() );      // syntax for all-in-one
    std::cout << std::endl << "After erasing duplicates the vector is: " << std::endl;
    for (uint i=0; i<vect.size(); i++)  { std::cout << vect[i] << " "; }

    // modifies vector to its next permutation order
    next_permutation(vect.begin(), vect.end());
    std::cout << std::endl << "The next permutation of the vector is: " << std::endl;
    for (uint i=0; i<vect.size(); i++)  { std::cout << vect[i] << " "; }

    // modifies vector to its prev permutation order (as before)
    prev_permutation(vect.begin(), vect.end());
    std::cout << std::endl << "The previous permutation of the vector is: " << std::endl;
    for (uint i=0; i<vect.size(); i++)  { std::cout << vect[i] << " "; }

    // iterate over all permutations
    std::cout << std::endl;
    std::vector<int> str_vec = {3, 2, 1};   // must be sorted ascending to get all permutations.
    std::sort(str_vec.begin(), str_vec.end());
    int i = 1;
    do
    {
        std::cout << "Permutation #" << i++ << " is " << printVec(str_vec) << std::endl;
    } while ( next_permutation(str_vec.begin(), str_vec.end()) );
    // in case of duplicates, the permutations do not show duplicates


    // Initializing vector vect2 already sorted
    std::vector<int> vect2 = {5, 10, 15, 20, 20, 23, 42, 45};

    // Return element-distance of first to maximum element
    std::cout << std::endl << "Distance between first to max element: " << std::endl;
    std::cout << distance(vect2.begin(),
                     max_element(vect2.begin(), vect2.end()));   // Returns	7
}



//    Useful functions (Part 4):
//    --------------------------
//    find (InputIterator first, InputIterator last, const T& val)  // Returns iterator to the object or last if not found
//    stable_sort  // Use to preserve the original relative ordering of objects with same value
//    sort         // Normal sort
TEST(CLASSNAME, Part4)
{
    std::cout << std::endl << "##################   PART 4   ##################" << std::endl;

    // using std::find with array and pointer
    int myints[] = { 10, 20, 30, 40 };
    size_t n = sizeof(myints)/sizeof(myints[0]);
    int *ptr1 = std::find (myints, myints+n, 30);
    if (ptr1 != myints+n)    std::cout << "First Element found in myints: " << *ptr1 << std::endl;
    else                     std::cout << "First Element not found in myints" << std::endl;

    int *ptr2 = std::find (myints, myints+n, 31);
    if (ptr2 != myints+n)    std::cout << "Second Element found in myints: " << *ptr2 << std::endl;
    else                     std::cout << "Second Element not found in myints" << std::endl;


    // using std::find with vector and iterator
    std::vector<int> myvector (myints,myints+4);
    std::vector<int>::iterator it = find (myvector.begin(), myvector.end(), 30);
    if (it != myvector.end())     std::cout << "First Element found in myvector: " << *it << std::endl;
    else                          std::cout << "First Element not found in myvector" << std::endl;

    auto it2 = find (myvector.begin(), myvector.end(), 31);
    if (it2 != myvector.end())     std::cout << "Second Element found in myvector: " << *it << std::endl;
    else                           std::cout << "Second Element not found in myvector" << std::endl;


    double my_doubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};
    std::vector<double> my_double_vector;
    my_double_vector.assign(my_doubles,my_doubles+8);  // another way to init vector from array
    std::cout << std::endl << "The double vector is: " << printVec(my_double_vector) << std::endl;

    // Only considers the int part for comparison - the ordering of all "int-equal" elements remains stable with stable_sort though!
    // If sort is used instead of stable_sort, this ordering might or might not be preserved!
    std::stable_sort (my_double_vector.begin(), my_double_vector.end(), compare_as_ints);
    std::cout << std::endl << "The stable, sorted_as_int vector is: " << printVec(my_double_vector) << std::endl;

    // Real sorting of double values
    std::stable_sort (my_double_vector.begin(), my_double_vector.end());
    std::cout << std::endl << "The stable, real-sorted vector is: " << printVec(my_double_vector) << std::endl;
}



//    Useful functions (Part 5):
//    --------------------------
//    priority_queue
//    A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.
TEST(CLASSNAME, Part5)
{
    std::cout << std::endl << "##################   PART 5   ##################" << std::endl;

    // define a lambda function for printing
    // Note: Lambda templates require c++14
    auto print_lambda = []<class T>(T q)
    {
        while(!q.empty())
        {
            std::cout << q.top() << " ";
            q.pop();
        }
        std::cout << '\n';
    };

    // Priority queue, per default ordered in decreasing order
    std::priority_queue<int> queue;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        queue.push(n);

    cout << "The standard priority queue is: " << endl;
    print_lambda(queue);
    cout << "Its front elememt is: " << queue.top() << endl << endl << endl;


    // Priority queue with increasing order
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue2;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        queue2.push(n);

    cout << "The increased-order priority queue is: " << endl;
    print_lambda(queue2);
    cout << "Its front elememt is: " << queue2.top() << endl << endl << endl;
}



//    Useful functions (Part 6):
//    --------------------------
//    Most important functions for vector, stack, queue, deque, priority_queue,
//    forward_list, list, unordered_map, unordered_set, map, set
TEST(CLASSNAME, Part6)
{
    std::cout << std::endl << "##################   PART 6   ##################" << std::endl;

      // vector
      std::vector<int> my_vector = {8};
      my_vector.push_back(9);
      my_vector.insert(my_vector.begin(), 7);
      int accessed_val = my_vector[0];     // or .at(0)
      accessed_val = my_vector.front();    // 7
      accessed_val = my_vector.back();     // 9 - direct access or front/back access
      my_vector.erase(my_vector.end()-1);  // same as my_vector.pop_back();
      // no find
      cout << "My vector is " << printVec(my_vector) << endl;


      // stack
      std::stack<int> my_stack;
      my_stack.push(3); my_stack.push(4); my_stack.push(5);
      accessed_val = my_stack.top();     // only top can be accessed
      my_stack.pop();                    // pop is a separate functions that only removes
      cout << "Accessed stack value is " << accessed_val << endl;
      // no find, no clear


      // queue
      std::queue<int> my_queue;
      my_queue.push(3); my_queue.push(4); my_queue.push(5);
      accessed_val = my_queue.front();    // 3
      accessed_val = my_queue.back();     // 5 - both sides can be accessed
      my_queue.pop();                     // pop is a separate functions that only removes
      cout << "Accessed queue value is " << accessed_val << endl;
      // no find, no clear

      // deque
      std::deque<int> my_deque = {3};
      my_deque.push_back(4);   // like normal queue
      my_deque.push_front(2); my_deque.push_front(1);   // this only works for deque
      accessed_val = my_deque.front();    // 1
      cout << "Accessed deque value is " << accessed_val << endl;
      accessed_val = my_deque.back();     // 4 - both sides can be accessed
      cout << "Accessed deque value is " << accessed_val << endl;
      my_deque.pop_front();               // pop is again a separate function that only removes...
      my_deque.pop_back();                // ...but dequeue can POP FROM EITHER SIDE
      // no find. Has some other convenience
      // functions that queue does not have,
      // like insert, erase, clear, ...

      // priority_queue
      std::priority_queue<int, std::vector<int>, std::greater<int>> my_prio_queue = {3, 4};    // default is less, meaning decreasing order
      my_prio_queue.push(1); my_prio_queue.push(5); my_prio_queue.push(2);
      accessed_val = my_prio_queue.top();     // 1 (smallest)
      cout << "Accessed priority_queue value is " << accessed_val << endl;
      my_prio_queue.pop();                    // remove smallest
      accessed_val = my_prio_queue.top();     // 2 (smallest)
      cout << "Accessed priority_queue value is " << accessed_val << endl << endl;
      // no find, no clear - same minimal API as queue, but has top() instead of front() and back()





      // define a lambda function for printing list entries
      // Note: Lambda templates require c++14
      auto print_lambda_list = []<class T>(T l)
      {
          while(!l.empty())
          {
              std::cout << l.front() << " ";
              l.pop_front();
          }
          std::cout << std::endl;
      };



      // forward_list - "singly linked list"
      #define PPSL print_lambda_list(my_forward_list)
      cout << endl << "forward_list " << endl;
      std::forward_list<int> my_forward_list = {5};
      my_forward_list.push_front(4);                                                                   // only push_front
      my_forward_list.push_front(3); my_forward_list.push_front(2); PPSL;                              // 2, 3, 4, 5
      my_forward_list.insert_after(my_forward_list.before_begin(), 1); PPSL;                           // 1, 2, 3, 4, 5
      my_forward_list.erase_after(my_forward_list.before_begin()); PPSL;     // erase - by iterator    // 2, 3, 4, 5
      my_forward_list.remove(4); PPSL;                                       // remove - by value      // 2, 3, 5
      accessed_val = my_forward_list.front();                                // access only to front()
      my_forward_list.pop_front(); PPSL;                                     // pop is only for front  // 3, 5
      my_forward_list.clear();
      // no find, but broad API (reverse(), sort(), unique(), ...)
      // where is the next pointer???



      // list - "doubly linked list"
      #define PPDL print_lambda_list(my_list)
      cout << endl << "list " << endl;
      std::list<int> my_list = {3};
      my_list.push_front(2);                                                                                   // push_front() or push_back()
      my_list.push_back(4);  my_list.push_back(5);   PPDL;                                                     // 2, 3, 4, 5
      my_list.insert(my_list.begin(), 1);  PPDL;                                                               // 1, 2, 3, 4, 5
      my_list.erase(my_list.begin()); PPDL;                                    // erase - by iterator          // 2, 3, 4, 5
      my_list.remove(4); PPDL;                                                 // remove - by value            // 2, 3, 5
      accessed_val = my_list.front(); accessed_val = my_list.back();           // access to front() or back()
      my_list.pop_front(); PPDL;                                               // pop from front or back       // 3, 5
      my_list.pop_back(); PPDL;                                                // pop from front or back       // 3
      my_list.clear();
      // no find, but broad API (reverse(), sort(), unique(), ...)
      // different API than forward_list. No insert_after --> insert. No before_begin.
      // where is the next and prev pointer???







      // define a lambda function for printing map entries
      // Note: Lambda templates require c++14
      auto print_lambda_map = []<class T>(T m)
      {
          for (auto it = m.begin(); it != m.end(); ++it)
          {
              cout << "Key: " << it->first << ", Value: " << it->second << endl;
          }
      };

      // unordered_map - "Hash Map"
      #define PPUM print_lambda_map(my_unord_map)
      cout << endl << "hash map " << endl;
      std::unordered_map<std::string, int> my_unord_map;
      my_unord_map["A"] = 1; my_unord_map["B"] = 2; my_unord_map["C"] = 3; my_unord_map["D"] = 4;
      my_unord_map.insert(std::pair<string, int>("E", 5));
      PPUM;                                                   // not sorted
      auto um_iter = my_unord_map.find("C");
      if ( um_iter != my_unord_map.end() )
          my_unord_map.erase(um_iter);
      um_iter = my_unord_map.find("AAAA");
      if ( um_iter != my_unord_map.end() )
          my_unord_map.erase(um_iter);

      cout << "After erasing, the hash map contains " << my_unord_map.size() << " elements" << endl;
      accessed_val = my_unord_map.at("D");        // throws exception if key not present
      cout << "The accessed value for D is " << accessed_val << endl;
      accessed_val = my_unord_map["E"];           // returns 0 if key not present
      cout << "The accessed value for E is " << accessed_val << endl;


      // map - Stored as "Binary Search Tree"
      #define PPM print_lambda_map(my_map)
      cout << endl << "map " << endl;
      std::map<std::string, int> my_map;
      my_map["A"] = 1; my_map["B"] = 2; my_map["C"] = 3; my_map["D"] = 4;
      my_map.insert(std::pair<string, int>("E", 5));
      PPM;                                                    // SORTED BY KEY!
      auto m_iter = my_map.find("C");
      if ( m_iter != my_map.end() )
          my_map.erase(m_iter);
      m_iter = my_map.find("AAAA");
      if ( m_iter != my_map.end() )
          my_map.erase(m_iter);

      cout << "After erasing, the map contains " << my_map.size() << " elements" << endl;
      accessed_val = my_map.at("D");        // throws exception if key not present
      cout << "The accessed value for D is " << accessed_val << endl;
      accessed_val = my_map["E"];           // returns 0 if key not present
      cout << "The accessed value for E is " << accessed_val << endl;






      // define a lambda function for printing set entries
      // Note: Lambda templates require c++14
      auto print_lambda_set = []<class T>(T s)
      {
          for (auto it = s.begin(); it != s.end(); ++it)
          {
              cout << "Entry: " << *it << endl;
          }
      };

      // unordered_set - "Hash Set"
      #define PPUS print_lambda_set(my_unord_set)
      cout << endl << "hash set " << endl;
      std::unordered_set<int> my_unord_set = {3, 2, 3, 1};
      my_unord_set.insert(5);  my_unord_set.insert(4);
      PPUS;                                                   // not sorted
      auto us_iter = my_unord_set.find(3);
      if ( us_iter != my_unord_set.end() )
          my_unord_set.erase(us_iter);
      us_iter = my_unord_set.find(99);
      if ( us_iter != my_unord_set.end() )
          my_unord_set.erase(us_iter);

      cout << "After erasing, the hash set contains " << my_unord_set.size() << " elements" << endl;
      // no [] access


      // set - Stored as "Binary Search Tree"
      #define PPS print_lambda_set(my_set)
      cout << endl << "set " << endl;
      std::set<int> my_set = {3, 2, 3, 1};
      my_set.insert(5);  my_set.insert(4);
      PPS;                                                   // SORTED BY KEY!
      auto s_iter = my_set.find(3);
      if ( s_iter != my_set.end() )
          my_set.erase(s_iter);
      s_iter = my_set.find(99);
      if ( s_iter != my_set.end() )
          my_set.erase(s_iter);

      cout << "After erasing, the set contains " << my_set.size() << " elements" << endl;
      // no [] access
}
#undef CLASSNAME
