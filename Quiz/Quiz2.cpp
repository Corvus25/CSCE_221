// 1. Please download code on your computer.
// 2. Implement void resize_array(int*& array, int& capacity)
// 3. Call the above function in void add_elements(int start, int total_elem)
// 4. Compile the program and run
// 5. Enter the output results to the eCampus quiz 2
// 6. Complete the quiz 2
// 7. Submit your program to eCampus

//Based on this computational experiment provide a mathematical formula for num_resize and num_copy with respect to n = total_elem.
//Assume that n is an exact power of 2.
//
//6.  Enter the output results to the eCampus quiz 2
//
//7. Complete and submit the quiz 2.

#include <iostream>

using namespace std;

int num_resize; // the number of resizes
int num_copy;  // the number of copied elements

void resize_array(int*& array, int& capacity)
{
    int newSize = capacity * 2;
    int* newArray = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        newArray[i] = 0;
    }
    for (int i = 0; i < capacity; i++) {
        newArray[i] = array[i];
        num_copy++;
    }

    delete[] array;
    array = newArray;

    capacity = newSize;
    num_resize++;
}

void add_elements(int start, int total_elem)
{
    // Clear tracker variables
    num_resize = num_copy = 0;

    // Initialize array
    int capacity = start;
    int size = 0;
    int* A = new int[capacity];

    // Add elements to array
    while (size < total_elem)
    {
        if (size == capacity) // Array is full; add more space
        {
            // resize array
            resize_array(A, capacity);
        }
        ++size;
        int index = size - 1;
        A[index] = index*index; // new values
    }

    // Print tracking info
    cout << endl;
    cout << "Total elements: " << total_elem << endl;
    cout << "Resize " << num_resize << " times." << endl;
    cout << "Copied " << num_copy << " elements in total." << endl;
}

int main()
{
    // test this program
    int total_elem[]= {1, 2, 4, 64, 1024};
    for (int i = 0; i < 5; i++)
        add_elements(1, total_elem[i]);
}