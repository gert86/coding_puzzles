// Given an unordered list of flights taken by someone, each represented as (origin, destination) pairs, and a starting airport, compute the person's itinerary.
// If no such itinerary exists, return null. If there are multiple possible itineraries, return the lexicographically smallest one. All flights must be used in the itinerary.
//
// For example, given the list of flights [('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL', 'YYZ'), ('HKO', 'ORD')] and starting airport 'YUL', you should return the list ['YUL', 'YYZ', 'SFO', 'HKO', 'ORD'].
//
// Given the list of flights [('SFO', 'COM'), ('COM', 'YYZ')] and starting airport 'COM', you should return null.
//
// Given the list of flights [('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')] and starting airport 'A', you should return the list ['A', 'B', 'C', 'A', 'C'] even though
// ['A', 'C', 'A', 'B', 'C'] is also a valid itinerary. However, the first one is lexicographically smaller.


#include<QString>
#include<QStringList>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// common includes


using namespace std;


// Notes:
// Problem seems easy at the first glance, but here are the challenges
// 1: We need to handle duplicates, thus we need to try different paths (recursively)
// 2: Duplicates need to be processed in a certain order
// 3: We don't want O(N²) complexity, therefore we need to organize the flights in a good way first
// 4: It's not sufficient to check if an itinerary exists - we also need to STORE AND RETURN the final result
// 5: For the different variants (duplicates) we need to copy the itinerary that was created up to this point
// 6: The recursive part needs to distinguish between DONE and FAILED
// 7: ATTENTION: Flight entry ("SRC-DEST") vs. Location entry ("DEST")



// Inner method - called from outer method initially and from itself recursively
bool createItineraryRecursive(QStringList &sorted_flight_list, QString starting_airport, QStringList *resulting_itinerary)
{
    // We are done - OK
    if (sorted_flight_list.isEmpty())
    {
        return true;
    }
    //cout << "Not done yet. Num flights: " << sorted_flight_list.count() << " and itinerary_size: " << resulting_itinerary->count() << endl;

    QStringList eligible_connection_flights = sorted_flight_list.filter(starting_airport + "-");
    if (eligible_connection_flights.isEmpty())
    {
        // we are done - FAIL        
        return false;
    }

    // easy case - only one possible next flight
    if (eligible_connection_flights.size()==1)
    {
        QString next_flight = eligible_connection_flights[0];
        QString next_destination = next_flight.mid( next_flight.indexOf("-") + 1 );

        // Take this flight and repeat at dest airport
        sorted_flight_list.removeOne(next_flight);
        resulting_itinerary->push_back(next_destination);

        return createItineraryRecursive(sorted_flight_list, next_destination, resulting_itinerary);
    }


    // difficult case - more than one next option
    for (auto &next_flight : eligible_connection_flights)
    {
        QString next_destination = next_flight.mid( next_flight.indexOf("-") + 1 );

        // Take this flight and repeat at dest airport - create a copy of resulting itinerary and remaining flight list
        QStringList *sorted_flight_list_copy = new QStringList(sorted_flight_list);
        QStringList *resulting_itinerary_copy = new QStringList(*resulting_itinerary);

        sorted_flight_list_copy->removeOne(next_flight);
        resulting_itinerary_copy->push_back(next_destination);

        if ( createItineraryRecursive(*sorted_flight_list_copy, next_destination, resulting_itinerary_copy) )
        {
            // Do not forget this! Also, it does not work to do this assignment with the pointers!
            *resulting_itinerary = *resulting_itinerary_copy;
            return true;
        }
    }

    // none of the options worked
    return false;
}


// outer method - called from main
bool createItinerary(const QList<QPair<QString, QString>> &flight_list, QString starting_airport, QStringList *resulting_itinerary)
{
    // Trivial case where initial list is empty - could also return true (needs to be defined)
    if (flight_list.isEmpty())
        return false;

    // Put everything into sorted QStringList
    QStringList sorted_flight_list;
    for(auto &flight : flight_list)
    {
        sorted_flight_list.push_back(flight.first + "-" + flight.second);
    }
    sorted_flight_list.sort(Qt::CaseInsensitive);

    // Add the start airport to resulting itinerary because recursive method will always add the destination of each flight only
    resulting_itinerary->push_back(starting_airport);

    return createItineraryRecursive(sorted_flight_list, starting_airport, resulting_itinerary);
}




