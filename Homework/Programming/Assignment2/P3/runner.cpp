#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <sstream>
#include "MinQueue.h"
#include "TemplatedDLList.h"

int main() {

    LinkedQueue<int> test;
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    cout << test;
    cout << "Is empty? " << test.is_empty() << endl;
    cout << "Size: " << test.size() << endl;
    cout << "Min: " << test.min() << endl;

    test.dequeue();
    cout << test;
    cout << "Is empty? " << test.is_empty() << endl;
    cout << "Size: " << test.size() << endl;
    cout << "Min: " << test.min() << endl;

    test.dequeue();
    test.dequeue();
    test.dequeue();
    test.dequeue();
    cout << test;
    cout << "Is empty? " << test.is_empty() << endl;
    cout << "Size: " << test.size() << endl;
    cout << "Min: " << test.min() << endl;
    return 0;
}