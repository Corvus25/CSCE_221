#include "Collection.h"
#include "Stress_ball.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

// Default Constructor
Collection::Collection() {
    size = 0;
    capacity = 0;
    array = nullptr;
}

// Single-Argument constructor
Collection::Collection(int sz) : capacity(sz) {
    capacity = sz;
    size = 0;
    array = new Stress_ball[sz];
}

// Copy Constructor
Collection::Collection(const Collection& orig) {
    this->capacity = orig.capacity;
    this->size = orig.size;

    Stress_ball *newAry = new Stress_ball[capacity];
    for (int i = 0; i < size; i++) {
        newAry[i] = orig.array[i];
    }
//    delete[] this->array;
    this->array = newAry;
}

// Copy Assignment operator
Collection &Collection::operator=(const Collection& orig) {
    if (&orig == this) {
        return *this;
    }

    // Copy the resource
    this->capacity = orig.capacity;
    this->size = orig.size;

    Stress_ball *newAry = new Stress_ball[capacity];
    for (int i = 0; i < size; i++) {
        newAry[i] = orig.array[i];
    }
    delete[] this->array;
    this->array = newAry;

    return *this;
}

// Destructor
Collection::~Collection() {
    make_empty();
}

// Move constructor
Collection::Collection(Collection&& orig) {
    array = orig.array;
    size = orig.size;
    capacity = orig.capacity;

    orig.array = nullptr;
    orig.size = 0;
    orig.capacity = 0;
}

// Move assignment operator
Collection &Collection::operator=(Collection&& orig) {
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

void Collection::insert_item(const Stress_ball &sb) {
    if (this->size == this->capacity) {
        resize();
    }
    this->array[size] = sb;
    this->size++;
}

void Collection::resize() {
    if (this->capacity == 0) {
        int newCapacity = 1;
        Stress_ball *newAry = new Stress_ball[newCapacity];
        this->array = newAry;
        this->capacity = newCapacity;
    } else {
        int newCapacity = this->capacity * 2;
        Stress_ball *newAry = new Stress_ball[newCapacity];
        for (int i = 0; i < this->size; i++) {
            newAry[i] = this->array[i];
        }
        delete[] this->array;
        this->array = newAry;
        this->capacity = newCapacity;
    }
}

bool Collection::contains(const Stress_ball &sb) const {
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == sb) {
            return true;
        }
    }
    return false;
}

// Do not decrease the 'capacity' of the array.
// Be sure there are no gaps between elements of the array.
// Throw an exception if the collection is already empty.
Stress_ball Collection::remove_any_item() {
    srand(time(NULL));
    if (this->size == 0) {
        throw runtime_error("Collection is already empty. Unable to remove Stress Ball.");
    }
    int randIndex = rand() % this->size;
    Stress_ball a = Stress_ball(this->array[randIndex]);
    for (int i = randIndex; i < this->size-1; i++) {
        this->array[i] = this->array[i+1];
    }
    this->size--;
    return a;
}

// Do not decrease the 'capacity' of the array.
// Be sure there are no gaps between elements of the array.
// Throw an exception if the collection is already empty.
void Collection::remove_this_item(const Stress_ball& sb) {
    if (this->size == 0) {
        throw runtime_error("Collection is already empty. Unable to remove Stress Ball.");
    }
    int index;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == sb) {
            index = i;
            break;
        }
    }

    for (int i = index; i < this->size-1; i++) {
        this->array[i] = this->array[i+1];
    }
    this->size--;
}

// Deallocate memory, set size & capacity to 0.
void Collection::make_empty() {
    try {
        this->size = 0;
        this->capacity = 0;
        delete[] this->array;
        array = nullptr;
    } catch (int e) {
        cout << e;
    }
}

bool Collection::is_empty() const {
    return this->size == 0;
}

int Collection::total_items() const {
    return this->size;
}

int Collection::total_items(Stress_ball_sizes s) const {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i].get_size() == s) {
            count++;
        }
    }
    return count;
}

int Collection::total_items(Stress_ball_colors t) const {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i].get_color() == t) {
            count++;
        }
    }
    return count;
}

