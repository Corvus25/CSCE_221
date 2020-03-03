// test of the DLList class

#include <iostream>
#include <cstdlib>
#include "DLList.h"

using namespace std;

int main() {
    // Construct a linked list with header & trailer
    cout << "Create a new list" << endl;
    DLList dll;
    cout << dll << endl << endl;

    cout << "Insert 10 nodes at back with value 10,20,30,..,100";
    for (int i = 10; i <= 100; i += 10) {
        dll.insert_last(i);
    }
    cout << dll << endl << endl;

    cout << "Insert 10 nodes at front with value 10,20,30,..,100";
    for (int i = 10; i <= 100; i += 10) {
        dll.insert_first(i);
    }
    cout << dll << endl << endl;

    cout << "Copy to a new list";
    DLList dll2(dll); // Copy constructor
    cout << dll2 << endl;

    cout << "Assign to another new list";
    DLList dll3;
    dll3 = dll;
    cout << dll3 << endl << endl;

    cout << "Delete the last 10 nodes of first list";
    for (int i = 0; i < 10; i++) {
        dll.remove_last();
    }
    cout << dll << endl << endl;

    cout << "Delete the first 10 nodes of first list";
    for (int i = 0; i < 10; i++) {
        dll.remove_first();
    }
    cout << dll << endl << endl;

    // Check the other two lists
    cout << "Make sure the other two lists are not affected." << endl;
    cout << "list2: " << dll2 << endl;
    cout << "list3: " << dll3 << endl;

    cout << "More testing on first list..." << endl << endl;
    // Exceptions are thrown if insertion/deletion is not possible. The code below is designed to execute without error
    // just so the program continues to run.
    auto node = dll.first_node()->prev;
    dll.insert_after(*node, 2);
    cout << dll;
    node = dll.first_node();
    dll.insert_after(*node, 4);
    cout << dll;
    dll.insert_before(*node, 5);
    cout << dll;
    node = dll.first_node();
    dll.remove_after(*node);
    cout << dll;
    node = dll.after_last_node()->prev;
    dll.remove_before(*node);
    cout << dll;

    // Testing traversing backwards
    cout << "test traverse backwards" << endl;
    cout << "Add nodes 1-5";
    for (int i = 0; i < 3; i++) {
        dll.insert_last(i+1);
    }

    cout << dll << endl;
    node = dll.after_last_node()->prev;
    while (node != nullptr) {
        cout << node << endl;
        node = node->prev;
    }
    cout << endl;

//     Move constructor - moving dll to dll4
    cout << "dll: " << dll;
    cout << "Moving dll to dll4..." << endl;
    DLList dll4(move(dll));
    cout << "dll: " << dll;
    cout << "dll4: " << dll4;


    // Move assignment - moving dll to dll5
    cout << "Moving dll4 to dll5..." << endl;
    DLList dll5;
    dll5 = move(dll4);
    cout << "dll4: " << dll4;
    cout << "dll5: " << dll5;

    return 0;
}
