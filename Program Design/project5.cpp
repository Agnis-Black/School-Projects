// Prog5Pentago.cpp
//     Play the two-player game of Pentago, trying to get 5 pieces in a row.
//
// Author: Dale Reed
// Program: #5, Pentago using classes
// 3/23/2020
//
/*
Project 5: Pentago. Late submission essay: The differences between my code and the given solution is that I so not use any global or constant variables in my code. A lot of the class functions in the solution are already defined by calling other functions. My code is longer and doesn't have such intricate back and forth. The solution uses a 1D array, but my code uses a 2D vector for board pieces/positions. The solution has an algorithm where the board is printed in 2 sections but my code is mostly hard copied as in the commented example. To check for a win the solution uses a loop relevant to the 1D array, my code is mostly hard copied for wins in total 64 if statements to check for a win in either X or O piece. The solution has a board check function in which the winning conditions are checked by a loop and Booleans assigned according to who won. My code is more hard coded and only loops to see if board is full/empty. Our winning output statements are similar that we both Boolean type to print out winner. The solution code uses a 2D array for the rotation of both right and left but my code uses a 2D vector. The rotation in the solution consists of making the rows into columns and columns into rows and them reversing them to give a clockwise rotation. Similar is done for anticlockwise rotation. The Left rotation also involves making rows into columns and columns into rows then reversing the array elements in 1 set. A temporary variable is used to store the initial value for later reference. My code is different that it divides square into 2 triangles and makes them swamp diagonally. My code's left swap consists of 3 clockwise rotations. In the solution the validity checks have a separate function. My code does all it's checks by calling functions in the switch statement of the original input for row character. Both codes use the same code to switch board pieces from O to X piece and so forth.  The solution does not use switch statements at all whereas my code is full of all row values for switch and my minor functions to check for other values. The check validity functions are similar but are coded differently.
*/

#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>    // For toupper()
#include <vector>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << "\n"
         << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
         << "                                                                 \n"
         << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
         << "quadrants.  There are two players, X and O, who alternate turns. \n"
         << "The goal of each player is to get five of their pieces in a row, \n"
         << "either horizontally, vertically, or diagonally.                  \n"
         << "                                                                 \n"
         << "Players take turns placing one of their pieces into an empty     \n"
         << "space anywhere on the board, then choosing one of the four       \n"
         << "board quadrants to rotate 90 degrees left or right.              \n"
         << "                                                                 \n"
         << "If both players get five in a row at the same time, or the       \n"
         << "last move is played with no five in a row, the game is a tie.    \n"
         << "If a player makes five a row by placing a piece, there is no need\n"
         << "to rotate a quadrant and the player wins immediately.            \n"
         << "                                                                 \n"
         << "     Play online at:  https://perfect-pentago.net                \n"
         << "     Purchase at:     www.mindtwisterusa.com                     \n"
         << "                                                                 \n"
         << "For each move provide four inputs:                               \n"
         << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
         << "For instance input of B32R places the next piece at B3 and then  \n"
         << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
         << "                                                                 \n"
         << "At any point enter 'x' to exit the program or 'i' to display instructions." << endl;
} // end displayInstructions()

class Board {                          // Keeps a user's review of a restaurant
public:
    void displayBoard();
    void makeMove(char pieceToMove, char userRow, char userCol,bool &spaceEmpty);
    void rotateQuadrant(char userQuadrant, char userRotation);
    bool checkForWinX();
    bool checkForWinO();


private:

    char A1,A2,A3,A4,A5,A6,
            B1,B2,B3,B4,B5,B6,
            C1,C2,C3,C4,C5,C6,
            D1,D2,D3,D4,D5,D6,
            E1,E2,E3,E4,E5,E6,
            F1,F2,F3,F4,F5,F6;

