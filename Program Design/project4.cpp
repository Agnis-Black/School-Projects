/* ----------------------------------------
 * Program 4: Two Codes
 * Class: CS 141, Spring 2020.
 * Authors: Aqsa Arif, Kevin Rodriguez.
 * System: CLion on Windows
 * Lab: Tues 3 pm and 8 am respectively
 * UIN: 677417263 and 651086752 respectively
 * ----------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// This function opens the file and determines if file is read
void openFile(vector<string> &textLines) {
    ifstream inStream;
    string textHoldingVariable;
    inStream.open("ConstitutionAndBillOfRights.txt");
    //This command checks if the text file is available
    if (!inStream.is_open()) {
        cout << "Could not find ConstitutionAndBillOfRights.txt.  Exiting..." << endl;
        exit(-1);
    }
    // Read the next line from File until it reaches the end.
    while (getline(inStream, textHoldingVariable)) {
        // Line contains string of length > 1 then save it in vector; prevents saving blank lines.
        if (textHoldingVariable.size() > 1)
            textLines.push_back(textHoldingVariable);
    }
    inStream.close(); // close the file
}
// end openFile

// This function is to ensure any lower input character is passed as upper in cases
char upperChar(char &menuOption) {
    if(islower(menuOption)) {
        menuOption = toupper(menuOption);
        return menuOption;
    }
    return menuOption;
}
// end upperChar

//This function takes the string line and makes all letters in Line lower alphabets
string lowerString(string &textLine) {
    int sizeOfLine = textLine.size();
    for(int i = 0;i<sizeOfLine;i++){
        textLine[i] = tolower(textLine[i]);
    }
    return textLine;
}
// end lowerString

// This function makes all lines lower case
void lowerCaseLines(vector<string> &textLinesLowered) {
    int totalNumberOfLines = textLinesLowered.size();
    // totalNumberOfLines is a variable made to ensure all 250 lines are passed through lowerString function
    for(int i = 0; i < totalNumberOfLines; i++) {
        string toLower = textLinesLowered.at(i);
        lowerString(toLower);
        textLinesLowered.at(i) = toLower;
        // By this point textLinesLowered is a vector that contains all text lines with lowered alphabets
    }
}
// end lowerCaseLines

// This function locates the line in the file
void locateLineNumber(vector<string> textLines,string wordOrPhrase,vector <int> &lineNumber){
    int totalNumberOfLines = textLines.size();
    vector <string> textLinesLowered(totalNumberOfLines);
    for(int i = 0; i < totalNumberOfLines; i++) {
        // Initially make vector for lower alphabets equal to original text file vector
        textLinesLowered.at(i) = textLines.at(i);
    }
    lowerCaseLines(textLinesLowered);
    //By this point all Lines have been lower cased by above function call
    for(int i = 0; i < totalNumberOfLines; i++) {
        string sourceText = textLinesLowered.at(i);
        // This is the search, if a location is found it is stored in the lineNumber vector
        if(sourceText.find(wordOrPhrase) != string::npos) {
            lineNumber.push_back(i);
        }
    }
    if(lineNumber.size() == 0) {
        // This is a defaulter, if no search match is found assign found line number to be 251
        // In printLine this location would not print anything but upon p or f menuOption give an error message to try another search word/Phrase
        lineNumber.push_back(9999);
    }
}
// end locateLineNumber

// This function prints according to all input variables
void printLine(vector<string> textLines, vector <int> lineNumber, int lineNumVariable = 0, bool firstRun = true , bool printAll = false){
    // lineNumVariable is the variable that keeps changing according to the p / f / w choosing menuOption
    if(lineNumVariable < 0) {
        cout << "There is no previous file contents." << endl;
    }
    else if(lineNumVariable > 250) {
        cout << "There is no following file contents." << endl;
    }
    else if(firstRun == true) {
        // If menuOption w is chosen, prints out first occurence of search
        cout << "Line " << lineNumber.at(0) << ":" << endl;
        cout << textLines.at(lineNumber.at(0)) << endl;
    }
    else if(printAll == true) {
        // If menuOption a is chosen loops and prints all occurences stored in lineNumber vector
        for(long unsigned int i = 0; i < lineNumber.size();i++) {
            cout << "Line " << lineNumber.at(i) << ":" << endl;
            cout << textLines.at(lineNumber.at(i)) << endl;
        }
    }
    else {
        // This part the general printing associated with f or p menuOption
        cout << "Line " << lineNumVariable << ":" << endl;
        cout << textLines.at(lineNumVariable) << endl;
    }
}
// end PrintLine

// Starting the int main
int main() {
    char menuOption;                   // This is the Switch variable
    int lineNumVariable = 0;           // lineNumVariable is the variable that keeps changing according to the p / f / w choosing menuOption
    bool firstRun;                     // This boolean makes sure upon w menuOption only first found line is printed
    bool printAll;                     // This boolean is to print all occurences upon choosing 'A' menuOption
    bool validInput = false;           // In case word or phrase to look up is not found in text file, default statements are printed out
    string wordOrPhrase;               // The variable that will hold key word or phrase to search
    vector <string> textLines(0);   // The vector that will hold all text lines
    vector <int> lineNumber(0);     // This vector will hold occurences of key word of phrase as line numbers

    // Display first menu and handle menu options
    cout << "Select from the following choices: \n"
         << "  W  Enter word or phrase to find, and display enclosing text  \n"
         << "  X  Exit program  \n"
         << "Your choice: \n";

    cin >> menuOption;
    upperChar(menuOption);
    // The above two lines take input them convert input into upper char to make sure it runs in the switch cases

    while(menuOption != 'X') {

        switch (menuOption) {

            case 'W': {
                cout << "Enter word or phrase: " ;
                // We get word or phrase to search by user from here
                cin.get();
                getline(cin, wordOrPhrase);
                lowerString(wordOrPhrase);
                // By this point word or phrase is stored in wordOrPhrase variable and is in lower case alphabet
                openFile(textLines);
                // The clear wipes out the lineNumber vector to make sure correct first occurence is printed
                lineNumber.clear();
                locateLineNumber(textLines,wordOrPhrase,lineNumber);
                // Below is the initial line printing
                if(lineNumber.at(0) != 9999) {
                    // If locateLineNumber does not default, first occurence is printed
                    printLine(textLines, lineNumber);
                    lineNumVariable = lineNumber.at(0);
                    firstRun = false;
                    validInput = true;
                }
                else{
                    // If locateLineNumber does default, user is prompted to retry with valid search
                    cout << "Word or phrase not found in file. Please retry." << endl;
                }
                break;
            }

            case 'P': {

                if(validInput == false) {
                    // If word or phrase to search is invalid, user prompted to retry
                    cout << "First you must find a word or phrase.  Please retry." << endl;
                    break;
                }
                else {
                    if(lineNumVariable == 251 ){
                        lineNumVariable = 250;
                    }
                    if (lineNumVariable != -1) {
                        lineNumVariable -= 1;
                    }
                    printLine(textLines, lineNumber, lineNumVariable, firstRun);
                    break;
                }
            }

            case 'F':{

                if(validInput == false) {
                    // If word or phrase to search is invalid, user prompted to retry
                    cout << "First you must find a word or phrase.  Please retry." << endl;
                    break;
                }
                else {
                    if(lineNumVariable == -1 ){
                        lineNumVariable = 0;
                    }
                    if (lineNumVariable != 251) {
                        lineNumVariable += 1;
                    }
                    printLine(textLines, lineNumber, lineNumVariable, firstRun);
                    break;
                }
            }

            case 'A': {

                if(validInput == false) {
                    // If word or phrase to search is invalid, user prompted to retry
                    cout << "First you must find a word or phrase.  Please retry." << endl;
                    break;
                }
                else {
                    printAll = true;
                    printLine(textLines, lineNumber, lineNumVariable, firstRun, printAll);
                    break;
                }
            }

            default: {
                //Sanity Check
                cout << "Invalid menu option.  Exiting program." << endl;
                break;
            }
        }
        // end switch( menuOption)

        // Upon exiting switch, user shown display and prompted for next command
        cout << "\nSelect from the following choices: \n"
             << "  W  Enter word or phrase to find, and display enclosing text  \n"
             << "  P  Display previous text   \n"
             << "  F  Display following text   \n"
             << "  A  Display all occurrences of found word or phrase \n"
             << "  X  Exit program  \n"
             << "Your choice: \n";

        cin >> menuOption;
        upperChar(menuOption);
    }
    // While loop is exited when x or X is selected
    cout << "Exiting program." << endl;
    exit(0);
}
// end of main()