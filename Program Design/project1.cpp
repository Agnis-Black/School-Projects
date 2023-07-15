#include <iostream>   // for cin and cout
#include <iomanip>    // for setw() and setfill()
using namespace std;  // so that we don't need to preface every cin and cout with std::
/* ______________________________________________
 |   _____    _____    _____    _____    _____   | Original ASCII graphic 
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  | Attempt at drawing PSR - Polk Street Residence 
 |   _____    _____    _____    _____    _____   | (Campus housing)
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |
 |   _____    _____    _____    _____    _____   |
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |
 |   _____    _____    _____    _____    _____   |
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |
 |   _____    _____    _____    _____    _____   |
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |
 |   _____    _____    _____    _____    _____   |
 |  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |
 |                                               |
 |   _____    ________________________________   |
 |  | ,|, |  |	   |   |   |   |   |   |   |   |  |
 |__|__|__|__|____|___|___|___|___|___|___|___|__|
*/
int main(){
    int menuOption = 0;
    cout << "Choose from among the following options:  \n"
         << "1. Display original graphic  \n"
         << "2. Display building          \n"
         << "3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    cout << endl;   // Leave a blank line after getting the user input for the menu option.
    if( menuOption == 3) { // See if exit was chosen
        exit( 0);
    }
    else if( menuOption == 1) { // Coding for original ASCII graphic
        cout << " _______________________________________________ \n"; // Roof of building
        for(int floorNum=2;floorNum<=13;floorNum++){
           if( floorNum % 2 == 0){
              cout << "|   _____    _____    _____    _____    _____   | \n";
            }
            else{
               cout << "|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  |_|_|_|  | \n";
            }
        }
        cout << "|                                               |\n";
        cout << "|   _____    ________________________________   |\n";
        cout << "|  | ,|, |  |	 |   |   |   |   |   |   |   |  |\n";
        cout << "|__|__|__|__|____|___|___|___|___|___|___|___|__|\n"; // Ground floor windows and door
      }//end if( menuOption == 1)  // menu option to display custom graphic
      
    else if ( menuOption == 2) { //This menu option will display Chicago's John Hancock building
       int buildSections = 0;
       cout << "Number of building sections -> "; // Prompt that will be displayed for input
       cin >> buildSections;
       cout << endl; // Skip line after getting input
       int lineNum = buildSections;
       int forwardCount = 0; // Used to adjust number of floors in each section
       while( lineNum != -1 ){ // The -1 is important, it enables printing of section 0
          if( lineNum == buildSections){
             cout << setw(4 + buildSections) << "/\\" << endl;
             cout << setw(4 + buildSections) << "||" << endl;
             cout << setw(4 + buildSections) << "||" << endl;
             cout << setw(4 + buildSections) << "--" << endl;
             cout << setw(5 + buildSections) << "|++|" << endl;
             cout << setw(5 + buildSections) << "====" << endl;
          }
         int floorNum = 2 * forwardCount;           // Total number of floors to be drawn for a building section
         int floorCount = floorNum / 2;             // This is to keep track of number of floors being drawn
         int incSpace = 1;                          // Used for increasing spacing
         int dwnSpace = forwardCount * 2;           // Used for decreasing
         for (int midtopFloors = floorCount;midtopFloors!=0;midtopFloors--){
            // This is variable used for top part of the X in the building sections
            cout << setw(3 + lineNum) << setfill(' ')<< "|";
            cout << setw(incSpace) << setfill(':') << "\\";
            cout << setw(dwnSpace-incSpace) << "/";
            cout << setw(incSpace) << setfill(':') << "|";
            incSpace += 1;
            dwnSpace -= 1;
            cout << endl;
         }
         incSpace = 1;
         for (int midbotFloors = floorCount;midbotFloors!=0;midbotFloors--){
            // This is variable used for bottom part of the X
            cout << setw(3 + lineNum) << setfill(' ') << "|";
            cout << setw(dwnSpace) << setfill(':') << "/";
            cout << setw(2*incSpace-1) << "\\";
            cout << setw(dwnSpace) << "|";
            cout << endl;
            dwnSpace -=1;
            incSpace +=1;
            if (midbotFloors == 1){
               cout << setw(3 + lineNum) << setfill(' ') << "/";
               cout << setw(2*forwardCount+1) << setfill('-') << "\\" << endl;
            }
         }
         if (lineNum == 0){ // This part is used to draw base
            cout << " " << setw(4+2*buildSections) << setfill('.') << "." << endl;
            cout << setw(6+2*buildSections) << setfill('+') << "+" << endl;
            cout << endl;
         }
         forwardCount +=1;
         lineNum--;
       }
    return 0;
    }
}