    vector<vector<char> > boardQuadrants;
    vector<vector<char> > boardQuadOne = {{A1, A2, A3},
                                          {B1, B2, B3},
                                          {C1, C2, C3}};
    vector<vector<char> > boardQuadTwo = {{A4,A5,A6},
                                          {B4,B5,B6},
                                          {C4,C5,C6}};
    vector<vector<char> > boardQuadThree = {{D1,D2,D3},
                                            {E1,E2,E3},
                                            {F1,F2,F3}};
    vector<vector<char> > boardQuadFour = {{D4,D5,D6},
                                           {E4,E5,E6},
                                           {F4,F5,F6}};
    vector<char> fiveInRow{'.','.','.','.','.','.'};
    bool firstRun = true;
    bool boardFull = false;
    bool winO = false;
    bool winX = false;
};

// Function makes all vector values to '.' default
void defaulter(vector<vector <char> > &board){
    for (long unsigned int i = 0; i < board.size(); i++) {
        for (long unsigned int j = 0; j < board[i].size(); j++)
            board[i][j] = '.';
    }
}

bool loopAllPieces(vector<vector <char>> board){
    for(long unsigned int i = 0; i< board.size();i++){
        for(long unsigned int j = 0; j < board[i].size();j++){
            if(board[i][j] == '.'){
                return false;
            }
        }
    }
    return true;
}

// Sets the restaurant's name
void Board::displayBoard() {
    if(firstRun == true){
        cout << "Welcome to Pentago, where you try to get 5 of your pieces in a line.\n"
             << "At any point enter 'x' to exit or 'i' for instructions. \n";
        defaulter(boardQuadOne);
        defaulter(boardQuadTwo);
        defaulter(boardQuadThree);
        defaulter(boardQuadFour);
        firstRun = false;

    }
    if(checkForWinO() == true){
        winO = true;
    }
    if(checkForWinX() == true){
        winX = true;
    }
    if(winX && winO){
        cout << "*** Both X and O have won.  Game is a tie." << endl;
    }
    else if(winX){
        cout << "*** X has won the game!" << endl;
    }
    else if(winO){
        cout << "*** O has won the game!" << endl;
    }
    if ((loopAllPieces(boardQuadOne))&&(loopAllPieces(boardQuadTwo))&&
        (loopAllPieces(boardQuadThree))&&(loopAllPieces(boardQuadFour))) {
        cout << "    *** No one has won.  Game is a tie." << endl;
        boardFull = true;
    }

    cout << "\n    1   2   3   4   5   6   \n"
         << "  1-----------------------2 \n"
         << "A | " << boardQuadOne[0][0] << "   " << boardQuadOne[0][1] << "   " << boardQuadOne[0][2] << " | " << boardQuadTwo[0][0] << "   " << boardQuadTwo[0][1] << "   " << boardQuadTwo[0][2] << " | A\n"
         << "  |           |           | \n"
         << "B | " << boardQuadOne[1][0] << "   " << boardQuadOne[1][1] << "   " << boardQuadOne[1][2] << " | " << boardQuadTwo[1][0] << "   " << boardQuadTwo[1][1] << "   " << boardQuadTwo[1][2] << " | B\n"
         << "  |           |           | \n"
         << "C | " << boardQuadOne[2][0] << "   " << boardQuadOne[2][1] << "   " << boardQuadOne[2][2] << " | " << boardQuadTwo[2][0] << "   " << boardQuadTwo[2][1] << "   " << boardQuadTwo[2][2] << " | C\n"
         <<   "  |-----------+-----------| \n"
         <<   "D | " << boardQuadThree[0][0] << "   " << boardQuadThree[0][1] << "   " << boardQuadThree[0][2] << " | " << boardQuadFour[0][0] << "   " << boardQuadFour[0][1] << "   " << boardQuadFour[0][2] << " | D\n"
         <<   "  |           |           | \n"
         <<   "E | " << boardQuadThree[1][0] << "   " << boardQuadThree[1][1] << "   " << boardQuadThree[1][2] << " | " << boardQuadFour[1][0] << "   " << boardQuadFour[1][1] << "   " << boardQuadFour[1][2] << " | E\n"
         <<   "  |           |           | \n"
         <<   "F | " << boardQuadThree[2][0] << "   " << boardQuadThree[2][1] << "   " << boardQuadThree[2][2] << " | " << boardQuadFour[2][0] << "   " << boardQuadFour[2][1] << "   " << boardQuadFour[2][2] << " | F\n"
         <<   "  3-----------------------4  \n"
         <<   "    1   2   3   4   5   6    " << endl;
    if(boardFull == true){
        cout << " Thanks for playing.  Exiting... " << endl;
        exit(0);
    }
    if(winO || winX){
        cout << "Thanks for playing.  Exiting... " << endl;
        exit(0);
    }
}

