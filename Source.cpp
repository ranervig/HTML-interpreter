#include <iostream>
#include <fstream>
#include <deque>
#include <string>

#include "html_interpreter.h"

using namespace std;

deque<string> readFile();
string stringToList(string unformattedList);

int main() {

    deque<string> inputDeque = readFile();
    
    deque<string> convertedDeque = htmlInterpreter(inputDeque);
    
    while (!convertedDeque.empty()) {
        cout << convertedDeque.front() << endl;
        convertedDeque.pop_front();
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
