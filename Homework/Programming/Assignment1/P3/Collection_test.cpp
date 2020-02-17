#include <iostream>
#include "Stress_ball_test.cpp"
#include "Jeans_test.cpp"

using namespace std;

int main() {

    cout << endl << "Welcome! This is \"Collection_test.cpp\".";
    cout << endl << "This program will test the templated implementation of Stress_ball and Jeans." << endl;

    int answer = 0;
    cout << "Select a version to test: stress_ball (=0) or jeans (=1): ";
    cin >> answer;
    if (answer == 0) {
        test_stress_balls();
    }
    else if (answer == 1) {
        test_jeans();
    }

    cout << endl << "This marks the end of this test file. The program will now terminate. Good bye :)" << endl;
    return 0;
}