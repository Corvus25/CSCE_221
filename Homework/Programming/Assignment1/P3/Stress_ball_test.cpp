#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include "Stress_ball.h"
#include "Collection.h"

using namespace std;
using CollectionSB = Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes>;

ostream &operator<<(ostream &os, const CollectionSB &c) {

    map<Stress_ball_colors, string> convert_color;
    map<Stress_ball_sizes, string> convert_size;

    convert_color[Stress_ball_colors::red] = "red";
    convert_color[Stress_ball_colors::blue] = "blue";
    convert_color[Stress_ball_colors::yellow] = "yellow";
    convert_color[Stress_ball_colors::green] = "green";
    convert_size[Stress_ball_sizes::small] = "small";
    convert_size[Stress_ball_sizes::medium] = "medium";
    convert_size[Stress_ball_sizes::large] = "large";

    for (int i = 0; i < c.getSize(); i++) {
        os << "(" << convert_color[c[i].get_color()] << ", " << convert_size[c[i].get_size()] << ")" << endl;
    }
    return os;
}

istream &operator>>(istream &is, CollectionSB &c) {

    map<string, Stress_ball_colors> convert_color;
    map<string, Stress_ball_sizes> convert_size;

    convert_color["red"] = Stress_ball_colors::red;
    convert_color["blue"] = Stress_ball_colors::blue;
    convert_color["yellow"] = Stress_ball_colors::yellow;
    convert_color["green"] = Stress_ball_colors::green;
    convert_size["small"] = Stress_ball_sizes ::small;
    convert_size["medium"] = Stress_ball_sizes ::medium;
    convert_size["large"] = Stress_ball_sizes ::large;

    string line;

    do {
        string color;
        string size;

        is >> color >> size;
        Stress_ball_colors cl = convert_color[color];
        Stress_ball_sizes sz = convert_size[size];
        Stress_ball jn = Stress_ball(cl, sz);
        c.insert_item(jn);

    } while (!is.eof());

    return is;
}

int test_stress_balls() {

    Stress_ball sb1(Stress_ball_colors::red, Stress_ball_sizes::large);
    Stress_ball sb2(Stress_ball_colors::yellow, Stress_ball_sizes::medium);
    Stress_ball sb3(Stress_ball_colors::green, Stress_ball_sizes::small);
    Stress_ball sb4(Stress_ball_colors::blue, Stress_ball_sizes::small);

    CollectionSB A(4);
    CollectionSB B(5);

    A.insert_item(sb1);
    A.insert_item(sb2);
    A.insert_item(sb3);
    A.insert_item(sb4);

    B.insert_item(sb4);
    B.insert_item(sb4);
    B.insert_item(sb4);
    B.insert_item(sb4);
    B.insert_item(sb4);

    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Swapping A & B" << endl << endl;
    swap(A,B);

    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Sorting B..." << endl << endl;
    sort_by_size(B, Sort_choice::insertion_sort);
    cout << "B: " << endl << B << endl;

    cout << "Copying B to A..." << endl << endl;
    A = B;
    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;

    cout << "Merging A & B into C..." << endl << endl;
    auto C = make_Union(A, B);
    cout << "C: " << endl << C << endl;

    cout << "Importing new Collection..." << endl << endl;
    CollectionSB coll1 = CollectionSB();
    chdir("../Homework/Programming/Assignment1/P3");

    ifstream is1("stress_ball.data");
    if (!is1.is_open()) {
        throw runtime_error("Cannot open stress_ball.data.");
    }
    is1 >> coll1;
    cout << "Collection from file:" << endl << coll1;

    return 0;
}
