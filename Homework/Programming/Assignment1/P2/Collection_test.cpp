#include "Stress_ball.h"
#include "Collection.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

int main() {

    cout << endl << "Welcome! This is \"Collection_test.cpp\".";
    cout << endl << "This program will test the implementation of the functions residing in the Collection and Stress_ball programs." << endl;

    cout << "Creating empty Collection objects coll1, coll2, coll3." << endl;
    Collection coll1 = Collection();
    Collection coll2 = Collection();
    Collection coll3 = Collection();
    cout << "Filling coll1, coll2, coll3 via .data files." << endl;

    chdir("P2");
    ifstream is1("stress_ball1.data");
    if (!is1.is_open()) {
        throw runtime_error("Cannot open stress_ball1.data.");
    }
    ifstream is2("stress_ball2.data");
    if (!is2.is_open()) {
        throw runtime_error("Cannot open stress_ball2.data.");
    }
    ifstream is3("stress_ball3.data");
    if (!is3.is_open()) {
        throw runtime_error("Cannot open stress_ball3.data.");
    }
    is1 >> coll1;
    is2 >> coll2;
    is3 >> coll3;

    cout << "3 collection objects initialized & filled." << endl;
    cout << endl << "coll1: " << &coll1 << endl;
    coll1.print_items();
    cout << endl << "coll2: " << &coll2 << endl;
    coll2.print_items();
    cout << endl << "coll3: " << &coll3 << endl;
    coll3.print_items();

    cout << endl << endl;

    cout << "Sorting coll1 by bubble sort..." << endl;
    sort_by_size(coll1, Sort_choice::bubble_sort);
    cout << "Sorting coll2 by insertion sort..." << endl;
    sort_by_size(coll2, Sort_choice::insertion_sort);
    cout << "Sorting coll3 by selection sort..." << endl;
    sort_by_size(coll3, Sort_choice::selection_sort);

    cout << endl << "coll1: " << &coll1 << endl;
    cout << "Total Stress Ball's: " << coll1.total_items() << endl;
    cout << "# of Green's: " << coll1.total_items(Stress_ball_colors::green) << endl;
    cout << "# of Small's: " << coll1.total_items(Stress_ball_sizes::small) << endl;
    coll1.print_items();
    cout << endl << "coll2: " << &coll2 << endl;
    cout << "Total Stress Ball's: " << coll2.total_items() << endl;
    cout << "# of Blue's: " << coll2.total_items(Stress_ball_colors::blue) << endl;
    cout << "# of Small's: " << coll2.total_items(Stress_ball_sizes::small) << endl;
    coll2.print_items();
    cout << endl << "coll3: " << &coll3 << endl;
    cout << "Total Stress Ball's: " << coll3.total_items() << endl;
    cout << "# of Red's: " << coll3.total_items(Stress_ball_colors::red) << endl;
    cout << "# of Large's: " << coll3.total_items(Stress_ball_sizes::large) << endl;
    coll3.print_items();

    cout << endl << endl;

    cout << "Init additional Collection object, coll4, as union of coll1, coll2..." << endl;
    Collection coll4 = make_Union(coll1, coll2);
    cout << endl << "coll4: " << &coll4 << endl;
    cout << "Total Stress Ball's: " << coll4.total_items() << endl;
    cout << "# of Yellow's: " << coll4.total_items(Stress_ball_colors::yellow) << endl;
    cout << "# of Small's: " << coll4.total_items(Stress_ball_sizes::small) << endl;
    coll4.print_items();

    cout << endl << endl;

    cout << "Swapping coll1, coll2..." << endl << endl;
    swap(coll1, coll3);
    cout << endl << "coll1: " << &coll1 << endl;
    coll1.print_items();
    cout << endl << "coll2: " << &coll3 << endl;
    coll2.print_items();

//    cout << endl << endl << "Done with requirements. Testing the rest just in case..." << endl;
//
//    cout << "Making SB..." << endl;
//    Stress_ball test;
//    cout << "Test SB:\t" << test << endl;
//    cout << "Inserting SB -> coll3..." << endl;
//    coll3.insert_item(test);
//    cout << endl << "coll3: " << &coll3 << endl;
//    cout << "Total Stress Ball's: " << coll3.total_items() << endl;
//    coll3.print_items();
//
//    cout << endl << endl;
//
//    cout << "1 = True\t0 = False" << endl;
//    cout << "Does coll3 contain \"test\"?: " << coll3.contains(test) << endl;
//    cout << "Removing \"test\" sb: " << endl;
//    coll3.remove_this_item(test);
//    cout << "Does coll3 contain \"test\"?: " << coll3.contains(test) << endl;
//
//    cout << "Remove random sb:" << endl;
//    coll3.remove_any_item();
//    coll3.print_items();
//
//    cout << "Is Collection empty? " << coll3.is_empty() << endl;
//    coll3.make_empty();
//    cout << "How about now? " << coll3.is_empty() << endl;
//    cout << endl << endl;
//
//    cout << endl << "coll3: " << &coll3 << endl;
//    cout << "Total Stress Ball's: " << coll3.total_items() << endl;
//    coll3.print_items();
//    cout << endl << "coll4: " << &coll4 << endl;
//    cout << "Total Stress Ball's: " << coll4.total_items() << endl;
//    coll3.print_items();
//    cout << endl << endl << "Move coll3 to coll4..." << endl << endl;
//    coll4 = move(coll3);
//    cout << endl << "coll3: " << &coll3 << endl;
//    cout << "Total Stress Ball's: " << coll3.total_items() << endl;
//    coll3.print_items();
//    cout << endl << "coll4: " << &coll4 << endl;
//    cout << "Total Stress Ball's: " << coll4.total_items() << endl;
//    coll3.print_items();

    cout << endl << "This marks the end of this test file. The program will now terminate. Good bye :)" << endl;
    return 0;
}