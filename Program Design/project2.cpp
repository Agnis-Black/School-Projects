/* ----------------------------------------------------------- 
    Program 2: Cuatro
    
    Class: CS 141, Spring 2020.  Tues 3pm lab
    System: Zybooks
    Author: Aqsa Arif

         -----------------------------------------------------------
  */
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
#include <cctype>     // for toupper()
using namespace std;  // so that we don't need to preface every cin and cout with std::

void displayInstructions()
{
    cout << "Welcome to the game of Cuatro, where you try to complete a set      \n"
         << "of four pieces that are alike.  Players take turns making moves.    \n"
         << "On each move your OPPONENT chooses the piece, then YOU get to       \n"
         << "place it on the board.  If you create a set of four alike when      \n"
         << "you place your piece, then you win!       \n"
         << "\n"
         << "A set of four alike can be completed by using four all upper (or all\n"
         << "lower) case characters, four all vowels (or all consonants), or four\n"
         << "all curved (or all straight-lined). Curved letters are 'O' and 'C'\n"
         << "(upper or lower), and straight-line letters are 'I' and 'Z' (upper or\n"
         << "lower). Groups of four can be created in a row, column, diagonal, or\n"
         << "corner quadrant.\n"
         << "\n"
         << "When prompted for input you may also enter 'x' or 'X' to exit." << endl;
}// end displayInstructions()

//Function to display original and remaining pieces
void displayPossibleMoves(string& upperRowPiecesToPlay,string& lowerRowPiecesToPlay)
   {
   cout << "Pieces:     Curved Straight" << endl;
   cout <<"      Upper: " << upperRowPiecesToPlay << endl;
   cout <<"      Lower: " << lowerRowPiecesToPlay << endl;
   cout << "            Vowel/Consonant" << endl;
}

// Function to display board 
void displayBoard(char& p1,char& p2,char& p3,char& p4,char& p5,char& p6,
                  char& p7,char& p8,char& p9,char& p10,char& p11,char& p12,
                  char& p13,char& p14,char& p15,char& p16)
{
   cout << " \n --------- " << "   Square #  " << endl;
   cout << "| " << p1 << " " << p2 << " " << p3 << " " << p4 << " |  " 
                                                                     << "1  2  3  4 " << endl;
   cout << "| " << p5 << " " << p6 << " " << p7 << " " << p8 << " |  " 
                                                                     << "5  6  7  8 " << endl;
   cout << "| " << p9 << " " << p10 << " " << p11 << " " << p12 << " |  "
                                                                     << "9 10 11 12 " << endl;
   cout << "| " << p13 << " " << p14 << " " << p15 << " " << p16 << " | " 
                                                                     << "13 14 15 16 " << endl;
   cout << " --------- " << endl;
}

// This is a function that checks if character entered is valid and removes from what is available if character is valid
bool getChar(char& pieceToMove,string& upperRowPiecesToPlay,string& lowerRowPiecesToPlay,
               char& p1,char& p2,char& p3,char& p4,char& p5,char& p6,
               char& p7,char& p8,char& p9,char& p10,char& p11,char& p12
               ,char& p13,char& p14,char& p15,char& p16){  
                  
   int piecePosition = 0;  
   // This if command looks for the character in the available upper pieces
   if((upperRowPiecesToPlay.find(pieceToMove)>=0)&&(upperRowPiecesToPlay.find(pieceToMove) != string::npos)){
      piecePosition = upperRowPiecesToPlay.find(pieceToMove);
      upperRowPiecesToPlay.replace(piecePosition, 1, " ");
      return true;
   }
   // This if command looks for the character in the available lower pieces
   else if((lowerRowPiecesToPlay.find(pieceToMove)>=0)&&(lowerRowPiecesToPlay.find(pieceToMove) != string::npos)){
            piecePosition = lowerRowPiecesToPlay.find(pieceToMove);
            lowerRowPiecesToPlay.replace(piecePosition, 1, " ");
            return true;
         }
         // If character not in upper or lower available pieces returns false
         else{
            cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;
            return false;
         }
}
 
