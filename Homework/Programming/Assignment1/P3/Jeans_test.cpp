#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include "Jeans.h"
#include "Collection.h"

using namespace std;
using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

ostream &operator<<(ostream &os, const CollectionJN &c) {

    map<Jeans_colors, string> convert_color;
    map<Jeans_sizes, string> convert_size;

    convert_color[Jeans_colors::navy] = "navy";
    convert_color[Jeans_colors::camo] = "camo";
    convert_color[Jeans_colors::teal] = "teal";
    convert_color[Jeans_colors::khaki] = "khaki";
    convert_size[Jeans_sizes::small] = "small";
    convert_size[Jeans_sizes::medium] = "medium";
    convert_size[Jeans_sizes::large] = "large";

    for (int i = 0; i < c.getSize(); i++) {
        os << "(" << convert_color[c[i].get_color()] << ", " << convert_size[c[i].get_size()] << ")" << endl;
    }
    return os;
}

istream &operator>>(istream &is, CollectionJN &c) {

    map<string, Jeans_colors> convert_color;
    map<string, Jeans_sizes> convert_size;

    convert_color["navy"] = Jeans_colors::navy;
    convert_color["camo"] = Jeans_colors::camo;
    convert_color["teal"] = Jeans_colors::teal;
    convert_color["khaki"] = Jeans_colors::khaki;
    convert_size["small"] = Jeans_sizes ::small;
    convert_size["medium"] = Jeans_sizes ::medium;
    convert_size["large"] = Jeans_sizes ::large;

    string line;

    do {
        string color;
        string size;

        is >> color >> size;
        Jeans_colors cl = convert_color[color];
        Jeans_sizes sz = convert_size[size];
        Jeans jn = Jeans(cl, sz);
        c.insert_item(jn);

    } while (!is.eof());

    return is;
}

int test_jeans() {

    Jeans jn1(Jeans_colors::navy, Jeans_sizes::large);
    Jeans jn2(Jeans_colors::camo, Jeans_sizes::medium);
    Jeans jn3(Jeans_colors::teal, Jeans_sizes::small);
    Jeans jn4(Jeans_colors::khaki, Jeans_sizes::small);

    CollectionJN A(4);
    CollectionJN B(5);

    A.insert_item(jn1);
    A.insert_item(jn2);
    A.insert_item(jn3);
    A.insert_item(jn4);

    B.insert_item(jn4);
    B.insert_item(jn4);
    B.insert_item(jn4);
    B.insert_item(jn4);
    B.insert_item(jn4);

    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Swapping A & B" << endl << endl;
    swap(A,B);

    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Sorting B..." << endl << endl;
    sort_by_size(B, Sort_choice::selection_sort);
    cout << "B: " << endl << B << endl;

    cout << "Copying B to A..." << endl << endl;
    A = B;
    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Merging A & B into C..." << endl << endl;
    auto C = make_Union(A, B);
    cout << "C: " << endl << C << endl;

    cout << "Importing new Collection..." << endl << endl;
    CollectionJN coll1 = CollectionJN();
    chdir("../Homework/Programming/Assignment1/P3");

    ifstream is1("jeans.data");
    if (!is1.is_open()) {
        throw runtime_error("Cannot open jeans.data.");
    }
    is1 >> coll1;
    cout << "Collection from file:" << endl << coll1;

    return 0;
}
