// Sean Wangnick
// swangnick@tamu.edu
// Section 505

#pragma once
#include <list>
#include <iostream>
#include <utility>
using namespace std;

template<typename T>
class HashTable {
private:
	int size{};
	vector<list<pair<int, T>>> *table;

    int hash(const int _key) {
        // h(x) = x % m
        return _key % size;
    }

public:
    HashTable(const int _size) {
		this->size = _size;
		table = new vector<list<pair<int, T>>>[size];

		for (int i = 0; i < size; i++) {
		    auto *spot = new list<pair<int, T>>;
            table->push_back(*spot);
		}
    }

	~HashTable() {
        delete[] table;
        table = nullptr;
	}

	// Place new element at end
    void insert(const int _key, T _value) {
		int index = hash(_key);
		pair<int, T> p1(_key, _value);
		table->at(index).push_back(p1);
    }

    // Will include empty chains
	int minChainLen() {
        // The highest chain length can be no greater than the # of students
        int min = table->size();

        for (int i = 0; i < table->size(); i++) {
		    int listLength = table->at(i).size();
		    if (listLength < min) {
		        min = listLength;
		    }
		}
        return min;
	}

    // Will include empty chains
	int maxChainLen() {
        int max = 0;

		for (int i = 0; i < table->size(); i++) {
		    int listLength = table->at(i).size();
		    if (listLength > max) {
		        max = listLength;
		    }
		}
		return max;
	}

    // Will include empty chains
	double averageChainLen() {
        double total = 0;
        double avg = 0;

        for (int i = 0; i < table->size(); i++) {
            total += table->at(i).size();
        }
        avg = total / table->size();
        return avg;
    }

	// Select the linked list and search for an element in the linked list
	// Return a pointer to the grade string
    T* search(int _key) {
        int index = hash(_key);
        auto resultList = table->at(index);

        // Find pair
        for (auto &p : resultList) {
            if (p.first == _key) {
                return &p.second;
            }
        }
        return nullptr;
    }

};