//This function assignes destination and checks validity of integer input  
bool switchNum(char& pieceToMove, int& squareNumberOnBoard,
               string& upperRowPiecesToPlay,string& lowerRowPiecesToPlay,
               char& p1,char& p2,char& p3,char& p4,char& p5,char& p6,
               char& p7,char& p8,char& p9,char& p10,char& p11,char& p12,
               char& p13,char& p14,char& p15,char& p16){  
                  
   // Checks if integer input is in valid range               
   if((squareNumberOnBoard<1)||(squareNumberOnBoard>16)){
      cout << "*** Sorry, that destination is invalid.  Please retry." << endl;
      return false;
   }
   // This if command checks if character is valid and only then assigns equivalent destination
   else if ((lowerRowPiecesToPlay.find(pieceToMove)>=0)&&(lowerRowPiecesToPlay.find(pieceToMove) != string::npos)||
      (upperRowPiecesToPlay.find(pieceToMove)>=0)&&(upperRowPiecesToPlay.find(pieceToMove) != string::npos)){
         
      switch (squareNumberOnBoard) {
			case 1: if(p1 == '.'){p1 = pieceToMove;}break;
			case 2: if(p2 == '.'){p2 = pieceToMove;}break;
			case 3: if(p3 == '.'){p3 = pieceToMove;}break;
			case 4: if(p4 == '.'){p4 = pieceToMove;}break;
			case 5: if(p5 == '.'){p5 = pieceToMove;}break;
			case 6: if(p6 == '.'){p6 = pieceToMove;}break;
			case 7: if(p7 == '.'){p7 = pieceToMove;}break;
			case 8: if(p8 == '.'){p8 = pieceToMove;}break;
			case 9: if(p9 == '.'){p9 = pieceToMove;}break;
			case 10: if(p10 == '.'){p10 = pieceToMove;}break;
			case 11: if(p11 == '.'){p11 = pieceToMove;}break;
			case 12: if(p12 == '.'){p12 = pieceToMove;}break;
			case 13: if(p13 == '.'){p13 = pieceToMove;}break;
			case 14: if(p14 == '.'){p14 = pieceToMove;}break;
			case 15: if(p15 == '.'){p15 = pieceToMove;}break;
			case 16: if(p16 == '.'){p16 = pieceToMove;}break;
			default: "*** Sorry, that destination is occupied.  Please retry."; 
		}
   }  return true;  
}

