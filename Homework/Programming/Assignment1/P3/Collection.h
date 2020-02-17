#ifndef PROJECTS_COLLECTION_H
#define PROJECTS_COLLECTION_H

#include <iostream>
#include <string>
#include "Stress_ball.h"

using namespace std;

template<typename Obj, typename F1, typename F2>
class Collection {
private:
    Obj *array; // pointer to dynamically allocated memory
    int size; // logical size of array - the number of elements in use
    int capacity; // physical size of array

public:
    Collection();
    Collection(int sz);
    Collection(const Collection<Obj, F1, F2>&); // Copy constructor (deep copy)
    Collection<Obj, F1, F2>& operator=(const Collection<Obj, F1, F2>&); // Copy Assignment Operator
    ~Collection(); // Destructor
    Collection(Collection<Obj, F1, F2>&&); // Move constructor (shallow copy), see Ch 1
    Collection<Obj, F1, F2>& operator=(Collection<Obj, F1, F2>&&); // Move assignment operator

    void insert_item(const Obj& obj);
    void resize(); // Double size of array, copy elements from old to new array
    bool contains(const Obj& obj) const; // Check if an object of a given color & size is in the collection

    Obj remove_any_item(); // Remove and return a random object
    void remove_this_item(const Obj& obj); // Remove an object with a specific color and size from the collection
    void make_empty(); // Make the collection empty
    bool is_empty() const; // Check if the collection is empty
    int total_items() const; // Return total number of objects in the collection.
    int total_items(F2 s) const; // Return total number of objects of the same size in the collection
    int total_items(F1 t) const; // Return total number of objects of the same color in the collection.
    void print_items() const; // Print all the objects in the collection

    Obj& operator[](int i);
    const Obj& operator[](int i) const;

    int getSize() const;
    int getCapacity() const;
};


// Default Constructor
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection() {
    size = 0;
    capacity = 0;
    array = nullptr;
}

// Single-Argument constructor
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(int sz) {
    capacity = sz;
    size = 0;
    array = new Obj[sz];
}

// Copy Constructor
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(const Collection& orig) {
    this->capacity = orig.capacity;
    this->size = orig.size;

    Obj *newAry = new Obj[capacity];
    for (int i = 0; i < size; i++) {
        newAry[i] = orig.array[i];
    }
//    delete[] this->array;
    this->array = newAry;
}

// Copy Assignment operator
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> &Collection<Obj, F1, F2>::operator=(const Collection& orig) {
    if (&orig == this) {
        return *this;
    }

    // Copy the resource
    this->capacity = orig.capacity;
    this->size = orig.size;

    Obj *newAry = new Obj[capacity];
    for (int i = 0; i < size; i++) {
        newAry[i] = orig.array[i];
    }
    delete[] this->array;
    this->array = newAry;

    return *this;
}

// Destructor
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::~Collection() {
    make_empty();
}

// Move constructor
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(Collection&& orig) {
    array = orig.array;
    size = orig.size;
    capacity = orig.capacity;

    orig.array = nullptr;
    orig.size = 0;
    orig.capacity = 0;
}

// Move assignment operator
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> &Collection<Obj, F1, F2>::operator=(Collection&& orig) {
    if (this == &orig) {
        return *this;
    }

    // Free existing resource
    delete[] array;

    // Copy from source object
    array = orig.array;
    size = orig.size;
    capacity = orig.capacity;

    // Release data pointer from source object
    // to keep destructor from freeing memory multiple times
    orig.array = nullptr;
    orig.size = 0;
    orig.capacity = 0;

    return *this;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::insert_item(const Obj &obj) {
    if (this->size == this->capacity) {
        resize();
    }
    this->array[size] = obj;
    this->size++;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::resize() {
    if (this->capacity == 0) {
        int newCapacity = 1;
        Obj *newAry = new Obj[newCapacity];
        this->array = newAry;
        this->capacity = newCapacity;
    } else {
        int newCapacity = this->capacity * 2;
        Obj *newAry = new Obj[newCapacity];
        for (int i = 0; i < this->size; i++) {
            newAry[i] = this->array[i];
        }
        delete[] this->array;
        this->array = newAry;
        this->capacity = newCapacity;
    }
}

template<typename Obj, typename F1, typename F2>
bool Collection<Obj, F1, F2>::contains(const Obj &obj) const {
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == obj) {
            return true;
        }
    }
    return false;
}

