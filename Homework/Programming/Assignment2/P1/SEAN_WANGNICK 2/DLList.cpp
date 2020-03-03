// implementation of the DLList class

#include <stdexcept>
#include "DLList.h"
#include <sstream>
#include <iomanip>
#include <iostream>


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
    explicit EmptyDLList(char const *msg = nullptr) : runtime_error(msg) {}
};
struct InvalidInsertion : public std::runtime_error {
    explicit InvalidInsertion(char const *msg = nullptr) : runtime_error(msg) {}
};
struct InvalidRemoval : public std::runtime_error {
    explicit InvalidRemoval(char const *msg = nullptr) : runtime_error(msg) {}
};
struct PointerInvalid : public std::runtime_error {
    explicit PointerInvalid(char const *msg = nullptr) : runtime_error(msg) {}
};

// copy constructor
DLList::DLList(const DLList &dll) {
    // Initialize the list
    header.next = &trailer;
    trailer.prev = &header;

    DLListNode *curr = dll.header.next;
    while (curr != dll.after_last_node()) {
        this->insert_last(curr->obj);
        curr = curr->next;
    }
}

// copy assignment operator
DLList &DLList::operator=(const DLList &dll) {
    if (this != &dll) {
        // Clear DLL
        DLListNode *curr = header.next;
        while (curr != &trailer) {
            DLListNode *next = curr->next;
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
DLList::DLList(DLList &&dll) {
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
DLList &DLList::operator=(DLList &&dll) {
    // Destruct
    DLListNode *prev_node, *node = header.next;
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
DLList::~DLList() { // From Slides
    DLListNode *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// insert a new object as the first one
void DLList::insert_first(int obj) { // From Slides
    DLListNode *newNode = new DLListNode(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert a new object as the last one
void DLList::insert_last(int obj) { // From Slides
    DLListNode *newNode = new DLListNode(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first node from the list
int DLList::remove_first() { // From Slides
    if (this->is_empty()) {
        throw EmptyDLList("Empty Doubly Linked List");
    }
    DLListNode *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    int obj = node->obj;
    delete node;
    return obj;
}

// remove the last node from the list
int DLList::remove_last() { // From Slides
    if (this->is_empty()) {
        throw EmptyDLList("Empty Double Linked List");
    }
    DLListNode *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    int obj = node->obj;
    delete node;
    return obj;
}

// return the first object (do not remove)
int DLList::first() const { // From Slides
    if (this->is_empty()) {
        throw EmptyDLList("Empty Doubly Linked List");
    }
    return header.next->obj;
}

// return the last object (do not remove)
int DLList::last() const { // From Slides
    if (this->is_empty()) {
        throw EmptyDLList("Empty Doubly Linked List");
    }
    return trailer.prev->obj;
}

// insert a new node after the node p
void DLList::insert_after(DLListNode &p, int obj) {
    if (&p == nullptr) {
        throw PointerInvalid("Invalid. Pointer = nullptr");
    }
    if (p.next == nullptr || p.prev == &trailer) {
        throw InvalidInsertion("Invalid Insertion. Index out of bounds.");
    }
    DLListNode *tmp = p.next;
    DLListNode *node = new DLListNode;
    node->obj = obj;
    p.next = node;
    node->next = tmp;
    tmp->prev = node;
    node->prev = &p;
}

// insert a new node before the node p
void DLList::insert_before(DLListNode &p, int obj) {
    if (&p == nullptr) {
        throw PointerInvalid("Invalid. Pointer = nullptr");
    }
    if (p.prev == nullptr || p.next == &header) {
        throw InvalidInsertion("Invalid Insertion. Index out of bounds.");
    }
    DLListNode *tmp = p.prev;
    DLListNode *node = new DLListNode;
    node->obj = obj;
    p.prev = node;
    node->prev = tmp;
    tmp->next = node;
    node->next = &p;
}

// remove the node after the node p
int DLList::remove_after(DLListNode &p) {
    if (this->is_empty()) {
        throw EmptyDLList("Empty Doubly Linked List");
    }
    if (&p == nullptr) {
        throw PointerInvalid("Invalid. Pointer = nullptr");
    }
    if (&p == &trailer || p.next->next == nullptr) {
        throw InvalidRemoval("Invalid Removal. Index out of bounds.");
    }
    DLListNode *tmp = p.next->next;
    DLListNode *toDelete = p.next;
    toDelete->prev = nullptr;
    toDelete->next = nullptr;
    tmp->prev = &p;
    p.next = tmp;
    int val = toDelete->obj;
    delete toDelete;
    return val;
}

// remove the node before the node p
int DLList::remove_before(DLListNode &p) {
    if (this->is_empty()) {
        throw EmptyDLList("Empty Doubly Linked List");
    }
    if (&p == nullptr) {
        throw PointerInvalid("Invalid. Pointer = nullptr");
    }
    if (&p == &header || p.prev->prev == nullptr) {
        throw InvalidRemoval("Invalid Removal. Index out of bounds.");
    }
    DLListNode *tmp = p.prev->prev;
    DLListNode *toDelete = p.prev;
    toDelete->prev = nullptr;
    toDelete->next = nullptr;
    tmp->next = &p;
    p.prev = tmp;
    int val = toDelete->obj;
    delete toDelete;
    return val;
}

// Helper function to format the output
std::string DLList::to_str() const {
    std::stringstream os;
    const DLListNode *curr = &header;
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
ostream &operator<<(ostream &out, const DLList &dll) {
    out << dll.to_str();
    return out;
}
