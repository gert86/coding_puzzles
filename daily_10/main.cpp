// Implement a job scheduler which takes in a function f and an integer n, and calls f after n milliseconds.

#include<QString>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <vector>

using namespace std;

// Test Function 1
void functionToExecute()
{
    cout << "1: Executing functionToExecute" << endl;
}

// Test Function 2
int functionToExecuteWithReturnVal()
{
    cout << "2: Executing functionToExecuteWithReturnVal and returning 10" << endl;
    return 10;
}

// Test Function 3
void functionToExecuteWithArgs(string str, int num)
{
    cout << "3: Executing functionToExecuteWithArgs with args (" << str << " and " << num << ")" << endl;
}

// Test Function 4
int functionToExecuteWithArgsWithReturnVal(string str, int num)
{
    cout << "4: Executing functionToExecuteWithArgsWithReturnVal with args (" << str << " and " << num << ") and returning 20" << endl;
    return 20;
}

//////////////////////////////////////////////////////////
///  EASY JOB SCHEDULER
///  Naive version that only works for void functions
/////////////////////////////////////////////////////////
void jobSchedulerEasy(uint sleep_ms, void (*func)())
{
    cout << endl << ">>> Entered EASY job scheduler >>>" << endl;
    usleep(sleep_ms*1000);
    (*func)();
    cout << "<<< Leaving EASY job scheduler" << endl;
}


//////////////////////////////////////////////////////////
///  TEMPLATED JOB SCHEDULER
///  Only works for function 1 and 2 (without args)
/////////////////////////////////////////////////////////
template<typename Ret, typename... Args>
struct FunctionPointer
{
    using fp_type = Ret (*)(Args...);

    FunctionPointer(fp_type x)
        : func_(x)
    {}

    Ret operator()(Args&&... args) {
        return func_(std::forward<Args>(args)...);
    }

    fp_type func_;
};

template<typename Ret, typename... Args>
FunctionPointer<Ret, Args...> make_function_pointer(Ret (*func)(Args...))
{
    return {func};
}

template<typename Ret, typename... Args>
void jobSchedulerTemplated(uint sleep_ms, FunctionPointer<Ret, Args...> func)
{
    cout << endl << ">>> Entered TEMPLATED job scheduler >>>" << endl;
    usleep(sleep_ms*1000);
    func();
    cout << "<<< Leaving TEMPLATED job scheduler" << endl;
}




//////////////////////////////////////////////////////////
///  FUNCTIONAL JOB SCHEDULER
///  Works for all types but omits return value
/////////////////////////////////////////////////////////
void jobSchedulerFunctional(uint sleep_ms, std::function<void()> &func)
{
    cout << endl << ">>> Entered FUNCTIONAL job scheduler >>>" << endl;
    usleep(sleep_ms*1000);
    func();
    cout << "<<< Leaving FUNCTIONAL job scheduler" << endl;
}


//////////////////////////////////////////////////////////
///  SUPER-DUPER JOB SCHEDULER
///  Like functional scheduler, but uses template for return type. Works for all types.
/////////////////////////////////////////////////////////
template<typename Ret>
Ret jobSchedulerSuperDuper(uint sleep_ms, std::function<Ret()> &func)
{
    cout << endl << ">>> Entered SUPER-DUPER job scheduler >>>" << endl;
    usleep(sleep_ms*1000);
    return func();
    //cout << "<<< Leaving SUPER-DUPER job scheduler" << endl;  // only drawback: This log is not possible because we cannot store the return value if void.
}



int main()
{    
    enum Mode {Easy, Templated, Functional, SuperDuper};

    Mode mode = Mode::SuperDuper;

    //////////////////////////////////////////////////////////
    ///  EASY JOB SCHEDULER
    ///

    // The easy scheduler can be invoked like this, but it only works for function 1
    if (mode == Mode::Easy)
    {
        cout << "Going to test the easy job scheduler..." << endl;
        jobSchedulerEasy(5000u, &functionToExecute);
    }




    //////////////////////////////////////////////////////////
    ///  TEMPLATED JOB SCHEDULER

    if (mode == Mode::Templated)
    {
        cout << "Going to test the templated job scheduler..." << endl;

        // 1: void
        auto fn1 = make_function_pointer(functionToExecute);                // Note: type is FunctionPointer<void>
        //fn1();                                // call directly
        jobSchedulerTemplated(5000, fn1);       // call via job scheduler

        // 2: non-void
        auto fn2 = make_function_pointer(functionToExecuteWithReturnVal);   // Note: type is FunctionPointer<int>
        //fn2();                                // call directly
        jobSchedulerTemplated(5000, fn2);       // call via job scheduler

        // 3: void with args
        auto fn3 = make_function_pointer(functionToExecuteWithArgs);        // Note: type is FunctionPointer<void, string, int>
        fn3("Hello", 42);                       // call directly
        //jobSchedulerTemplated(5000, fn3);     // call via job scheduler    --> does not work yet!

        // 4: non-void with args
        auto fn4 = make_function_pointer(functionToExecuteWithArgsWithReturnVal);
        fn4("Goodbye", 69);                     // call directly
        //jobSchedulerTemplated(5000, fn4);     // call via job scheduler   --> does not work currently
    }


    //////////////////////////////////////////////////////////
    ///  FUNCTIONAL JOB SCHEDULER

    if (mode == Mode::Functional)
    {
        cout << "Going to test the functional job scheduler..." << endl;

        // 1: void
        std::function<void()> ff1= functionToExecute;
        //ff1();                                // call directly
        jobSchedulerFunctional(5000, ff1);       // call via job scheduler

        // 2: non-void
        std::function<void()> ff2 = functionToExecuteWithReturnVal;    // omitting return value!
        //ff2();                                // call directly
        jobSchedulerFunctional(5000, ff2);       // call via job scheduler

        // 3: void with args
        std::function<void()> ff3 = std::bind(functionToExecuteWithArgs, "Hello", 42);
        //ff3();                       // call directly
        jobSchedulerFunctional(5000, ff3);     // call via job scheduler

        // 4: non-void with args
        std::function<void()> ff4 = std::bind(functionToExecuteWithArgsWithReturnVal, "Goodbye", 69);  // omitting return value!
        //ff4();                       // call directly
        jobSchedulerFunctional(5000, ff4);     // call via job scheduler
    }

    //////////////////////////////////////////////////////////
    ///  SUPER-DUPER JOB SCHEDULER

    if (mode == Mode::SuperDuper)
    {
        cout << "Going to test the super-duper job scheduler..." << endl;

        // 1: void
        std::function<void()> ff1= functionToExecute;
        //ff1();                                // call directly
        jobSchedulerSuperDuper<void>(5000, ff1);       // call via job scheduler

        // 2: non-void
        std::function<int()> ff2 = functionToExecuteWithReturnVal;
        //ff2();                                // call directly
        int ret2 = jobSchedulerSuperDuper<int>(5000, ff2);       // call via job scheduler
        cout << "Return value was " << ret2 << endl;

        // 3: void with args
        std::function<void()> ff3 = std::bind(functionToExecuteWithArgs, "Hello", 42);
        //ff3();                       // call directly
        jobSchedulerSuperDuper<void>(5000, ff3);     // call via job scheduler

        // 4: non-void with args
        std::function<int()> ff4 = std::bind(functionToExecuteWithArgsWithReturnVal, "Goodbye", 69);  // omitting return value!
        //ff4();                       // call directly
        int ret4 = jobSchedulerSuperDuper<int>(5000, ff4);     // call via job scheduler

        cout << "Return value was " << ret4 << endl;
    }

    return 0;
}

