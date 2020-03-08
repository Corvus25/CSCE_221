// header file for the templated DLList

#ifndef TEMPLATEDDLList_H
#define TEMPLATEDDLList_H

#include <iostream>
using namespace std;

// extend runtime_error from <stdexcept>
template<typename T>
struct EmptyTemplatedDLList : public std::runtime_error {
    explicit EmptyTemplatedDLList<T>(char const *msg = nullptr) : runtime_error(msg) {}
};
template<typename T>
struct InvalidInsertion : public std::runtime_error {
    explicit InvalidInsertion<T>(char const *msg = nullptr) : runtime_error(msg) {}
};
template<typename T>
struct InvalidRemoval : public std::runtime_error {
    explicit InvalidRemoval<T>(char const *msg = nullptr) : runtime_error(msg) {}
};
template<typename T>
struct PointerInvalid : public std::runtime_error {
    explicit PointerInvalid<T>(char const *msg = nullptr) : runtime_error(msg) {}
};

template<typename T>
class TemplatedDLList; // class declaration

// doubly linked list node
template<typename T>
struct TemplatedDLListNode {
    T obj;
    TemplatedDLListNode *prev, *next;

    // constructor
    TemplatedDLListNode(T e = {}, TemplatedDLListNode *p = nullptr, TemplatedDLListNode *n = nullptr)
            : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template<typename T>
class TemplatedDLList {
private:
    TemplatedDLListNode<T> header, trailer;
    unsigned int sz;
public:

    TemplatedDLList<T>() : header(), trailer() { // default constructor
        header.next = &trailer;
        trailer.prev = &header;
    }

    TemplatedDLList<T>(const TemplatedDLList<T> &dll); // copy constructor
    TemplatedDLList<T>(TemplatedDLList<T> &&dll); // move constructor
    ~TemplatedDLList(); // destructor
    unsigned int size() const { return sz; }
    TemplatedDLList<T> &operator=(const TemplatedDLList<T> &dll); // copy assignment operator
    TemplatedDLList<T> &operator=(TemplatedDLList<T> &&dll); // move assignment operator
    // return the pointer to the first node
    TemplatedDLListNode<T> *first_node() const { return header.next; }

    // return the pointer to the trailer
    const TemplatedDLListNode<T> *after_last_node() const { return &trailer; }

    // return if the list is empty
    bool is_empty() const { return header.next == &trailer; }

    T first() const; // return the first object
    T last() const; // return the last object
    void insert_first(T obj); // insert to the first node
    T remove_first(); // remove the first node
    void insert_last(T obj); // insert to the last node
    T remove_last(); // remove the last node
    void insert_after(TemplatedDLListNode<T> &p, T obj);
    void insert_before(TemplatedDLListNode<T> &p, T obj);
    T remove_after(TemplatedDLListNode<T> &p);
    T remove_before(TemplatedDLListNode<T> &p);

