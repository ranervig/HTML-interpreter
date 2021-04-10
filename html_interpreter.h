//  Created by Syed Rehman on 4/8/21.
//  Class: Advanced C++ CIS 164
//  Description: This file defines the interpreter class for the HTML Interpreter program.

#pragma once

#include <deque>

#include "html_list_generator.h"

using namespace std;

deque<string> htmlInterpreter(deque<string> rawInput) {
    
    deque<string> convertedInputLines;
    string shorthandBuffer = "";
    bool titleSet = false;
    
    //While loop transfers line to convertedQueue first, then converts string
    do {
        
        convertedInputLines.push_back(rawInput.front());
        rawInput.pop_front();
        
        shorthandBuffer = "";
        
        //This for loop converts each string to HTML or just pushes a non-html line directly through
        for(const auto &a : convertedInputLines.back()){

            //Ensure string is longer than 2 characters (3 being the smallest potential shorthand code) to prevent overflow issues
            if(convertedInputLines.back().size() > 2){
                shorthandBuffer = shorthandBuffer + a;
            }
            else {
                //pass through short lines
                convertedInputLines.back() = convertedInputLines.back() + "\n";
                break; //End loop if line is not greater than 3.
            }
            
            //Look for shorthand start character
            if(shorthandBuffer.substr(0,1) == "*") {
                
                if( shorthandBuffer == "*TI " && !titleSet){
                    //do title things, can only be set once
                    //this will add automatically generated html lines to front and back before moving on
                    convertedInputLines.push_front("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n");
                    titleSet = true; //prevents recreating header content
                    convertedInputLines.back().erase(0, 4); //remove shorthand code
                    convertedInputLines.back() = "<title>" + convertedInputLines.back() + "</title> \n"; //Add leftover text to html tags and overwrite
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    convertedInputLines.push_back("</head>\n<body>\n");
                    break;
                }
                else if( shorthandBuffer == "*TI " && titleSet){
                    //delete titles after a title has already been set
                    convertedInputLines.pop_back();
                    break;
                }
                else if( shorthandBuffer == "*// " ){
                    //do comment things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code
                    convertedInputLines.back() = "<!-- " + convertedInputLines.back() + " --> \n"; //Add leftover text to html tags and overwrite
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*OL " ){
                    //do ordered list things
                    convertedInputLines.back() = stringToList(convertedInputLines.back());
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*UL " ){
                    //do unordered list things
                    convertedInputLines.back() = stringToList(convertedInputLines.back());
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*BR" || shorthandBuffer == "*BR " ){
                    //do line break things
                    convertedInputLines.back().erase(0, convertedInputLines.back().size());
                    convertedInputLines.back() = "<br> \n";
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*AH " ){
                    //do link things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code from final line
                    convertedInputLines.back() = "<a href=\"" + convertedInputLines.back().substr(0, static_cast<int>(convertedInputLines.back().find(","))) + "\">" + convertedInputLines.back().substr(static_cast<int>(convertedInputLines.back().find(",") + 2), convertedInputLines.back().size() - 1) + "</a>\n";
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*H1 " || shorthandBuffer == "*H2 " || shorthandBuffer == "*H3 " ||
                         shorthandBuffer == "*H4 " || shorthandBuffer == "*H5 " || shorthandBuffer == "*H6 " ){
                    //do heading things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code from final line
                    convertedInputLines.back() = "<h" + shorthandBuffer.substr(2, 1) + ">" + convertedInputLines.back() + "</h" + shorthandBuffer.substr(2, 1) + "> \n"; //Add leftover text to html tags and overwrite
                    
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*ST " ){
                    //do strong things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code
                    convertedInputLines.back() = "<strong>" + convertedInputLines.back() + "</strong> \n"; //Add leftover text to html tags and overwrite
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*EM " ){
                    //do emphasis things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code
                    convertedInputLines.back() = "<em>" + convertedInputLines.back() + "</em> \n"; //Add leftover text to html tags and overwrite
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*PG " ){
                    //do paragraph things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code
                    convertedInputLines.back() = "<p>" + convertedInputLines.back() + "</p> \n"; //Add leftover text to html tags and overwrite
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else if( shorthandBuffer == "*IM " ){
                    //do img things
                    convertedInputLines.back().erase(0, 4); //remove shorthand code from final line
                    convertedInputLines.back() = "<img src=\"" + convertedInputLines.back().substr(0, static_cast<int>(convertedInputLines.back().find(","))) + "\" alt=\"" + convertedInputLines.back().substr(static_cast<int>(convertedInputLines.back().find(",") + 2), convertedInputLines.back().size() - 1) + "\">\n";
                    shorthandBuffer = ""; //Clear string buffer for clean detection of next line
                    break;
                }
                else{
                    //passing through, leaves non-shorthand lines in tact
                    continue;
                }
                
            }
            else {
                //pass through non-shorthand lines
                convertedInputLines.back() = convertedInputLines.back() + "\n";
                break; //break shorthand search after passthrough
            }
            
        }
        
    } while(rawInput.size() > 0);
    
    convertedInputLines.push_back("</body>\n</html>\n");
    
    return convertedInputLines;
}
