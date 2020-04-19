// Sean Wangnick
// swangnick@tamu.edu
// Section 505

#include "CSVEditor.hpp"

CSVEditor::CSVEditor(string& inputPath, string& rosterPath, string& outputPath, regex expr, int m) {
    auto* ht = new HashTable<string>(m);
    hashTable = ht;

    input.open(inputPath);
    roster.open(rosterPath);
    output.open(outputPath);

    if (!input.is_open()) {
        cout << "Error reading from path " << inputPath << endl;
    }
    if (!roster.is_open()) {
        cout << "Error reading from path " << rosterPath << endl;
    }
    if (!output.is_open()) {
        cout << "Error reading from path " << outputPath << endl;
    }

    regexPattern = expr;
}

CSVEditor::~CSVEditor(){
    input.close();
    roster.close();
    output.close();
    delete hashTable;
    hashTable = nullptr;
}

void CSVEditor::readCSVToTable() {
	string line;

	// While next record exists
	while (getline(input, line, '\r')) {
	    // Get match based on capture groups
        smatch regexMatches;
        regex_search(line, regexMatches, regexPattern);

        // Push capture groups into a vector as strings
        vector<string> matches;
	    for (int i = 1; i < regexMatches.size(); i++) {
	        matches.push_back(regexMatches.str(i));
	    }

        // Insert into Hash Table
        int UIN = stoi(matches.at(2));
	    string score = matches.at(3);
        hashTable->insert(UIN, score);
	}
}

void CSVEditor::writeCSVToFile() {
    string line;

    // While next record exists
    while (getline(roster, line, '\r')) {
        // Get match based on capture groups
        smatch regexMatches;
        regex_search(line, regexMatches, regexPattern);

        // Push capture groups into a vector as strings
        vector<string> matches;
        for (int i = 1; i < regexMatches.size(); i++) {
            matches.push_back(regexMatches.str(i));
        }

        // Search Hash Table for record
        // If record exists, append grade to line, write to output.csv.
        // Else, no modification, write line to output.csv
        int UIN = stoi(matches.at(2));
        if (hashTable->search(UIN) == nullptr) {
            output << line;
        } else {
            auto grade = *hashTable->search(UIN);
            line = line + grade;
            output << line;
        }
    }
}

std::tuple<int, int, double> CSVEditor::getStats(){
	int min = this->hashTable->minChainLen();
	int max = this->hashTable->maxChainLen();
	double avg = this->hashTable->averageChainLen();

	return std::make_tuple(min, max, avg);
}