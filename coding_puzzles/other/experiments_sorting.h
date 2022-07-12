#pragma once

#define CLASSNAME Experiments_Sorting

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Implementation and testing of the following sorting algorithms:
// * Bubble Sort
// * Selection Sort
// * Quick Sort
// * Merge Sort
// * Radix Sort
// * Bucket Sort

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Helper method to swap 2 elements in a given array
    void doSwap(vector<int> &array, int index1, int index2)
    {
        if ((int)array.size() <= index1 || (int)array.size() <= index2)
        {
            cerr << "doSwap: One of the indices is too large: index1=" << index1 << ", index2=" << index2 << endl;
            return;
        }

        if (index1 < 0 || index2 < 0)
        {
            cerr << "doSwap: One of the indices is too small: index1=" << index1 << ", index2=" << index2 << endl;
            return;
        }

        // this is better
        std::swap(array[index1], array[index2]);
    }

    void bubbleSort(vector<int> &array)
    {
        if (array.size() <= 1)
            return;

        for (int i=0; i<array.size()-1; i++)
        {
            for (int j=0; j<array.size()-1; j++)
            {
                // swap with neighbour
                if (array[j] > array[j+1])
                {
                    doSwap(array, j, j+1);
                }
            }
        }
    }

    void selectionSort(vector<int> &array)
    {
        if (array.size() <= 1)
            return;

        for (int i=0; i<array.size(); i++)
        {
            int current_min = std::numeric_limits<int>::max();
            int current_min_index = -1;
            for (int j=i; j<array.size(); j++)
            {
                if (array[j] < current_min)
                {
                    current_min = array[j];
                    current_min_index = j;
                }
            }

            // swap with min. element
            doSwap(array, i, current_min_index);
        }
    }

    // Helper method for quick sort
    int quickSortPartition(vector<int> &array, int left, int right)
    {
        int pivot_index = (left + right)/2;
        int pivot_value = array[pivot_index];

        // swap left and right elements according to the pivot element
        while (left <= right)
        {
            // Find element on left that should be right
            while(array[left] < pivot_value)  left++;

            // Find element on right that should be left
            while(array[right] > pivot_value)  right--;

            // Swap elements and move left and right indices
            if (left <= right)
            {
                doSwap(array, left, right);
                left++;
                right--;
            }
        }

        return left;
    }

    void quickSort(vector<int> &array, int left, int right)
    {
        if (array.size() <= 1)
            return;

        int index = quickSortPartition(array, left, right);
        if (index > left+1)
        {
            // sort left half
            //cout << "#### L: index was " << index << ". Sorting from " << left << " to " << index-1 << endl;
            quickSort(array, left, index - 1);
        }

        if (index < right)
        {
            // sort right half
            //cout << "#### R: index was " << index << ". Sorting from " << index << " to " << right << endl;
            quickSort(array, index, right);
        }
    }

    // Helper method for merge sort that merges back the results
    void merge(vector<int> &array, vector<int> &helper_array, int left, int middle, int right)
    {
        //cout << "######## merge called for range [" << left << " to " << right << "] with middle=" << middle << endl;

        // copy both halves into the helper array
        for(int i=left; i <= right; i++)
            helper_array[i] = array[i];

        int helper_left = left;
        int helper_right = middle + 1;
        int current = left;

        // Iterate through helper array. Compare the left and right half, copying back the
        // smaller element from the two halves into the original array.
        while (helper_left <= middle && helper_right <= right)
        {
            if (helper_array[helper_left] <= helper_array[helper_right])
            {
                // copy element from left half
                array[current] = helper_array[helper_left];
                helper_left++;
            }
            else
            {
                // copy element from right half
                array[current] = helper_array[helper_right];
                helper_right++;
            }
            current++;
        }

        // If the upper half was copied back completely and the lower half not, the rest of the lower half must be copied back.
        // Note: Otherwise this is not necessary, because the remaining upper half entries would be already in the right place.
        int remaining_elements_to_copy = middle - helper_left;
        for(int i=0; i<=remaining_elements_to_copy; i++)
            array[current + i] = helper_array[helper_left + i];
    }

    // Helper method for merge sort that creates the helper array and allows to specify range
    void mergeSortHelper(vector<int> &array, vector<int> &helper_array, int left, int right)
    {
        //cout << "#### mergeSortHelper called for range [" << left << " to " << right << "]" << endl;
        if (left < right)
        {
            int middle = (left + right)/2;
            mergeSortHelper(array, helper_array, left, middle);       // sort left half
            mergeSortHelper(array, helper_array, middle + 1, right);  // sort right half
            merge(array, helper_array, left, middle, right);          // merge them
        }
    }

    void mergeSort(vector<int> &array)
    {
        if (array.size() <= 1)
            return;

        vector<int> helper_array;
        helper_array.resize(array.size());
        mergeSortHelper(array, helper_array, 0, array.size() - 1);
    }

    void radixSort(vector<int> &array)
    {
        if (array.size() <= 1)
            return;

        vector<int> zeros;
        vector<int> ones;

        for (int i=0; i < 8*sizeof(int); i++)
        {
            // divide into 2 buckets (for ones and zeros)
            ones.clear();
            zeros.clear();
            for (int el : array)
            {
                if (el & (1<<i))
                    ones.push_back(el);
                else
                    zeros.push_back(el);
            }

            // combine buckets into a single array again
            array.clear();
            if (i < 8*sizeof(int) - 1)
            {
                // normal case - zeros before ones (i.e. smaller before larger)
                for (int el : zeros)
                    array.push_back(el);
                for (int el : ones)
                    array.push_back(el);
            }
            else
            {
                // sign bit - ones before zeros (i.e. negatives before positives)
                for (int el : ones)
                    array.push_back(el);
                for (int el : zeros)
                    array.push_back(el);
            }

            // Debug
            //cout << "#### Bit #" << i << ": Ones:  " << printVec(ones) << endl;
            //cout << "#### Bit #" << i << ": Zeros: " << printVec(zeros) << endl;
            //cout << "#### Bit #" << i << ": Array: " << printVec(array) << endl << endl;
        }
    }

    void bucketSort(vector<int> &array)
    {
        if (array.size() <= 1)
            return;

        // create configurable number of buckets
        int NUM_BUCKETS = 10;
        vector<int> buckets[NUM_BUCKETS];
        int max_val = *std::max_element(array.begin(), array.end());
        int min_val = *std::min_element(array.begin(), array.end());
        int diff = max_val - min_val;
        //cout << "## max = " << max_val << ", min=" << min_val << ", diff=" << diff << endl;

        // put each element into a certain bucket (like hash function)
        for (int el : array)
        {
            int bucket_idx = NUM_BUCKETS - 1;
            if (el != max_val)
            {
                bucket_idx = floor( ((el-min_val)/(float)diff) * NUM_BUCKETS);
                //cout << "######### idx of element " << el << " is " << bucket_idx << endl;
            }
            buckets[bucket_idx].push_back(el);
        }

        // sort each bucket individually (using an arbitrary sorting algorithm)
        for (auto &bucket : buckets)
        {
            std::sort(bucket.begin(), bucket.end());
            //cout << "#### Bucket has values: " << printVec(bucket) << endl;
        }

        // Copy the sorted buckets back to the original array
        array.clear();
        for (auto bucket : buckets)
        {
            for (int el : bucket)
            {
                array.push_back(el);
            }
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    const vector<int> array = {9, 0, -6, 7, 3, 1, 9, 0, 5, 100, -34, 21, 2, 15, 11};
    cout << "The unsorted array is:       " << printVec(array) << endl << endl;

    // reference soloution
    vector<int> sorted_reference = array;
    std::sort(sorted_reference.begin(), sorted_reference.end());
    cout << "Reference Solution:          " << printVec(sorted_reference) << endl;
    cout << "----------------" << endl;

    // Bubble Sort
    vector<int> sorted_bubble = array;
    instance.bubbleSort(sorted_bubble);
    cout << "Sorting with Bubble Sort:    " << printVec(sorted_bubble) << endl;
    ASSERT_EQ(sorted_reference, sorted_bubble);

    // Selection Sort
    vector<int> sorted_selection = array;
    instance.selectionSort(sorted_selection);
    cout << "Sorting with Selection Sort: " << printVec(sorted_selection) << endl;
    ASSERT_EQ(sorted_reference, sorted_selection);

    // Quick Sort
    vector<int> sorted_quick = array;
    instance.quickSort(sorted_quick, 0, array.size() - 1);
    cout << "Sorting with Quick Sort:     " << printVec(sorted_quick) << endl;
    ASSERT_EQ(sorted_reference, sorted_quick);

    // Merge Sort
    vector<int> sorted_merged = array;
    instance.mergeSort(sorted_merged);
    cout << "Sorting with Merge Sort:     " << printVec(sorted_merged) << endl;
    ASSERT_EQ(sorted_reference, sorted_merged);

    // Radix Sort
    vector<int> sorted_radix = array;
    instance.radixSort(sorted_radix);
    cout << "Sorting with Radix Sort:     " << printVec(sorted_radix) << endl;
    ASSERT_EQ(sorted_reference, sorted_radix);

    // Bucket Sort
    vector<int> sorted_bucket = array;
    instance.bucketSort(sorted_bucket);
    cout << "Sorting with Bucket Sort:    " << printVec(sorted_bucket) << endl;
    ASSERT_EQ(sorted_reference, sorted_bucket);
}

#undef CLASSNAME
