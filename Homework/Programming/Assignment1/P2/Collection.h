#ifndef PROJECTS_COLLECTION_H
#define PROJECTS_COLLECTION_H

#include <iostream>
#include <string>
#include "Stress_ball.h"

using namespace std;

class Collection {
private:
    Stress_ball *array; // pointer to dynamically allocated memory
    int size; // logical size of array - the number of elements in use
    int capacity; // physical size of array

public:
    Collection();
    Collection(int sz);
    Collection(const Collection&); // Copy constructor (deep copy)
    Collection& operator=(const Collection&); // Copy Assignment Operator
    ~Collection(); // Destructor
    Collection(Collection&&); // Move constructor (shallow copy), see Ch 1
    Collection& operator=(Collection&&); // Move assignment operator

    void insert_item(const Stress_ball& sb);
    void resize(); // Double size of array, copy elements from old to new array
    bool contains(const Stress_ball& sb) const; // Check if a stress ball of a given color & size is in the collection

    Stress_ball remove_any_item(); // Remove and return a random stress ball
    void remove_this_item(const Stress_ball& sb); // Remove a stress ball with a specific color and size from the collection
    void make_empty(); // Make the collection empty
    bool is_empty() const; // Check if the collection is empty
    int total_items() const; // Return total number of stress balls in the collection.
    int total_items(Stress_ball_sizes s) const; // Return total number of stress balls of the same size in the collection
    int total_items(Stress_ball_colors t) const; // Return total number of stress balls of the same color in the collection.
    void print_items() const; // Print all the stress balls in the collection

    Stress_ball& operator[](int i);
    const Stress_ball& operator[](int i) const;

    int getSize() const;
    int getCapacity() const;
};

enum class Sort_choice {
    bubble_sort,
    insertion_sort,
    selection_sort
};

istream& operator>>(istream& is, Collection& c);
ostream& operator<<(ostream& os, const Collection& c);

Collection make_Union(const Collection& c1, const Collection& c2);
void swap(Collection& c1, Collection& c2);
void sort_by_size(Collection& c, Sort_choice sort);



#endif //PROJECTS_COLLECTION_H