// Character check for vowels
bool vowelCheck(char v1){
   if(( v1 == 'O')||( v1 == 'o')||( v1 == 'I')||( v1 == 'i')){
      return true;
   }
   else{
      return false;
   }
}
// Character check for consonents
bool constantCheck(char v1){
   if(( v1 == 'Z')||( v1 == 'z')||( v1 == 'C')||( v1 == 'c')){
         return true;
   }
   else{
      return false;
   }
}
// Charcter check for curves
bool curveCheck(char v1){
   if(( v1 == 'O')||( v1 == 'o')||( v1 == 'C')||( v1 == 'c')){
         return true;
   }
   else{
      return false;
   }
}
//Character check for straight 
bool straightCheck(char v1){
   if(( v1 == 'Z')||( v1 == 'z')||( v1 == 'I')||( v1 == 'i')){
         return true;
   }
   else{
      return false;
   }
}
// Character check for upper
bool allUpperCheck(char v1, char v2, char v3, char v4){
   if((isupper(v1)>0)&&(isupper(v2)>0)&&(isupper(v3)>0)&&(isupper(v4)>0)){
         return true;
   }
   else{
      return false;
   }
}
// Character check for lower
bool allLowerCheck(char v1, char v2, char v3, char v4){
   if((islower(v1)>0)&&(islower(v2)>0)&&(islower(v3)>0)&&(islower(v4)>0)){
         return true;
   }
   else{
      return false;
   }
}
// This function is to check if any 4 characters are true for the 6 combinations: Upper, Lower, Curved, Vowel, etc.
bool validityCheck(char v1, char v2, char v3, char v4){
   if( allLowerCheck(v1,v2,v3,v4)||
	allUpperCheck(v1,v2,v3,v4)||
       straightCheck(v1) && straightCheck(v2) && straightCheck(v3) && straightCheck(v4)||
       curveCheck(v1) && curveCheck(v2) && curveCheck(v3) && curveCheck(v4)||
       constantCheck(v1) && constantCheck(v2) && constantCheck(v3) && constantCheck(v4)||
       vowelCheck(v1) && vowelCheck(v2) && vowelCheck(v3) && vowelCheck(v4)){
          return true;
       }
       else { return false;
       }
}
// This is the main functin that checks for possibilities of wins in all directions: horizontally, vertically, etc.
bool comboCheckForWin(char& p1,char& p2,char& p3,char& p4,char& p5,char& p6,
                      char& p7,char& p8,char& p9,char& p10,char& p11,char& p12,
                      char& p13,char& p14,char& p15,char& p16)
{
   if(validityCheck(p1,p2,p3,p4)||
	validityCheck(p5,p6,p7,p8)||
	validityCheck(p9,p10,p11,p12)||
	validityCheck(p13,p14,p15,p16)||
        validityCheck(p1,p5,p9,p13)||
	validityCheck(p2,p6,p10,p14)||
	validityCheck(p3,p7,p11,p15)||
	validityCheck(p4,p8,p12,p16)||
        validityCheck(p1,p2,p5,p6)||
	validityCheck(p3,p4,p7,p8)||
	validityCheck(p9,p10,p13,p14)||
	validityCheck(p11,p12,p15,p16)||
        validityCheck(p1,p6,p11,p16)||
	validityCheck(p4,p7,p10,p13)){
         return true;
      }
      else{
         return false;
      }
}
// This function is the one that makes the move on board
void makeMove(char& pieceToMove, int& squareNumberOnBoard, string& upperRowPiecesToPlay,string& lowerRowPiecesToPlay,
      char& p1,char& p2,char& p3,char& p4,char& p5,char& p6,
      char& p7,char& p8,char& p9,char& p10,char& p11,char& p12,
      char& p13,char& p14,char& p15,char& p16){
   
   bool toLoop = false;
   // Checks for exit button
   char exitButtonUpper = 'X'; 
   char exitButtonLower = 'x';
   if((pieceToMove == exitButtonUpper)||(pieceToMove == exitButtonLower)){
      cout << "Exiting program...";
      exit(0);
   }
   while(toLoop == false){ // This while loop keeps looping until both character and integer entered are valid
      bool numBool = switchNum(pieceToMove,squareNumberOnBoard,
                  upperRowPiecesToPlay,lowerRowPiecesToPlay,
                  p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
   
      bool charBool = getChar(pieceToMove,upperRowPiecesToPlay,lowerRowPiecesToPlay,
                  p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
      
      displayBoard(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
      displayPossibleMoves(upperRowPiecesToPlay,lowerRowPiecesToPlay);
      
      // This if command serves the purpose of taking input again if character or integer input is invalid
      if( (numBool == true) && (charBool == true)){ 
         toLoop = true;
      }
      else{
         cin >> pieceToMove;
         cin >> squareNumberOnBoard;  
      }
   }
}
//-------------------------------------------------------------------------------------
int main(){
   // All original pieces and destinations
   char p1, p2, p3, p4,p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16;
   p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p14=p15=p16= '.';
   string upperRowPiecesToPlay = "OO/CC II/ZZ";
   string lowerRowPiecesToPlay = "oo/cc ii/zz";
   
   bool anyWins = false;    // The original variable o check for wins
   int moveCounter = 1;     // the counter that makes sure moves are less than 16 in bottom loop
   char pieceToMove;        // variable for character entered
   int squareNumberOnBoard; // varaible for destination entered
   int playerNum = 1;       // variable used to switch between first and second player
   
   displayInstructions();
   // Function called to display starting board
   displayBoard(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
   displayPossibleMoves(upperRowPiecesToPlay,lowerRowPiecesToPlay);
   
   do{
   // Changing players loop
	if( playerNum == 1) {
	   cout << moveCounter << ". Player 1 enter piece, and Player 2 enter destination: ";
		playerNum = 2 ;
	   }
	   else {
		   cout << moveCounter << ". Player 2 enter piece, and Player 1 enter destination: ";
		   playerNum = 1;
	   }
   cin >> pieceToMove;
   cin >> squareNumberOnBoard;
   
   makeMove(pieceToMove,squareNumberOnBoard,upperRowPiecesToPlay,lowerRowPiecesToPlay,
      p1,p2,p3,p4,p5,p6,p7,p8,
      p9,p10,p11,p12,p13,p14,p15,p16);
      
   anyWins = comboCheckForWin(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
   // Final wining display loop
   if( anyWins == true ){
      if(playerNum == 1){
         cout << "*** Player 1 you won!" << endl;
      }
      else{
         cout << "*** Player 2 you won!" << endl;
      }
      exit(0);
   }
   moveCounter +=1;
   }while(moveCounter <= 16);
    return 0;
} // end main()