bool validInputRow(char userRow) {
    if((userRow>='A')&&(userRow<='F')){
        return true;
    }
    return false;
}

bool validInputCol(char userCol) {
    int column = userCol - '0';
    if((column>0)&&(column<=6)){
        return true;
    }
    return false;
}

bool validInputRotation(char userRotation){
    if(userRotation=='R'){
        return true;
    }
    if(userRotation=='L'){
        return true;
    }
    return false;
}

bool validInputQuadrant(char userQuadrant){
    int quadrant = userQuadrant - '0';
    if((quadrant>=1)&&(quadrant<=4)){
        return true;
    }
    return false;
}

bool validMove(char tempChar){
    if(tempChar == '.'){
        return true;
    }
    return false;
}


void Board::makeMove(char pieceToMove, char userRow, char userCol,bool &spaceEmpty) {
    int column = userCol - '0';
    int row = userRow - 'A';
    char tempChar = '.';
    spaceEmpty = true;
    if((column < 4)&& (row < 3)){
        tempChar = boardQuadOne[row][column - 1];
        if(validMove(tempChar) == true) {
            boardQuadOne[row][column - 1] = pieceToMove;
        }
        else {
            spaceEmpty = false;
        }
    }
    else if((column > 3)&& (row < 3)){
        tempChar = boardQuadTwo[row][column - 4];
        if(validMove(tempChar) == true) {
            boardQuadTwo[row][column - 4] = pieceToMove;
        }
        else {
            spaceEmpty = false;
        }
    }
    else if((column < 4)&& (row > 2)){
        tempChar = boardQuadThree[row - 3][column - 1];
        if(validMove(tempChar) == true) {
            boardQuadThree[row - 3][column - 1] = pieceToMove;
        }
        else {
            spaceEmpty = false;
        }
    }
    else if((column > 3)&& (row > 2)){
        tempChar = boardQuadFour[row - 3][column - 4];
        if(validMove(tempChar) == true) {
            boardQuadFour[row - 3][column - 4] = pieceToMove;
        }
        else {
            spaceEmpty = false;
        }
    }
}

