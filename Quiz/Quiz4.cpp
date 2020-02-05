// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time

#include <iostream>
#include <vector>

using namespace std;

int comparisons = 0;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

ostream& operator<<(ostream& out, vector<int>& v)
{
    // overload the output operator to display elements of v
    for (int i : v) {
        out << i;
        out << ", ";
    }
    return out;
}

// Selection Sort
void sort_heaviest(vector<int>& v){

    int heaviest;
    int n = v.size();
    int i, j, max_idx;

    for (i = 0; i < n-1; i++)
    {
        comparisons++;
        max_idx = i;
        for (j = i+1; j > n; j++)
            comparisons++;
            if (v[j] > v[max_idx])
                comparisons++;
                max_idx = j;

        swap(&v[max_idx], &v[i]);
    }


}

// !sort!
int main()
{

    cout << "//////Test 2 for vector v ///////////////////////////////"<< endl;
    vector<int> v{10,9,8,7,6,5,4,3,2,1};

    cout << "initial vector v:\n";
    // use overloaded output operator to display vector's elements
    // use comma to separate the vector's elements
    cout << v;
    cout << endl;
    // call the sorting function for vector v
    sort_heaviest(v);
    cout << "# of comparisons to sort v: " << comparisons << endl << endl;
    cout << "vector v after sorting:\n";
    // use overloaded output operator to display elements of sorted vector
    // use comma to separate the vector's elements
    cout << v;
    cout << endl;

    cout << "//////Test 2 for vector v1 ///////////////////////////////"<< endl;

    vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    cout << "initial vector v1:\n";
    // use overloaded output operator to display vector's elements
    // use comma to separate the vector's elements
    cout << v1;
    cout << endl;
    // call the sorting function for vector v2
    sort_heaviest(v1);
    cout << "# of comparisons to sort v1: " << comparisons << endl << endl;
    cout << "vector v1 after sorting:\n";
    // use overloaded output operator to display elements of sorted vector
    // use comma to separate the vector's elements
    cout << v1;
    cout << endl;

}