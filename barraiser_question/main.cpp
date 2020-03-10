// Given a 2D array containing a binary image. Return the number of objects in the image.
// An object is a bunch of adjacent black pixels. Neighourhood is only straight line, not diagonal.

//  W W B W W
//  B B W B B
//  B B W W B
// This would be 3 objects

#include<QString>
#include<QQueue>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// common includes


using namespace std;


struct Coord
{
    int row;
    int col;

    Coord(int r, int c) : row(r), col(c)  {}
};

int getNumObjects(const vector< vector<char> > &image)
{
    // image height must be > 0
    int img_height = image.size();
    if (img_height==0)
        return 0;

    // image width must be > 0
    int img_width = image[0].size();
    if (img_width==0)
        return 0;

    // All columns must have the same width
    // This check is not necessary if a better data structure is used as image
    for (int row=0; row<img_height; row++)
    {
        if (image[row].size() != img_width)
        {
            cerr << "This is not a regular image because the width is not equal in all rows." << endl;
            return 0;
        }
    }

    // Use that instead of a hash set to check whether we have already visited a pixel
    vector<bool> visited_cols(img_width, false);
    vector<vector<bool>> visited_map(img_height, visited_cols);

    int num_objects = 0;
    for (int row=0; row<img_height; row++)
    {
        for (int col=0; col<img_width; col++)
        {
            if (image[row][col] == 'B')
            {
                // Check if we have already processed this coordinate
                if (visited_map[row][col])
                    continue;

                // We found a new object
                num_objects++;
                visited_map[row][col] = true;

                // Add to queue and find all of neighbours that belong to the same object
                QQueue<Coord> queue;
                queue.push_back(Coord(row, col));

                while(!queue.isEmpty())
                {
                    // find all neighbours and put them on the list
                    Coord current_pixel = queue.front();
                    queue.pop_front();

                    // lower neighbour
                    Coord lower_neighbour(current_pixel.row+1, current_pixel.col);
                    if (lower_neighbour.row < img_height)
                    {
                        if (!visited_map[lower_neighbour.row][lower_neighbour.col]  && image[lower_neighbour.row][lower_neighbour.col] == 'B')
                        {
                            queue.push_back(lower_neighbour);
                            visited_map[lower_neighbour.row][lower_neighbour.col] = true;
                        }
                    }

                    // upper neighbour
                    Coord upper_neighbour(current_pixel.row-1, current_pixel.col);
                    if (upper_neighbour.row >= 0)
                    {
                        if (!visited_map[upper_neighbour.row][upper_neighbour.col]  && image[upper_neighbour.row][upper_neighbour.col] == 'B')
                        {
                            queue.push_back(upper_neighbour);
                            visited_map[upper_neighbour.row][upper_neighbour.col] = true;
                        }
                    }

                    // right neighbour
                    Coord right_neighbour(current_pixel.row, current_pixel.col+1);
                    if (right_neighbour.col < img_width)
                    {
                        if (!visited_map[right_neighbour.row][right_neighbour.col] && image[right_neighbour.row][right_neighbour.col] == 'B')
                        {
                            queue.push_back(right_neighbour);
                            visited_map[right_neighbour.row][right_neighbour.col] = true;
                        }
                    }

                    // left neighbour
                    Coord left_neighbour(current_pixel.row, current_pixel.col-1);
                    if (left_neighbour.col >= 0)
                    {
                        if (!visited_map[left_neighbour.row][left_neighbour.col] && image[left_neighbour.row][left_neighbour.col] == 'B')
                        {
                            queue.push_back(left_neighbour);
                            visited_map[left_neighbour.row][left_neighbour.col] = true;
                        }
                    }
                }
            }
        }
    }

    return num_objects;
}


int main(int argc, char *argv[])
{        
    vector< vector<char> > test_image;
    vector<char> curr_row = {'W', 'B', 'B', 'B', 'B', 'B'};       test_image.push_back(curr_row);
    curr_row =              {'B', 'B', 'W', 'W', 'W', 'B'};       test_image.push_back(curr_row);
    curr_row =              {'B', 'B', 'W', 'B', 'W', 'B'};       test_image.push_back(curr_row);
    curr_row =              {'B', 'B', 'W', 'B', 'B', 'B'};       test_image.push_back(curr_row);


    int num_objects = getNumObjects(test_image);

    cout << "The image contains " << num_objects << " objects." << endl;
    return 0;
}
