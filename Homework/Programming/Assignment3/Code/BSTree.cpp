#include "BSTree.h"
#include <queue>

// input / output operators
ostream &operator<<(ostream &out, BSTree &tree) {
    tree.update_search_times();
    tree.print_level_by_level(out);
    return out;
}

ostream &operator<<(ostream &out, Node node) {
    return out << "( " << node.value << ", "
               << node.search_time << " )";
}

istream &operator>>(istream &in, BSTree &tree) {
    /*
      take input from the in stream, and build your tree
      input will look like
      4
      2
      6
      1
      3
      5
      7
    */
    int next;
    while (in >> next)
        tree.insert(next);
    return in;
}

///////////// Implementation To Do ////////////////////

// copy constructor
BSTree::BSTree(const BSTree &other) {
    /*
      complete this copy constructor
      make sure when copying nodes to copy
      the value and left and right children
    */
    // basically copy_helper + a little more
    this->root = new Node(other.root->value);
    this->size = other.size;
    this->root->search_time = other.root->search_time;
    copy_helper(this->root, other.root);
    // must be a deep copy (something like this->root = new Node(other->root->value);)
}

//copy assignment
BSTree& BSTree::operator=(const BSTree &other) {
    /*
      complete this assignment operator
      make sure when copying nodes to copy
      the value
      and left and right children
      not important for this part but will be used later
    */
    if (this != &other) {
        // Clear this
        deleteTree(root);
        root = new Node(other.root->value);

        // Copy this
        this->size = other.size;
        this->root->search_time = other.root->search_time;
        copy_helper(this->root, other.root);
    }
    return *this;
}

// move constructor
BSTree::BSTree(BSTree &&other) {
    // Reassign the roots + some other details
    if (other.size <= 0) {
        return;
    }

    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;
}

// move assignment
BSTree& BSTree::operator=(BSTree &&other) {
    // Destruct first

    if (this != &other) {
        // Clear this
        deleteTree(root);
        root = other.root;

        // Copy this
        size = other.size;

        other.root = nullptr;
        other.size = 0;
    }
    return *this;
}

// destructor
BSTree::~BSTree() {
    // use a helper function
    deleteTree(root);
    root = nullptr;
}

// recursive
void BSTree::copy_helper(Node *copy_to, const Node *copy_from) const {
    if (copy_from == nullptr)
        return;

    if (copy_from->left != nullptr) {
        copy_to->left = new Node(*copy_from->left);
        copy_helper(copy_to->left, copy_from->left);
    } else {
        copy_to->left = nullptr;
    }

    if (copy_from->right != nullptr) {
        copy_to->right = new Node(*copy_from->right);
        copy_helper(copy_to->right, copy_from->right);
    } else {
        copy_to->right = nullptr;
    }
}

void BSTree::deleteTree(const Node *node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
    node = nullptr;
}

Node *BSTree::insert(int obj) {
    /*
      insert a node into the tree
      first find where the node should go
      then modify pointers to connect your new node
    */

    // depthTracker is the old method of updating search_time during insertion
    // before the implementation of update_search_times().

//    int depthTracker = 2;

    if (root == nullptr) {
        root = new Node(obj);
        this->size++;
        return root;
    }

    Node* current = root;
    while (current) {
        if (obj <= current->value) {
            if (current->left == nullptr) {
                current->left = new Node(obj);
//                current->left->search_time = depthTracker;
                this->size++;
                return root;
            } else {
                current = current->left;
//                depthTracker++;
            }
        }
        if (obj > current->value) {
            if (current->right == nullptr) {
                current->right = new Node(obj);
//                current->right->search_time = depthTracker;
                this->size++;
                return root;
            } else {
                current = current->right;
//                depthTracker++;
            }
        }
    }
    return root;
}

Node *BSTree::search(int obj) {
    /*
      recursively search down the tree to find the node that contains obj
      if you dont find anything return null
    */
    if (root == nullptr) {
        return nullptr;
    }

    Node* current = root;
    while (current) {
        if(obj < current->value) {
            if (current->left == nullptr) {
                return nullptr;
            } else {
                current = current->left;
            }
        }
        if(obj > current->value) {
            if (current->right == nullptr) {
                return nullptr;
            } else {
                current = current->right;
            }
        }
        if(obj == current->value) {
            return current;
        }
    }
    return nullptr;
}

int BSTree::height(Node *node) {
    if (node == nullptr) {
        return 0;
    } else {
        int lheight = height(node->left);
        int rheight = height(node->right);

        if (lheight > rheight) {
            return (lheight + 1);
        } else {
            return (rheight + 1);
        }
    }
}

void BSTree::searchTime(Node *node, int level) {
    if (node == nullptr)
        return;
    if (level == 1) {
        node->search_time = -1 * (height(node) - height(root)) + 1;
    }
    else if (level > 1)
    {
        searchTime(node->left, level-1);
        searchTime(node->right, level-1);
    }
}

void BSTree::getSearchTime(Node *root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        searchTime(root, i);
    }
}

void BSTree::update_search_times() {
    /*
      do a BFS or DFS of your tree and update the search times of all nodes
    */
    getSearchTime(root);
}

void BSTree::printInOrder(Node* node, ostream &out) {
    if (node == nullptr) {
        return;
    }
    // First left node, then node's value, then right node
    printInOrder(node->left, out);
    out << node->value << " ";
    printInOrder(node->right, out);
}

ostream &BSTree::inorder(ostream &out) {
    /*
      print your nodes in infix order
      if our tree looks like

      4
      2 6
      1 3 5 7

      we should get

      1 2 3 4 5 6 7
    */
    printInOrder(this->root, out);
    return out;
}

// implemented
void BSTree::pretty_print_node(ostream &out, Node *node) {
    out << node->value << "[" << node->search_time << "] ";
}

// implemented
ostream &BSTree::print_level_by_level(ostream &out) {
    /*
      print the tree using a BFS
      output should look like this if we dont have a full tree

      4
      2 6
      1 X 5 7
      X X X X X X X 9

      it will be helpful to do this part iteratively,
      so do the BFS with the std stack data structure.

      it may also be helpful to put the entire tree into a vector
      (probably google this if you dont know how to do it)
    */

    if (root == nullptr)
        return out;

    bool hasNodes = true;
    vector<Node *> current_level;
    vector<Node *> next_level;
    current_level.push_back(root);
    while (hasNodes) {
        hasNodes = false;
        for (auto node : current_level) {
            if (node != nullptr) {
                pretty_print_node(out, node);
                if (node->left != nullptr)
                    hasNodes = true;
                if (node->right != nullptr)
                    hasNodes = true;

                next_level.push_back(node->left);
                next_level.push_back(node->right);
            } else {
                out << "X ";
                next_level.push_back(nullptr);
                next_level.push_back(nullptr);
            }
        }
        out << endl;
        current_level.clear();
        current_level = next_level;
        next_level.clear();
    }

    return out;
}

// implemented
int BSTree::get_total_search_time(Node *node) {
    if (node == nullptr)
        return 0;

    return get_total_search_time(node->left) +
           get_total_search_time(node->right) + node->search_time;
}

// implemented
float BSTree::get_average_search_time() {
    this->update_search_times();
    int total_search_time = get_total_search_time(root);
    if (total_search_time == 0)
        return -1;

    return ((float) total_search_time) / size;
}

