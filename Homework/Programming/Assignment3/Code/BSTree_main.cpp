#include <iostream>
#include <fstream>
#include <sstream>
#include "BSTree.h"

using namespace std;

BSTree read_file(string file_name) {
    /*
      open the file and use the input operator (operator>>)
      to construct a new tree
    */

    BSTree new_tree;

    ifstream is;
    is.open(file_name);
    if(!is) {
        cout << "Error reading file " << file_name << endl;
    }

    is >> new_tree;
    return new_tree;
}


int main() {

    cout << endl;
    cout << "///////////////////////////////" << endl;
    cout << "/////       TESTING       /////" << endl;
    cout << "///////////////////////////////" << endl;
    cout << endl;
    
    // test insert
    BSTree *tree1 = new BSTree();
    tree1->insert(5);
    tree1->insert(3);
    tree1->insert(9);
    tree1->insert(7);
    tree1->insert(10);
    tree1->insert(11);

    // test search
    auto a = tree1->search(5);  // true
    auto b = tree1->search(2);  // false
    auto c = tree1->search(11); // true

    // test output level by level
    auto d = tree1->get_average_search_time();
    tree1->print_level_by_level(cout) << endl;
    delete tree1;
    tree1->print_level_by_level(cout) << endl;
    auto e = tree1->get_average_search_time();

    // test output in order
    cout << "With tree: " << endl;
    BSTree *tree2 = new BSTree();
    tree2->insert(4);
    tree2->insert(2);
    tree2->insert(1);
    tree2->insert(3);
    tree2->insert(6);
    tree2->insert(5);
    tree2->insert(7);
    cout << "In-Order traversal produces: " << endl;
    tree2->inorder(cout) << endl << endl;

    cout << "Level by level: " << endl;
    tree2->print_level_by_level(cout) << endl;
    cout << "Update search times, print again: " << endl;
    tree2->update_search_times();
    tree2->print_level_by_level(cout) << endl;

    // test the copy constructor
    BSTree tree3 = *tree2;
    cout << "copy tree2 to tree3 (copy constructor)" << endl;
    cout << "tree2: " << tree2 << endl;
    tree2->print_level_by_level(cout) << endl;
    cout << "tree3: " << &tree3 << endl;
    tree3.print_level_by_level(cout) << endl;

    // test the copy assignment
    BSTree tree5;
    tree5 = *tree2;
    cout << "copy tree2 to tree5 (copy assignment)" << endl;
    cout << "tree2: " << tree2 << endl;
    tree2->print_level_by_level(cout) << endl;
    cout << "tree5: " << &tree5 << endl;
    tree5.print_level_by_level(cout) << endl;

    // test move constructor
    cout << "Moving tree2 to tree4... (move constructor)" << endl;
    BSTree tree4(move(*tree2));
    cout << "tree2: " << tree2 << endl;
    tree2->print_level_by_level(cout) << endl;
    cout << "tree4: " << &tree4 << endl;
    tree4.print_level_by_level(cout) << endl;

    // test move assignment
    cout << "Moving tree4 to tree6... (move assignment)" << endl;
    BSTree tree6;
    tree6 = move(tree4);
    cout << "tree4: " << &tree4 << endl;
    tree4.print_level_by_level(cout) << endl;
    cout << "tree6: " << &tree6 << endl;
    tree6.print_level_by_level(cout) << endl;

    cout << endl << endl;

    for (int i = 1; i <= 12; i++) {
        string dir = "data-files/" + std::to_string(i);
        BSTree l = read_file(dir + "l");
        cout << "average search time linear " << i << " "
             << l.get_average_search_time() << endl;
        BSTree p = read_file(dir + "p");
        cout << "average search time perfect " << i << " "
             << p.get_average_search_time() << endl;
        BSTree r = read_file(dir + "r");
        cout << "average search time random " << i << " "
             << r.get_average_search_time() << endl;

        if (i <= 4) {
            cout << "prefect tree " << i << endl << p;
        }

        if (i >= 5) {
            // create fstream
            // read out to fstream
            string outDir = "out-files/" + std::to_string(i);
            ofstream out(outDir + "p");
            if (out) {
                p.inorder(out);
                p.print_level_by_level(out);
            }
        }

        cout << endl;
    }

    cout << endl;
    cout << "///////////////////////////////" << endl;
    cout << "/////     APPLICATION     /////" << endl;
    cout << "///////////////////////////////" << endl;
    cout << endl;

    string outDir;

    cout << "//////// TREE10 ////////" << endl;
    cout << "Making tree10 with 10 nodes" << endl;
    BSTree *tree10 = new BSTree();
    tree10->insert(5);
    tree10->insert(3);
    tree10->insert(2);
    tree10->insert(1);
    tree10->insert(4);
    tree10->insert(8);
    tree10->insert(6);
    tree10->insert(7);
    tree10->insert(9);
    tree10->insert(10);
    tree10->update_search_times();

    if (tree10->get_size() < 16) {
        cout << "Inorder traversal: ";
        tree10->inorder(cout) << endl;
        tree10->print_level_by_level(cout) << endl;
    }

    cout << "Average search cost: " << tree10->get_average_search_time() << endl;
    cout << "Number of nodes: " << tree10->get_size() << endl;

    outDir = "out-files/tree10";
    ofstream out(outDir);
    if (out) {
        tree10->inorder(out) << endl;
        cout << "Outputted to file" << endl;
    }
    cout << endl << endl;

    // tree30
    cout << "//////// TREE30 ////////" << endl;
    cout << "Making tree30 with 20 nodes" << endl;
    BSTree *tree30 = new BSTree();
    tree30->insert(16);
    tree30->insert(8);
    tree30->insert(4);
    tree30->insert(12);
    tree30->insert(2);
    tree30->insert(1);
    tree30->insert(3);
    tree30->insert(6);
    tree30->insert(5);
    tree30->insert(7);
    tree30->insert(10);
    tree30->insert(14);
    tree30->insert(9);
    tree30->insert(11);
    tree30->insert(13);
    tree30->insert(15);
    tree30->insert(24);
    tree30->insert(28);
    tree30->insert(20);
    tree30->insert(18);
    tree30->insert(17);
    tree30->insert(19);
    tree30->insert(22);
    tree30->insert(21);
    tree30->insert(23);
    tree30->insert(26);
    tree30->insert(30);
    tree30->insert(25);
    tree30->insert(27);
    tree30->insert(29);
    tree30->update_search_times();

    if (tree30->get_size() < 16) {
        cout << "Inorder traversal: ";
        tree30->inorder(cout) << endl;
        tree30->print_level_by_level(cout) << endl;
    }

    cout << "Average search cost: " << tree30->get_average_search_time() << endl;
    cout << "Number of nodes: " << tree30->get_size() << endl;

    outDir = "out-files/tree30";
    ofstream out2(outDir);
    if (out) {
        tree30->inorder(out2) << endl;
        cout << "Outputted to file" << endl;
    }
    cout << endl << endl;
    tree30->print_level_by_level(cout) << endl;
}

