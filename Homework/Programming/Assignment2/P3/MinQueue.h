#ifndef MINQUEUE_H
#define MINQUEUE_H

#include <iostream>
#include "TemplatedDLList.h"
using namespace std;

// extend runtime_error from <stdexcept>
template<typename T>
struct QueueEmptyException : public std::runtime_error {
    explicit QueueEmptyException<T>(char const *msg = nullptr) : runtime_error(msg) {}
};

template<typename T>
class LinkedQueue {
private:
    TemplatedDLList<T> tdll; // internal TemplatedDLList object
    unsigned int sz {0};
public:
    bool is_empty() const { return tdll.is_empty(); }
    void enqueue(int elem) { sz++; tdll.insert_last(elem); }
    int dequeue();
    int size() { return sz; }
    T min();

    string to_str() const;
};

//template<typename T>
//int LinkedQueue<T>::size() {
//    auto *curr = tdll.first_node();
//    int size = 0;
//    while (curr != tdll.after_last_node()) {
//        curr = curr->next;
//        size++;
//    }
//    return size;
//}

template<typename T>
T LinkedQueue<T>::min() {
    if (tdll.is_empty()) {
        throw QueueEmptyException<T>("Access to an empty queue");
    }
    auto curr = tdll.first_node();
    int min = curr->obj;
    for (int i = 0; i < size(); i++) {
        if (curr->obj < min) {
            min = curr->obj;
        }
        curr = curr->next;
    }
    return min;
}

template<typename T>
int LinkedQueue<T>::dequeue() {
    if (tdll.is_empty()) {
        throw QueueEmptyException<T>("Access to an empty queue");
    }
    sz--;
    return tdll.remove_first();
}

// Helper function to format the output
template<typename T>
std::string LinkedQueue<T>::to_str() const {
    std::stringstream os;
    os << endl;
    os << "First =>";
    auto curr = tdll.first_node();
    if (curr->next == NULL) {
//        throw QueueEmptyException<T>("Access to an empty queue");
//      Not really needed... just making sure curr->next isn't called if it doesn't exist.
    } else {
        os << std::setw(5) << curr->obj;
        curr = curr->next;
    }
    while (curr->next) {
        os << std::setw(4) <<  "=>" << std::setw(3) << curr->obj;
        curr = curr->next;
    }
    os << std::setw(12) << "<= Last";
    os << endl;
    return os.str();
}

// output operator
template<typename T>
ostream &operator<<(ostream &out, const LinkedQueue<T> &queue) {
    out << queue.to_str();
    return out;
}

#endif