void rotateRight(vector<vector <char> > &board){
    int sizeOfVector = board.size();
    for (int i = 0; i < sizeOfVector; i++) {
        for (int j = i; j < sizeOfVector; j++) {
            int temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
    for (int i = 0; i < sizeOfVector; i++) {
        for (int j = 0; j < (sizeOfVector / 2); j++) {
            int temp = board[i][j];
            board[i][j] = board[i][sizeOfVector - 1 - j];
            board[i][sizeOfVector - 1 - j] = temp;
        }
    }
}

bool Board::checkForWinX() {
    char tempPieceX = 'X';

    if((tempPieceX == boardQuadOne[0][0])&&
        (tempPieceX == boardQuadOne[1][0])&&
        (tempPieceX == boardQuadOne[2][0])&&
        (tempPieceX == boardQuadThree[0][0])&&
        (tempPieceX == boardQuadThree[1][0])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][1])&&
       (tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[2][1])&&
       (tempPieceX == boardQuadThree[0][1])&&
       (tempPieceX == boardQuadThree[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][2])&&
       (tempPieceX == boardQuadOne[1][2])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadThree[1][2])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[0][0])&&
       (tempPieceX == boardQuadTwo[1][0])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[1][0])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[0][1])&&
       (tempPieceX == boardQuadTwo[1][1])&&
       (tempPieceX == boardQuadTwo[2][1])&&
       (tempPieceX == boardQuadFour[0][1])&&
       (tempPieceX == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[0][2])&&
       (tempPieceX == boardQuadTwo[1][2])&&
       (tempPieceX == boardQuadTwo[2][2])&&
       (tempPieceX == boardQuadFour[0][2])&&
       (tempPieceX == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][0])&&
       (tempPieceX == boardQuadOne[2][0])&&
       (tempPieceX == boardQuadThree[0][0])&&
       (tempPieceX == boardQuadThree[1][0])&&
       (tempPieceX == boardQuadThree[2][0])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[2][1])&&
       (tempPieceX == boardQuadThree[0][1])&&
       (tempPieceX == boardQuadThree[1][1])&&
       (tempPieceX == boardQuadThree[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][2])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadThree[1][2])&&
       (tempPieceX == boardQuadThree[2][2])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[1][0])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[1][0])&&
       (tempPieceX == boardQuadFour[2][0])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[1][1])&&
       (tempPieceX == boardQuadTwo[2][1])&&
       (tempPieceX == boardQuadFour[0][1])&&
       (tempPieceX == boardQuadFour[1][1])&&
       (tempPieceX == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[1][2])&&
       (tempPieceX == boardQuadTwo[2][2])&&
       (tempPieceX == boardQuadFour[0][2])&&
       (tempPieceX == boardQuadFour[1][2])&&
       (tempPieceX == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][0])&&
       (tempPieceX == boardQuadOne[0][1])&&
       (tempPieceX == boardQuadOne[0][2])&&
       (tempPieceX == boardQuadTwo[0][0])&&
       (tempPieceX == boardQuadTwo[0][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][0])&&
       (tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[1][2])&&
       (tempPieceX == boardQuadTwo[1][0])&&
       (tempPieceX == boardQuadTwo[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[2][0])&&
       (tempPieceX == boardQuadOne[2][1])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadTwo[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadThree[0][0])&&
       (tempPieceX == boardQuadThree[0][1])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[0][1])){
        return true;
    }
    if((tempPieceX == boardQuadThree[1][0])&&
       (tempPieceX == boardQuadThree[1][1])&&
       (tempPieceX == boardQuadThree[1][2])&&
       (tempPieceX == boardQuadFour[1][0])&&
       (tempPieceX == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadThree[2][0])&&
       (tempPieceX == boardQuadThree[2][1])&&
       (tempPieceX == boardQuadThree[2][2])&&
       (tempPieceX == boardQuadFour[2][0])&&
       (tempPieceX == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][1])&&
       (tempPieceX == boardQuadOne[0][2])&&
       (tempPieceX == boardQuadTwo[0][0])&&
       (tempPieceX == boardQuadTwo[0][1])&&
       (tempPieceX == boardQuadTwo[0][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[1][2])&&
       (tempPieceX == boardQuadTwo[1][0])&&
       (tempPieceX == boardQuadTwo[1][1])&&
       (tempPieceX == boardQuadTwo[1][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[2][1])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadTwo[2][1])&&
       (tempPieceX == boardQuadTwo[2][2])){
        return true;
    }
    if((tempPieceX == boardQuadThree[0][1])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[0][1])&&
       (tempPieceX == boardQuadFour[0][2])){
        return true;
    }
    if((tempPieceX == boardQuadThree[1][1])&&
       (tempPieceX == boardQuadThree[1][2])&&
       (tempPieceX == boardQuadFour[1][0])&&
       (tempPieceX == boardQuadFour[1][1])&&
       (tempPieceX == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceX == boardQuadThree[2][1])&&
       (tempPieceX == boardQuadThree[2][2])&&
       (tempPieceX == boardQuadFour[2][0])&&
       (tempPieceX == boardQuadFour[2][1])&&
       (tempPieceX == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][0])&&
       (tempPieceX == boardQuadOne[2][1])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadFour[1][0])&&
       (tempPieceX == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][0])&&
       (tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadOne[1][1])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadFour[1][1])&&
       (tempPieceX == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceX == boardQuadOne[0][1])&&
       (tempPieceX == boardQuadOne[1][2])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadFour[0][1])&&
       (tempPieceX == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[0][2])&&
       (tempPieceX == boardQuadTwo[1][1])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadThree[1][1])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[1][1])&&
       (tempPieceX == boardQuadTwo[2][0])&&
       (tempPieceX == boardQuadThree[0][2])&&
       (tempPieceX == boardQuadThree[1][1])&&
       (tempPieceX == boardQuadThree[2][0])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[1][2])&&
       (tempPieceX == boardQuadTwo[2][1])&&
       (tempPieceX == boardQuadFour[0][0])&&
       (tempPieceX == boardQuadThree[1][2])&&
       (tempPieceX == boardQuadThree[2][1])){
        return true;
    }
    if((tempPieceX == boardQuadTwo[0][1])&&
       (tempPieceX == boardQuadTwo[1][0])&&
       (tempPieceX == boardQuadOne[2][2])&&
       (tempPieceX == boardQuadThree[0][1])&&
       (tempPieceX == boardQuadThree[1][0])){
        return true;
    }
    return false;
}

