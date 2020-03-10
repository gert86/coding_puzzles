#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


using namespace std;


bool isPlacementValid(const vector<int> &columns)
{
    for (int i=0; i<columns.size(); i++)
    {
        for (int j=i+1; j<columns.size(); j++)
        {
            // same row violation
            if (columns[i] == columns[j])
                return false;

            int col_diff = j - i;
            int row_diff = abs(columns[j] - columns[i]);

            // same diagonal violation
            if (col_diff == row_diff)
                return false;
        }
    }

    return true;
}

int numPlacements(int N, vector<int> &current_columns)
{
    // we are done
    if (current_columns.size() == N)
        return 1;

    int num_valid = 0;
    for (int i=0; i<N; i++)
    {
        vector<int> column_copy = current_columns;
        column_copy.push_back(i);    // try a placement

        if (isPlacementValid(column_copy))
        {
            num_valid += numPlacements(N, column_copy);
        }
    }

    return num_valid;
}

int numPlacements(int N)
{
    vector<int> columns;
    return numPlacements(N, columns);
}

int main(int argc, char *argv[])
{    

    for(int i=0; i<=10; i++)
    {
        int num = numPlacements(i);
        cout << "For N = " << i << " the number of placements is: " << num << endl;
    }

    return 0;
}
