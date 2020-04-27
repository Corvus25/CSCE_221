#include "graph.h"
#include "string"
#include "iostream"
using namespace std;

Graph::~Graph() {
    // Only need to destruct list pointers in adj_list
    for (auto &i : this->adj_list) {
        delete i;
        i = nullptr;
    }
}

void Graph::buildGraph(ifstream &input) {
    string line;
    vector<list<int> *> build_list;
    vector<Vertex> build_vertex_list;
    int iteration = 0;

    while (getline(input, line)) {

        // For each line in the file, add an empty list to adjacency_list
        auto *sequence = new list<int>;
        build_list.push_back(sequence);

        // Push elements in the line onto the list
        for (char elem : line) {
            if (elem == 45) { // Reaches negative value
                break;
            }
            if (elem != 32) { // Check that it's not a space
                build_list[iteration]->push_back(atoi(&elem));
            }
        }
        iteration++;
    }

    // Add heads of each list to the node_list
    for (auto i : build_list) {
        auto *v = new Vertex(*i->begin(), 0);
        build_vertex_list.push_back(*v);
        delete v; // destruct immediately here
    }

    // Reassign temporary vectors to class objects
    this->adj_list = build_list;
    this->node_list = build_vertex_list;
}

void Graph::displayGraph() {
    for (auto node : this->adj_list) {
        cout << *node->begin() << " :";
        for (auto ext : *node) {
            if (ext != *node->begin()) {
                cout << " " << ext;
            }
        }
        cout << endl;
    }
}