template<typename Obj, typename F1, typename F2>
Obj Collection<Obj, F1, F2>::remove_any_item() {
    srand(time(NULL));
    if (this->size == 0) {
        throw runtime_error("Collection is already empty. Unable to remove Object.");
    }
    int randIndex = rand() % this->size;
    Obj a = Obj(this->array[randIndex]);
    for (int i = randIndex; i < this->size-1; i++) {
        this->array[i] = this->array[i+1];
    }
    this->size--;
    return a;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::remove_this_item(const Obj &obj) {
    if (this->size == 0) {
        throw runtime_error("Collection is already empty. Unable to remove Obj.");
    }
    int index;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == obj) {
            index = i;
            break;
        }
    }

    for (int i = index; i < this->size-1; i++) {
        this->array[i] = this->array[i+1];
    }
    this->size--;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::make_empty() {
    try {
        this->size = 0;
        this->capacity = 0;
        delete[] this->array;
        array = nullptr;
    } catch (int e) {
        cout << e;
    }
}

template<typename Obj, typename F1, typename F2>
bool Collection<Obj, F1, F2>::is_empty() const {
    return this->size == 0;
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items() const {
    return this->size;
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items(F1 s) const {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i].get_color() == s) {
            count++;
        }
    }
    return count;
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items(F2 s) const {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i].get_size() == s) {
            count++;
        }
    }
    return count;
}

// Print color & size of an object.
template<typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::print_items() const {
    for (int i = 0; i < this->size; i++) {
        cout << this->array[i] << endl;
    }
}

// Directly access an object in a collection.
// Accesses an object in array at position i where i starts from 0 through size-1.
template<typename Obj, typename F1, typename F2>
Obj &Collection<Obj, F1, F2>::operator[](int i) {
    if (i >= 0 && i < this->size) {
        return this->array[i];
    } else {
        throw runtime_error("Injex out of bounds");
    }
}

// Directly access an object in a const collection.
// Accesses an object in array at position i where i starts from 0 through size-1.
template<typename Obj, typename F1, typename F2>
const Obj &Collection<Obj, F1, F2>::operator[](int i) const {
    if (i >= 0 && i < this->size) {
        return this->array[i];
    } else {
        throw runtime_error("Injex out of bounds");
    }
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::getSize() const {
    return this->size;
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::getCapacity() const {
    return this->capacity;
}


// --------- OUTSIDE OF COLLECTION CLASS -----------


template<typename Obj, typename F1, typename F2>
void swap(Collection<Obj, F1, F2> &c1, Collection<Obj, F1, F2> &c2) {
    Collection<Obj, F1, F2> tmp = move(c1);
    c1 = move(c2);
    c2 = move(tmp);
}

template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_Union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2) {
    int newSize = c1.getSize() + c2.getSize();
    Collection<Obj, F1, F2>* c3 = new Collection<Obj, F1, F2>(newSize);
    for (int i = 0; i < c1.getSize(); i++) {
        c3->insert_item(c1[i]);
    }
    for (int i = 0; i < c2.getSize(); i++) {
        c3->insert_item(c2[i]);
    }
    return *c3;
}

enum class Sort_choice {
    bubble_sort,
    insertion_sort,
    selection_sort
};

template<typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj, F1, F2> &c, Sort_choice sort) {
    int n = c.getSize();
    switch(sort) {
        case Sort_choice::bubble_sort:
            int i, j;
            for (i = 0; i < n-1; i++) {
                for (j = 0; j < n-i-1; j++) {
                    if (c[j].get_size() > c[j+1].get_size()) {
                        Obj tmp = c[j];
                        c[j] = c[j+1];
                        c[j+1] = tmp;
                    }
                }
            }
            break;

        case Sort_choice::insertion_sort:
            for (int k = 1; k < n; k++) {
                Obj tmp = c[k];
                int j = k;
                for (j = k; j > 0 && tmp.get_size() < c[j-1].get_size(); j--) {
                    c[j] = c[j-1];
                }
                c[j] = tmp;
            }
            break;

        case Sort_choice::selection_sort:
            for (int k = 0; k < n-1; k++) {
                int index = k;
                for (int i = k+1; i < n; i++) {
                    if (c[i].get_size() < c[index].get_size()) {
                        index = i;
                    }
                }
                Obj tmp = c[k];
                c[k] = c[index];
                c[index] = tmp;
            }
            break;

        default:
            throw runtime_error("Invalid sort type. Exiting gracefully...");
    }
}

#endif //PROJECTS_COLLECTION_H
