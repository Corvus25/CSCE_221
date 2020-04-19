// Sean Wangnick
// swangnick@tamu.edu
// Section 505

#include <string>
#include <regex>
#include "HashTable.hpp"
#include "CSVEditor.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    regex expr("(.*),(.*),(.*),(.*)");
	
    string inputPath = "./input.csv";
    string rosterPath = "./roster.csv";
    string outputPath = "./output.csv";

	int m = 0;
	//OBTAIN M HERE
	ifstream roster(rosterPath);
	if (!roster.is_open()) {
		cout << "Error reading from path " << rosterPath << endl;
	}
	string line;
	while (getline(roster, line, '\r')) {
		m++;
	}
	if (m == 0) {
		cout << "Error, m (bucket size) cannot be zero. There was a problem reading the roster" << endl;
		exit(1);
	}


    CSVEditor editor(inputPath, rosterPath, outputPath, expr, m);
    editor.readCSVToTable();
    editor.writeCSVToFile();

	std::tuple<int, int, double> stats = editor.getStats();

	cout << "minimum chain len = " << std::get<0>(stats) << endl;
	cout << "maximum chain len = " << std::get<1>(stats) << endl;
	cout << "average chain len = " << std::get<2>(stats) << endl;

//	HashTable<string> test(5);
//	test.insert(427003618, "93");
//	test.insert(427003518, "92");
//	test.insert(427003718, "94");
//	test.insert(427003717, "90");
//	test.insert(427003510, "84");
//	test.insert(427003511, "85");
//	test.insert(427003511, "86");
//
//	int min = test.minChainLen();
//	int max = test.maxChainLen();
//	double avg = test.averageChainLen();
//
//	cout << min << endl;
//  cout << max << endl;
//  cout << avg << endl;

    return 0;    
}
