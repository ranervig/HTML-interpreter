#include <iostream>
#include <fstream>
#include <deque>
#include <string>
using namespace std;

deque<string> readFile();
string stringToList(string unformattedList);

int main() {

	deque<string> inputDeque = readFile();
	while (!inputDeque.empty()) {
		cout << inputDeque.front() << endl;
		inputDeque.pop_front();
	}

	return 0;
}


//Robby Nervig
deque<string> readFile() {
	fstream file;
	string fileName;
	deque<string> fileQueue;

	cout << "Please enter the name of the file to convert, including extension(.txt):";
	cin >> fileName;
	file.open(fileName, ios::in);

	//checks if file opened correctly 
	while (!file.good()) {
		cout << "Please enter a valid file name, including extension(.txt):";
		cin >> fileName;
		file.open(fileName, ios::in);
	}

	string line;
	//pull lines from file and add to deque
	while (getline(file, line)) {
		fileQueue.push_back(line);
	}

	file.close();
	return fileQueue;
}



string stringToList(string unformattedList) { // Noah Chung
    // takes a string and returns a string in HTML list format that can be added to the queue
    // tested it with items of different size and with lists with 3 and 4 items
    const int AFTER_TAG = 4;
    string list;
    size_t nextComma = 0;
    bool firstItem = true;

    while (nextComma != string::npos) {
        string dimension;
        size_t comma = unformattedList.find(", ", nextComma);
        nextComma = unformattedList.find(", ", nextComma + 2);

        if (firstItem == true) {
            list = list + "<li>" + unformattedList.substr(AFTER_TAG, nextComma - 4) + "</li>" + "\n";
        }

        if (firstItem == false && nextComma == string::npos) {
            list = list + "<li>" + unformattedList.substr(comma + 2) + "</li>" + "\n";
        }
        else if (firstItem == false) {
            list = list + "<li>" + unformattedList.substr(comma + 2, (nextComma - comma - 2)) + "</li>" + "\n";
        }
        firstItem = false;
    }

    if(unformattedList.substr(0, 3) == "*UL") {
        list = "<ul>\n" + list + "</ul>\n";
    }
    else {
        list = "<ol>\n" + list + "</ol>\n";
    }

    return list;
}