int main(int argc, char *argv[])
{        
    QString starting_airport_1 = "YUL";
    QList<QPair<QString, QString>> flight_list_1;
    flight_list_1.push_back(QPair<QString,QString>("SFO", "HKO"));
    flight_list_1.push_back(QPair<QString,QString>("YYZ", "SFO"));
    flight_list_1.push_back(QPair<QString,QString>("YUL", "YYZ"));
    flight_list_1.push_back(QPair<QString,QString>("HKO", "ORD"));

    QStringList *resulting_itinerary_1 = new QStringList();
    bool result_1 = createItinerary(flight_list_1, starting_airport_1, resulting_itinerary_1);

    if (result_1)
    {
        cout << "1: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_1)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "1: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: YUL YYZ SFO HKO ORD

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QString starting_airport_2 = "COM";
    QList<QPair<QString, QString>> flight_list_2;
    flight_list_2.push_back(QPair<QString,QString>("SFO", "COM"));
    flight_list_2.push_back(QPair<QString,QString>("COM", "YYZ"));

    QStringList *resulting_itinerary_2 = new QStringList();
    bool result_2 = createItinerary(flight_list_2, starting_airport_2, resulting_itinerary_2);

    if (result_2)
    {
        cout << "2: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_2)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "2: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: No valid itinerary possible

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QString starting_airport_3 = "A";
    QList<QPair<QString, QString>> flight_list_3;
    flight_list_3.push_back(QPair<QString,QString>("A", "B"));
    flight_list_3.push_back(QPair<QString,QString>("A", "C"));
    flight_list_3.push_back(QPair<QString,QString>("B", "C"));
    flight_list_3.push_back(QPair<QString,QString>("C", "A"));

    QStringList *resulting_itinerary_3 = new QStringList();
    bool result_3 = createItinerary(flight_list_3, starting_airport_3, resulting_itinerary_3);

    if (result_3)
    {
        cout << "3: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_3)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "3: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: A B C A C

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QString starting_airport_4 = "A";
    QList<QPair<QString, QString>> flight_list_4;
    flight_list_4.push_back(QPair<QString,QString>("B", "C"));
    flight_list_4.push_back(QPair<QString,QString>("B", "D"));
    flight_list_4.push_back(QPair<QString,QString>("A", "B"));
    flight_list_4.push_back(QPair<QString,QString>("D", "B"));
    flight_list_4.push_back(QPair<QString,QString>("C", "E"));

    QStringList *resulting_itinerary_4 = new QStringList();
    bool result_4 = createItinerary(flight_list_4, starting_airport_4, resulting_itinerary_4);

    if (result_4)
    {
        cout << "4: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_4)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "4: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: A B D B C E

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QString starting_airport_5 = "A";
    QList<QPair<QString, QString>> flight_list_5;
    flight_list_5.push_back(QPair<QString,QString>("B", "C"));  //2
    flight_list_5.push_back(QPair<QString,QString>("B", "D"));  //6
    flight_list_5.push_back(QPair<QString,QString>("A", "B"));  //1
    flight_list_5.push_back(QPair<QString,QString>("D", "B"));  //7
    flight_list_5.push_back(QPair<QString,QString>("C", "E"));  //3
    flight_list_5.push_back(QPair<QString,QString>("E", "A"));  //4
    flight_list_5.push_back(QPair<QString,QString>("A", "B"));  //5

    QStringList *resulting_itinerary_5 = new QStringList();
    bool result_5 = createItinerary(flight_list_5, starting_airport_5, resulting_itinerary_5);

    if (result_5)
    {
        cout << "5: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_5)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "5: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: A B C E A B D B (also possible: A B D B C E A B)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QString starting_airport_6 = "A";
    QList<QPair<QString, QString>> flight_list_6;
    flight_list_6.push_back(QPair<QString,QString>("B", "C"));  //2
    flight_list_6.push_back(QPair<QString,QString>("B", "C"));  //6
    flight_list_6.push_back(QPair<QString,QString>("C", "B"));  //3
    flight_list_6.push_back(QPair<QString,QString>("B", "D"));  //4
    flight_list_6.push_back(QPair<QString,QString>("A", "B"));  //1
    flight_list_6.push_back(QPair<QString,QString>("D", "B"));  //5
    flight_list_6.push_back(QPair<QString,QString>("E", "A"));  //8
    flight_list_6.push_back(QPair<QString,QString>("A", "F"));  //9
    flight_list_6.push_back(QPair<QString,QString>("C", "E"));  //7


    QStringList *resulting_itinerary_6 = new QStringList();
    bool result_6 = createItinerary(flight_list_6, starting_airport_6, resulting_itinerary_6);

    if (result_6)
    {
        cout << "6: SUCCESS: There is a valid itinerary..." << endl;
        for (auto &airport : *resulting_itinerary_6)
        {
            cout << airport.toStdString() << " ";
        }
        cout << endl << endl;
    }
    else
    {
        cout << "6: FAIL: No valid itinerary possible." << endl << endl;
    }

    // Expected: A B C B D B C E A F   (also possible: A B D B C B C E A F)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;
}