// Print color & size of a stress ball, see Stress_ball class.
void Collection::print_items() const {
    for (int i = 0; i < this->size; i++) {
        cout << this->array[i] << endl;
    }
}

// Directly access a stress ball in a collection.
// Accesses a stress ball in array at position i where i starts from 0 through size-1.
Stress_ball &Collection::operator[](int i) {
    if (i >= 0 && i < this->size) {
        return this->array[i];
    } else {
        throw runtime_error("Index out of bounds");
    }
}

// Directly access a stress ball in a const collection.
// Accesses a stress ball in array at position i where i starts from 0 through size-1.
const Stress_ball &Collection::operator[](int i) const {
    if (i >= 0 && i < this->size) {
        return this->array[i];
    } else {
        throw runtime_error("Index out of bounds");
    }
}

int Collection::getSize() const {
    return this->size;
}

int Collection::getCapacity() const {
    return this->capacity;
}

// --------- OUTSIDE OF COLLECTION CLASS -----------

istream &operator>>(istream &is, Collection &c) {

    map<string, Stress_ball_colors> convert_color;
    map<string, Stress_ball_sizes> convert_size;

    convert_color["red"] = Stress_ball_colors::red;
    convert_color["blue"] = Stress_ball_colors::blue;
    convert_color["yellow"] = Stress_ball_colors::yellow;
    convert_color["green"] = Stress_ball_colors::green;
    convert_size["small"] = Stress_ball_sizes ::small;
    convert_size["medium"] = Stress_ball_sizes ::medium;
    convert_size["large"] = Stress_ball_sizes ::large;

    string line;

    do {
        string color;
        string size;

        is >> color >> size;
        Stress_ball_colors cl = convert_color[color];
        Stress_ball_sizes sz = convert_size[size];
        Stress_ball sb = Stress_ball(cl, sz);
        c.insert_item(sb);

    } while (!is.eof());

    return is;
}

ostream &operator<<(ostream &os, const Collection &c) {

    map<Stress_ball_colors, string> convert_color;
    map<Stress_ball_sizes, string> convert_size;

    convert_color[Stress_ball_colors::red] = "red";
    convert_color[Stress_ball_colors::blue] = "blue";
    convert_color[Stress_ball_colors::yellow] = "yellow";
    convert_color[Stress_ball_colors::green] = "green";
    convert_size[Stress_ball_sizes::small] = "small";
    convert_size[Stress_ball_sizes::medium] = "medium";
    convert_size[Stress_ball_sizes::large] = "large";

    for (int i = 0; i < c.getSize(); i++) {
        os << "(" << convert_color[c[i].get_color()] << ", " << convert_size[c[i].get_size()] << ")" << endl;
    }
    return os;
}

Collection make_Union(const Collection &c1, const Collection &c2) {
    int newSize = c1.getSize() + c2.getSize();
    Collection* c3 = new Collection(newSize);
    for (int i = 0; i < c1.getSize(); i++) {
        c3->insert_item(c1[i]);
    }
    for (int i = 0; i < c2.getSize(); i++) {
        c3->insert_item(c2[i]);
    }
    return *c3;
}

void swap(Collection &c1, Collection &c2) {
    Collection tmp = move(c1);
    c1 = move(c2);
    c2 = move(tmp);
}

void sort_by_size(Collection &c, Sort_choice sort) {
    int n = c.getSize();
    switch(sort) {
        case Sort_choice::bubble_sort:
            int i, j;
            for (i = 0; i < n-1; i++) {
                for (j = 0; j < n-i-1; j++) {
                    if (c[j].get_size() > c[j+1].get_size()) {
                        Stress_ball tmp = c[j];
                        c[j] = c[j+1];
                        c[j+1] = tmp;
                    }
                }
            }
            break;

        case Sort_choice::insertion_sort:
            for (int k = 1; k < n; k++) {
                Stress_ball tmp = c[k];
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
                Stress_ball tmp = c[k];
                c[k] = c[index];
                c[index] = tmp;
            }
            break;

        default:
            throw runtime_error("Invalid sort type. Exiting gracefully...");
    }
}