    std::string to_str() const;
};

// output operator
template<typename T>
ostream &operator<<(ostream &out, const TemplatedDLList<T> &dll);



////////////////////////////////////////////////////////
/////           TemplatedDLList Class Definitions           /////
////////////////////////////////////////////////////////
// copy constructor
template<typename T>
TemplatedDLList<T>::TemplatedDLList(const TemplatedDLList<T> &dll) {
    // Initialize the list
    header.next = &trailer;
    trailer.prev = &header;

    TemplatedDLListNode<T> *curr = dll.header.next;
    while (curr != dll.after_last_node()) {
        this->insert_last(curr->obj);
        curr = curr->next;
    }
}

// copy assignment operator
template<typename T>
TemplatedDLList<T> &TemplatedDLList<T>::operator=(const TemplatedDLList<T> &dll) {
    if (this != &dll) {
        // Clear DLL
        TemplatedDLListNode<T> *curr = header.next;
        while (curr != &trailer) {
            TemplatedDLListNode<T> *next = curr->next;
            delete curr;
            curr = next;
        }

        // Copy DLL
        curr = dll.header.next;
        while (curr->next) {
            this->insert_last(curr->obj);
            curr = curr->next;
        }
    }
    return *this;
}

// move constructor
template<typename T>
TemplatedDLList<T>::TemplatedDLList(TemplatedDLList<T> &&dll) {
    header.next = &trailer;
    trailer.prev = &header;

    if (!dll.is_empty()) {
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;

        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
}

// move assignment operator
template<typename T>
TemplatedDLList<T> &TemplatedDLList<T>::operator=(TemplatedDLList<T> &&dll) {
    // Destruct
    TemplatedDLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }

    header.next = &trailer;
    trailer.prev = &header;

    if (!dll.is_empty()) {
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;

        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
    return *this;
}

// destructor
template<typename T>
TemplatedDLList<T>::~TemplatedDLList() { // From Slides
    TemplatedDLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// insert a new object as the first one
template<typename T>
void TemplatedDLList<T>::insert_first(T obj) { // From Slides
    TemplatedDLListNode<T> *newNode = new TemplatedDLListNode<T>(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert a new object as the last one
template<typename T>
void TemplatedDLList<T>::insert_last(T obj) { // From Slides
    TemplatedDLListNode<T> *newNode = new TemplatedDLListNode<T>(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first node from the list
template<typename T>
T TemplatedDLList<T>::remove_first() { // From Slides
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Doubly Linked List");
    }
    TemplatedDLListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
}

// remove the last node from the list
template<typename T>
T TemplatedDLList<T>::remove_last() { // From Slides
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Double Linked List");
    }
    TemplatedDLListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T obj = node->obj;
    delete node;
    return obj;
}

// return the first object (do not remove)
template<typename T>
T TemplatedDLList<T>::first() const { // From Slides
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Doubly Linked List");
    }
    return header.next->obj;
}

// return the last object (do not remove)
template<typename T>
T TemplatedDLList<T>::last() const { // From Slides
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Doubly Linked List");
    }
    return trailer.prev->obj;
}

// insert a new node after the node p
template<typename T>
void TemplatedDLList<T>::insert_after(TemplatedDLListNode<T> &p, T obj) {
    if (&p == nullptr) {
        throw PointerInvalid<T>("Invalid. Pointer = nullptr");
    }
    if (p.next == nullptr || p.prev == &trailer) {
        throw InvalidInsertion<T>("Invalid Insertion. Index out of bounds.");
    }
    TemplatedDLListNode<T> *tmp = p.next;
    TemplatedDLListNode<T> *node = new TemplatedDLListNode<T>;
    node->obj = obj;
    p.next = node;
    node->next = tmp;
    tmp->prev = node;
    node->prev = &p;
}

// insert a new node before the node p
template<typename T>
void TemplatedDLList<T>::insert_before(TemplatedDLListNode<T> &p, T obj) {
    if (&p == nullptr) {
        throw PointerInvalid<T>("Invalid. Pointer = nullptr");
    }
    if (p.prev == nullptr || p.next == &header) {
        throw InvalidInsertion<T>("Invalid Insertion. Index out of bounds.");
    }
    TemplatedDLListNode<T> *tmp = p.prev;
    TemplatedDLListNode<T> *node = new TemplatedDLListNode<T>;
    node->obj = obj;
    p.prev = node;
    node->prev = tmp;
    tmp->next = node;
    node->next = &p;
}

// remove the node after the node p
template<typename T>
T TemplatedDLList<T>::remove_after(TemplatedDLListNode<T> &p) {
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Doubly Linked List");
    }
    if (&p == nullptr) {
        throw PointerInvalid<T>("Invalid. Pointer = nullptr");
    }
    if (&p == &trailer || p.next->next == nullptr) {
        throw InvalidRemoval<T>("Invalid Removal. Index out of bounds.");
    }
    TemplatedDLListNode<T> *tmp = p.next->next;
    TemplatedDLListNode<T> *toDelete = p.next;
    toDelete->prev = nullptr;
    toDelete->next = nullptr;
    tmp->prev = &p;
    p.next = tmp;
    T val = toDelete->obj;
    delete toDelete;
    return val;
}

// remove the node before the node p
template<typename T>
T TemplatedDLList<T>::remove_before(TemplatedDLListNode<T> &p) {
    if (this->is_empty()) {
        throw EmptyTemplatedDLList<T>("Empty Doubly Linked List");
    }
    if (&p == nullptr) {
        throw PointerInvalid<T>("Invalid. Pointer = nullptr");
    }
    if (&p == &header || p.prev->prev == nullptr) {
        throw InvalidRemoval<T>("Invalid Removal. Index out of bounds.");
    }
    TemplatedDLListNode<T> *tmp = p.prev->prev;
    TemplatedDLListNode<T> *toDelete = p.prev;
    toDelete->prev = nullptr;
    toDelete->next = nullptr;
    tmp->next = &p;
    p.prev = tmp;
    T val = toDelete->obj;
    delete toDelete;
    return val;
}

// Helper function to format the output
template<typename T>
std::string TemplatedDLList<T>::to_str() const {
    std::stringstream os;
    const TemplatedDLListNode<T> *curr = &header;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "header: " << &header << std::endl;
    os << "trailer: " << &trailer << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    os << std::setw(16) << curr << std::setw(16) << curr->prev << std::setw(16) << curr->obj <<  std::setw(16) << curr->next << "\t<< Header" << std::endl;
    curr = curr->next;
    while (curr->next) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->obj;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setw(16) << curr << std::setw(16) << curr->prev << std::setw(16) << curr->obj <<  std::setw(16) << curr->next << "\t<< Trailer" << std::endl;
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

// output operator
template<typename T>
ostream &operator<<(ostream &out, const TemplatedDLList<T> &dll) {
    out << dll.to_str();
    return out;
}


#endif