bool Board::checkForWinO() {
    char tempPieceO = 'O';

    if((tempPieceO == boardQuadOne[0][0])&&
       (tempPieceO == boardQuadOne[1][0])&&
       (tempPieceO == boardQuadOne[2][0])&&
       (tempPieceO == boardQuadThree[0][0])&&
       (tempPieceO == boardQuadThree[1][0])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][1])&&
       (tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[2][1])&&
       (tempPieceO == boardQuadThree[0][1])&&
       (tempPieceO == boardQuadThree[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][2])&&
       (tempPieceO == boardQuadOne[1][2])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadThree[1][2])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[0][0])&&
       (tempPieceO == boardQuadTwo[1][0])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[1][0])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[0][1])&&
       (tempPieceO == boardQuadTwo[1][1])&&
       (tempPieceO == boardQuadTwo[2][1])&&
       (tempPieceO == boardQuadFour[0][1])&&
       (tempPieceO == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[0][2])&&
       (tempPieceO == boardQuadTwo[1][2])&&
       (tempPieceO == boardQuadTwo[2][2])&&
       (tempPieceO == boardQuadFour[0][2])&&
       (tempPieceO == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][0])&&
       (tempPieceO == boardQuadOne[2][0])&&
       (tempPieceO == boardQuadThree[0][0])&&
       (tempPieceO == boardQuadThree[1][0])&&
       (tempPieceO == boardQuadThree[2][0])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[2][1])&&
       (tempPieceO == boardQuadThree[0][1])&&
       (tempPieceO == boardQuadThree[1][1])&&
       (tempPieceO == boardQuadThree[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][2])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadThree[1][2])&&
       (tempPieceO == boardQuadThree[2][2])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[1][0])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[1][0])&&
       (tempPieceO == boardQuadFour[2][0])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[1][1])&&
       (tempPieceO == boardQuadTwo[2][1])&&
       (tempPieceO == boardQuadFour[0][1])&&
       (tempPieceO == boardQuadFour[1][1])&&
       (tempPieceO == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[1][2])&&
       (tempPieceO == boardQuadTwo[2][2])&&
       (tempPieceO == boardQuadFour[0][2])&&
       (tempPieceO == boardQuadFour[1][2])&&
       (tempPieceO == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][0])&&
       (tempPieceO == boardQuadOne[0][1])&&
       (tempPieceO == boardQuadOne[0][2])&&
       (tempPieceO == boardQuadTwo[0][0])&&
       (tempPieceO == boardQuadTwo[0][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][0])&&
       (tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[1][2])&&
       (tempPieceO == boardQuadTwo[1][0])&&
       (tempPieceO == boardQuadTwo[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[2][0])&&
       (tempPieceO == boardQuadOne[2][1])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadTwo[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadThree[0][0])&&
       (tempPieceO == boardQuadThree[0][1])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[0][1])){
        return true;
    }
    if((tempPieceO == boardQuadThree[1][0])&&
       (tempPieceO == boardQuadThree[1][1])&&
       (tempPieceO == boardQuadThree[1][2])&&
       (tempPieceO == boardQuadFour[1][0])&&
       (tempPieceO == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadThree[2][0])&&
       (tempPieceO == boardQuadThree[2][1])&&
       (tempPieceO == boardQuadThree[2][2])&&
       (tempPieceO == boardQuadFour[2][0])&&
       (tempPieceO == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][1])&&
       (tempPieceO == boardQuadOne[0][2])&&
       (tempPieceO == boardQuadTwo[0][0])&&
       (tempPieceO == boardQuadTwo[0][1])&&
       (tempPieceO == boardQuadTwo[0][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[1][2])&&
       (tempPieceO == boardQuadTwo[1][0])&&
       (tempPieceO == boardQuadTwo[1][1])&&
       (tempPieceO == boardQuadTwo[1][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[2][1])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadTwo[2][1])&&
       (tempPieceO == boardQuadTwo[2][2])){
        return true;
    }
    if((tempPieceO == boardQuadThree[0][1])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[0][1])&&
       (tempPieceO == boardQuadFour[0][2])){
        return true;
    }
    if((tempPieceO == boardQuadThree[1][1])&&
       (tempPieceO == boardQuadThree[1][2])&&
       (tempPieceO == boardQuadFour[1][0])&&
       (tempPieceO == boardQuadFour[1][1])&&
       (tempPieceO == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceO == boardQuadThree[2][1])&&
       (tempPieceO == boardQuadThree[2][2])&&
       (tempPieceO == boardQuadFour[2][0])&&
       (tempPieceO == boardQuadFour[2][1])&&
       (tempPieceO == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][0])&&
       (tempPieceO == boardQuadOne[2][1])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadFour[1][0])&&
       (tempPieceO == boardQuadFour[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][0])&&
       (tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadOne[1][1])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadFour[1][1])&&
       (tempPieceO == boardQuadFour[2][2])){
        return true;
    }
    if((tempPieceO == boardQuadOne[0][1])&&
       (tempPieceO == boardQuadOne[1][2])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadFour[0][1])&&
       (tempPieceO == boardQuadFour[1][2])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[0][2])&&
       (tempPieceO == boardQuadTwo[1][1])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadThree[1][1])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[1][1])&&
       (tempPieceO == boardQuadTwo[2][0])&&
       (tempPieceO == boardQuadThree[0][2])&&
       (tempPieceO == boardQuadThree[1][1])&&
       (tempPieceO == boardQuadThree[2][0])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[1][2])&&
       (tempPieceO == boardQuadTwo[2][1])&&
       (tempPieceO == boardQuadFour[0][0])&&
       (tempPieceO == boardQuadThree[1][2])&&
       (tempPieceO == boardQuadThree[2][1])){
        return true;
    }
    if((tempPieceO == boardQuadTwo[0][1])&&
       (tempPieceO == boardQuadTwo[1][0])&&
       (tempPieceO == boardQuadOne[2][2])&&
       (tempPieceO == boardQuadThree[0][1])&&
       (tempPieceO == boardQuadThree[1][0])){
        return true;
    }
    return false;
}

