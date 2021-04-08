#include <iostream>
#include <fstream>
#include <deque>
#include <string>
using namespace std;

deque<string> readFile();

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


