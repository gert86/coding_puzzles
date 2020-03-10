#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;


// Tutorial siehe: http://www.cplusplus.com/doc/oldtutorial/templates/


/////////////////////////////////////////////////////////////////
///                 1: Function templates
/////////////////////////////////////////////////////////////////
///
///  Using generic types as function arguments and/or return value
///

//template <typename T>         // Beide varianten...
template <class T>              // ...sind equivalent!
T GetMax(T a, T b)
{
    T result;
    result = (a>b) ? a : b;
    return result;
}

// Note:
// Man kann auch immer einen default type angeben, zB
// template <typename T=int>
//
// Dann kann man beim instanzieren folgendes machen:
// int biggest_int = GetMax<>(99, 66);
//
// In manchen Fällen ist das aber auch ohne default type möglich, wenn der Compiler
// den Typ automatisch bestimmen kann.




/////////////////////////////////////////////////////////////////
///                   2: Class templates
/////////////////////////////////////////////////////////////////
///
/// Using generic types as members or method arguments within the class.
///

template <class T>
class Mypair {
  private:
    T value_first;
    T value_second;

  public:
    Mypair (T first, T second)
    {
      value_first = first;
      value_second = second;
    }

    T getFirst() const
    {
        return value_first;
    }

    void setFirst(const T &val)
    {
        value_first = val;
    }

    T getSecond() const
    {
        return value_first;
    }

    void setSecond(const T &val);

};

// If functions are implemented outside, always use the template parameter twice...
//    template <class T> --> class template parameter
//    MyPair<T>          --> specifies that the function's template parameter is also the class template parameter
template <class T>
void Mypair<T>::setSecond(const T &val)
{
    value_second = val;
}



/////////////////////////////////////////////////////////////////
///               3: Template specialization
/////////////////////////////////////////////////////////////////
///
/// Having a class template and defining a special implementation for
/// a certain data type
///


// class template:
template <class T>
class Mycontainer {
    T element;
  public:
    Mycontainer (T arg) {element=arg;}
    T increase () {return ++element;}
};

// class template specialization:
// The empty <> signals that this is a specialization (like inheritance)
// After that we need to specify the type char explicitly anywhere in the function
template <>
class Mycontainer <char> {
    char element;
  public:
    Mycontainer (char arg) {element=arg;}
    char uppercase ()
    {
      if (( element>='a') && (element<='z') )
        element += ('A' - 'a');
      return element;
    }
};


/////////////////////////////////////////////////////////////////
///           4: Non-type parameters for templates
/////////////////////////////////////////////////////////////////
///
/// Template parameters are not always generic data types. They can also
/// contain a value of a standard type (e.g. int, to specify an
/// array size, which is otherwise not allowed by the compiler).
///


template <class T=char, int N=10>
class Mysequence {
    T memblock[N];
  public:
    void setmember (int x, T value);
    T getmember (int x);
};

template <class T, int N>
void Mysequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N>
T Mysequence<T,N>::getmember (int x) {
  return memblock[x];
}



/////////////////////////////////////////////////////////////////
///           5: Coding interview question
/////////////////////////////////////////////////////////////////
///
/// How to decide to calculate either SSD (sum of squared distances) or
/// SAD (sum of absolute differences) of COR (correlation)
///

class SSD
{
public:
    static int calculateError(const vector<int> &a, const vector<int> &b)
    {
        if (a.size() != b.size())
            return 0;

        int error = 0;
        for (int i=0; i<a.size(); i++)
        {
            error += (a[i] - b[i]) * (a[i] - b[i]);
        }

        return error;
    }
};

class SAD
{
public:
    static int calculateError(const vector<int> &a, const vector<int> &b)
    {
        if (a.size() != b.size())
            return 0;

        int error = 0;
        for (int i=0; i<a.size(); i++)
        {
            error += abs(a[i] - b[i]);
        }

        return error;
    }
};

class COR
{
public:
    static int calculateError(const vector<int> &a, const vector<int> &b)
    {
        if (a.size() != b.size())
            return 0;

        int error = 0;
        for (int i=0; i<a.size(); i++)
        {
            error += (a[i] + b[i]);
        }

        return error;
    }
};


template <class T>
class GenericErrorCalculator
{
public:
    static int calculateGenericError(const vector<int> &a, const vector<int> &b)
    {
        return T::calculateError(a, b);
    }
};





int main(int argc, char *argv[])
{    
    ///////////////////////////////////////////
    ///    1: Function template Testing
    ///////////////////////////////////////////
    float biggest_float = GetMax<float>(0.6, 0.9);      // The <int> is optional in this case (auto-deduction)
    cout << "The biggest float value is " << biggest_float << endl;

    int biggest_int = GetMax<int>(99, 66);
    cout << "The biggest int value is " << biggest_int << endl;

    string biggest_string = GetMax<string>("999", "666");
    cout << "The biggest string value is " << biggest_string << endl;
    cout << "------------------------------------------------" << endl << endl;



    ///////////////////////////////////////////
    ///    2: Class template Testing
    ///////////////////////////////////////////

    Mypair<int> mp_int(0,9);        // The <int> is required here!!!
    mp_int.setFirst(6);
    cout << "First int is " << mp_int.getFirst() << " and second one is " << mp_int.getSecond() << endl;

    Mypair<double> mp_double(0.006,0.009);
    cout << "First double is " << mp_double.getFirst() << " and second one is " << mp_double.getSecond() << endl;
    cout << "------------------------------------------------" << endl << endl;



    ///////////////////////////////////////////
    ///  3: Template Specialization Testing
    ///////////////////////////////////////////

    Mycontainer<int> myint (7);
    cout << "Calling increase for int gives: " << myint.increase() << endl;

    Mycontainer<float> myfloat(69.0);
    cout << "Calling increase for float gives: " << myfloat.increase() << endl;

    Mycontainer<char> mychar ('j');
    cout << "Calling uppercase for char gives: " << mychar.uppercase() << endl;

    cout << "------------------------------------------------" << endl << endl;


    ///////////////////////////////////////////
    /// 4: Non-type parameters for templates
    ///////////////////////////////////////////

    Mysequence <int,5> myints;
    myints.setmember (0, 100);
    cout << "Calling getmember() for int gives: " << myints.getmember(0) << endl;

    Mysequence <float,5> myfloats;
    myfloats.setmember (3, 3.1416);
    cout << "Calling getmember() for float gives: " << myfloats.getmember(3) << endl;

    Mysequence <> mychars;  // using defaults
    mychars.setmember (6, 'G');
    cout << "Calling getmember() for char gives: " << mychars.getmember(6) << endl;

    cout << "------------------------------------------------" << endl << endl;

    ///////////////////////////////////////////
    ///     5: Coding interview question
    ///////////////////////////////////////////

    vector<int> a = {1, 2, 3};
    vector<int> b = {1, 3, 6};

    cout << "Generic SSD error is: " << GenericErrorCalculator<SSD>::calculateGenericError(a, b) << endl;
    cout << "Generic SAD error is: " << GenericErrorCalculator<SAD>::calculateGenericError(a, b) << endl;
    cout << "Generic COR error is: " << GenericErrorCalculator<COR>::calculateGenericError(a, b) << endl;
    cout << "------------------------------------------------" << endl << endl;

    return 0;
}
