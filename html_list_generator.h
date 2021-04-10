// Noah Chung

#pragma once

#include <string>

using namespace std;

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
