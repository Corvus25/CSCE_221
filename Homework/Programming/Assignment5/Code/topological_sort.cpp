// topological sort

#include <iostream>
#include <queue>
#include "graph.h"

void Graph::compute_indegree() {
    for (auto each : this->adj_list) {
        bool first = true;
        for (auto node : *each) {
            if (!first) {
                this->node_list[node-1].indegree++;
            }
            first = false;
        }
    }
}

void Graph::topological_sort() {
    queue<Vertex> q;
    int counter = 0;
//    vector<Vertex> top_order;

    // Ensure the queue is empty, then queue vertices with indegree 0
    queue<Vertex> empty;
    swap(q, empty);
    for (auto vertex : this->node_list) {
        if (vertex.indegree == 0) {
            q.push(vertex);
        }
    }

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        v.top_num = ++counter; // Assign next number

        for (auto adj : *this->adj_list[v.label - 1]) {
            if (adj != v.label) {
                if (--node_list[adj - 1].indegree == 0) {
                    q.push(node_list[adj - 1]);
                }
            }
        }

        node_list[v.label - 1] = v;

    }

    try {
        if (counter != node_list.size()) {
            throw exception();
        }
    }
    catch (exception) {
        cout << "There are cycles in the graph";
        exit(1);
    }
}

void Graph::print_top_sort() {
    int level = 1;
    while (level != this->node_list.size() + 1) {
        for (auto node : this->node_list) {
            if (node.top_num == level) {
                cout << node.label << " ";
                break; // Slightly increase efficiency
            }
        }
        level++;
    }
    cout << endl;
}
