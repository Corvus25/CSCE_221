#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
    int search_time; //see the problem description

    // Node constructor
    Node(int val = 0, Node *l = nullptr, Node *r = nullptr)
            : value(val), left(l), right(r), search_time(0) {}
};

class BSTree {
public:
    BSTree() : size(0), root(nullptr) {}  // default constructor

    BSTree(const BSTree &other);  // copy constructor
    BSTree(BSTree &&other);  // move constructor

    BSTree& operator=(const BSTree &other);  // copy assignment
    BSTree& operator=(BSTree &&other);  // move assignment

    ~BSTree();  // destructor

    const Node *get_root() const { return root; }
    const int get_size() const { return size; }

    Node *insert(int obj);
    Node *search(int obj);

    void update_search_times();
    int get_total_search_time(Node *node);
    float get_average_search_time();

    ostream &inorder(ostream &out);
    ostream &print_level_by_level(ostream &out);

    void pretty_print_node(ostream &out, Node *node);

    void deleteTree(const Node *root);

private:
    int size;
    Node *root;

    // you may need helper functions to be called recursively
    // this is one example:
    void copy_helper(Node *copy_to, const Node *copy_from) const;
    void printInOrder(Node *node, ostream &out);
    void getSearchTime(Node *root);
    void searchTime(Node *root, int level);
    int height(Node *node);
};

// print a BSTree
ostream &operator<<(ostream &out, BSTree &tree);

// print a node
ostream &operator<<(ostream &out, Node node);

// read in a tree from a file
istream &operator>>(istream &in, BSTree &tree);


#endif