void Board::rotateQuadrant(char userQuadrant, char userRotation) {
    int quadrant = userQuadrant - '0';
    switch (quadrant) {
        case 1:
            if(userRotation == 'R') {
                rotateRight(boardQuadOne);
            }
            else if(userRotation == 'L'){
                rotateRight(boardQuadOne);
                rotateRight(boardQuadOne);
                rotateRight(boardQuadOne);
            }
            break;
        case 2:
            if(userRotation == 'R') {
                rotateRight(boardQuadTwo);
            }
            else if(userRotation == 'L'){
                rotateRight(boardQuadTwo);
                rotateRight(boardQuadTwo);
                rotateRight(boardQuadTwo);
            }
            break;
        case 3:
            if(userRotation == 'R') {
                rotateRight(boardQuadThree);
            }
            else if(userRotation == 'L'){
                rotateRight(boardQuadThree);
                rotateRight(boardQuadThree);
                rotateRight(boardQuadThree);
            }
            break;
        case 4:
            if(userRotation == 'R') {
                rotateRight(boardQuadFour);
            }
            else if(userRotation == 'L'){
                rotateRight(boardQuadFour);
                rotateRight(boardQuadFour);
                rotateRight(boardQuadFour);
            }
            break;
    }
}

int main() {
    int turnCount = 1;
    char userRow;
    char userCol;
    char userQuadrant;
    char userRotation;
    char pieceToMove = 'X';
    bool validMove = true;
    bool spaceEmpty = true;
    char userInput;
    Board theBoard;            // Create the boardQuadOne as an instance of the Board class
    theBoard.displayBoard();
    cout << turnCount << ".Enter row, column, quadrant, direction for X:";
    cin >> userInput;
    userInput = toupper(userInput);
    while((userInput != 'x')&&(userInput != 'X')) {
        validMove = false;
        spaceEmpty = false;
        if(userInput == 'I'){
            displayInstructions();     // Display game instructinos
            theBoard.displayBoard();
            cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
        }
        else {
            cin >> userCol >> userQuadrant >> userRotation;
            userRotation = toupper(userRotation);
            switch (userInput) {
                case 'A':
                    userRow = 'A';
                    if (validInputRow(userRow) == true) {
                        if (validInputCol(userCol) == true) {
                            if(validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 'B':
                    userRow = 'B';
                    if (validInputRow(userRow) == true) {
                        if (validInputCol(userCol)== true) {
                            if (validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }

                    break;
                case 'C':
                    userRow = 'C';
                    if (validInputRow(userRow)== true) {
                        if (validInputCol(userCol)== true) {
                            if (validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }

                    break;
                case 'D':
                    userRow = 'D';
                    if (validInputRow(userRow)== true) {
                        if (validInputCol(userCol)== true) {
                            if (validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }

                    break;
                case 'E':
                    userRow = 'E';
                    if (validInputRow(userRow)== true) {
                        if (validInputCol(userCol)== true) {
                            if (validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }

                    break;
                case 'F':
                    userRow = 'F';
                    if (validInputRow(userRow)== true) {
                        if (validInputCol(userCol)== true) {
                            if (validInputQuadrant(userQuadrant) == true) {
                                if(validInputRotation(userRotation) == true) {
                                    theBoard.makeMove(pieceToMove, userRow, userCol,spaceEmpty);
                                    if(spaceEmpty == true) {
                                        theBoard.rotateQuadrant(userQuadrant, userRotation);
                                        theBoard.displayBoard();
                                        validMove = true;
                                    }
                                }
                            }
                        }
                    }
                    break;
                default :
                    userRow = userInput;
            }
        }
        if(validMove == true) {
            if (userInput != 'I') {
                if (pieceToMove == 'X') {
                    pieceToMove = 'O';
                } else {
                    pieceToMove = 'X';
                }
                turnCount++;
            }
            cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
        }
        if ((validMove == false)&&(userInput!='X')&&(userInput!='I')){
            if(validInputRow(userRow) == false){
                cout << "    *** Invalid move row.  Please retry." << endl;
                theBoard.displayBoard();
                cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
            }
            else if(validInputCol(userCol) == false){
                cout << "    *** Invalid move column.  Please retry." << endl;
                theBoard.displayBoard();
                cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
            }
            else if(validInputQuadrant(userQuadrant) == false){
                cout << "    *** Selected quadrant is invalid.  Please retry." << endl;
                theBoard.displayBoard();
                cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
            }
            else if(validInputRotation(userRotation) == false){
                cout << "    *** Quadrant rotation direction is invalid.  Please retry." << endl;
                theBoard.displayBoard();
                cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
            }
            else if(spaceEmpty == false){
                cout << "    *** That board location is already taken.  Please retry." << endl;
                theBoard.displayBoard();
                cout << turnCount << ". Enter row, column, quadrant, direction for " << pieceToMove << ": " << endl;
            }
            else{
                cout << turnCount << ". Enter row, column, quadrant, direction for... " << pieceToMove << ": " << endl;
                if (userInput != 'I') {
                    theBoard.displayBoard();
                }
            }
        }
        cin >> userInput;
        userInput = toupper(userInput);
    }
    cout << "Exiting program... " << endl;
    return 0;
}
