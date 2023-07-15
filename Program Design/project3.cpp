/* ----------------------------------------------------------- 
    Program 1: Vigenere 
    
    Author: Burhanuddin Cutlerywala and Aqsa Arif
    Class: CS 141, Spring 2020.  Tues 1pm & 3pm respectively lab
    System: Zybooks
    
   -----------------------------------------------------------
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>    // Allows us to work with strlen and strcpy
using namespace std;

// This Function performs the binary search on a Word to find in Dictionary
bool binarySearch( char prac[],int numberOfWords, char dictionary[][81]){
    int low, mid, high;    // array indices for binary search
    int searchResult;      // Stores 0 if search succeeded
    low = 0;
    high = numberOfWords - 1; // Amount of words in dictionary to loop thorugh
    while (low <= high) {     
       mid = (low + high) / 2;
       searchResult = strcmp(prac, dictionary[mid]); // If found the word then returns true
       if (searchResult == 0) {
          return true;                   // found the key
          } 
          else if (searchResult < 0){    // If its below then gotta search in the first half of the dictd
            high = mid - 1;              //  Key should be before mid
            }
            else{
               low = mid + 1;            // Key should be after mid
            }
      }  //end while
      return false;
}

// This function checks if the work is in dictionary
void checkIfWordInDictionary(char encryptKey[], char userWord[], char secretMessage[], char alphas[27][27], 
                             char keyWordEncrypted[81], char dictionary[][81], int numberOfWords, char AnyArray[], 
                             int &numWordsInDecode, int numWordsInSentence, char decoding2dArray[81][81], int amountofWords,
                             char* newDecode, int space, int &theNumOfEnglishWords)
{
   int counter = 0 ;
   //Going through the decoding string
   for(int plainLetterText = 0; secretMessage[plainLetterText] != '\0'; plainLetterText++){
   //If finds space goes to the next row in the 2d array of decoding2dArray
      if(secretMessage[plainLetterText] != ' ' && secretMessage[plainLetterText] != '\0'){
         decoding2dArray[amountofWords][counter] = secretMessage[plainLetterText];
         counter++;
      }
      else{
         decoding2dArray[amountofWords][counter] = '\0';
         amountofWords++;
         counter = 0;
         continue;
      }
   }
   amountofWords++; 
   for(int check = 0 ; check < amountofWords; check++){
      if(binarySearch(decoding2dArray[check], numberOfWords, dictionary)){
         theNumOfEnglishWords++;
      }
   }
}

// This function decodes the ecrypted text by using the keyword
void decodeSecretMessage(char encryptKey[], char userWord[], char secretMessage[], char alphas[27][27], 
                         char keyWordEncrypted[81], char dictionary[][81], int numberOfWords, int &numWordsInDecode, 
                         int &theNumOfEnglishWords)
{
   int numWordsInSentence;
   char decoding2dArray[81][81];
   int amountofWords;
   char* newDecode;
   int space = 0;
   int i;
   int counter;
   int totalLength = (strlen(userWord) / strlen(encryptKey));
   int lenEncryptKey = strlen(encryptKey);
   int lenUserWord = strlen(userWord);
   for(int defaulter = 0 ; defaulter < 81; defaulter++){
      keyWordEncrypted[defaulter] = '\0';
      }
      
   for(int defaulter = 0; defaulter < 81; defaulter++){
      secretMessage[defaulter] = '\0';
      }
   //Outer loop is Looping through the length of userWord (Word to be encryted)
   for( i = 0; i < totalLength; i++){
      //Inner loop goes through encryptWord to add letter by letter
      for(int j = 0; j < lenEncryptKey; j++ ){
         counter = (lenEncryptKey * i) + j;
         keyWordEncrypted[counter] = encryptKey[j];
      }
   }
   for (int j=0; j < lenUserWord % lenEncryptKey; j++){
      counter = (lenEncryptKey * i) + j;
      keyWordEncrypted[counter] = encryptKey[j];
   }
   int lengthOfEncryptKey = strlen(keyWordEncrypted);
   keyWordEncrypted[lengthOfEncryptKey] = '\0';
   for(int i = 0 ; userWord[i] != '\0'; i++){
      int counter = keyWordEncrypted[i] - 97;
      if(isalpha(userWord[i])){
         for(int j = 0 ; j < 26; j++){
            if(alphas[counter][j] == userWord[i]){
               secretMessage[i] = alphas[0][j];
            }
         }
      }
      else{
         secretMessage[i] = userWord[i];
      }
   }
   char AnyArray[81];
   int secretMessageLength = strlen(secretMessage);
   for(int i = 0 ; i < secretMessageLength; i++){
      if(secretMessage[i] == '\n'){
         secretMessage[i] = '\0';
      }
   }
   newDecode = secretMessage;
   checkIfWordInDictionary(encryptKey, userWord, secretMessage, alphas, 
                           keyWordEncrypted, dictionary, numberOfWords, AnyArray, 
                           numWordsInDecode, numWordsInSentence, decoding2dArray, 
                           amountofWords, newDecode, space, theNumOfEnglishWords);
}

// This function encodes a text by using key
void encodeSecretMessage(char encryptKey[], char userWord[], char secretMessage[], char alphas[27][27], 
                         char keyWordEncrypted[81], char dictionary[][81])
{
   int i;
   int counter;
   int totalLength = (strlen(userWord) / strlen(encryptKey));
   int lenEncryptKey = strlen(encryptKey);
   int lenUserWord = strlen(userWord);
   //Outer loop is Looping through the length of userWord (Word to be encryted)
   for(int defaulter = 0; defaulter < 81; defaulter++){
      keyWordEncrypted[defaulter] = '\0';
   }
   for( i = 0; i < totalLength; i++) {  //Inner loop goes through encryptWord to add letter by letter
      for(int j = 0; j < lenEncryptKey;j++ ){
         counter = (lenEncryptKey * i) + j;
         keyWordEncrypted[counter] = encryptKey[j];
      }
   }
   for(int defaulter = 0; defaulter < 81; defaulter++){ //Makes all chars in the array equal to null
      secretMessage[defaulter] = '\0';
   }
   
   for (int j=0; j < (lenUserWord % lenEncryptKey) ; j++) { //Goes through the encryptKey to repeat the word
      counter = (lenEncryptKey * i) + j;
      keyWordEncrypted[counter] = encryptKey[j];
   }
   for(int i = 0 ; userWord[i] != '\0'; i++){  // Goes through the alpha array to find out which col and row equals to the letter
      int counter = keyWordEncrypted[i] - 97;
      int counterNumTwo = userWord[i] - 97;
      if(userWord[i] != ' '){  // Check if spaces are in the word
         secretMessage[i] = alphas[counter][counterNumTwo]; // Goes through 2d array to decrypt
      }
      else{
         secretMessage[i] = userWord[i];
      }
   }
   
   
}

// This function makes the alphabet table
void makeAlphaArray(char alphas[27][27]){
   //this is the starting char in each row that dictates what the last letter in each row will be
   char startingAlpha = 'a';
   //This var keeps changing to be put in the array
   char currentLetter = 'a';
   //Goes through each charachter to store in array
   for(int i=0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
         // If letter is equal to ascii chart after Z, then resets to A
         if(currentLetter == 'z'+1) {
            currentLetter = 'a';
         }
         //Storing 2d array with the letter
         alphas[i][j] = currentLetter;
         //Increments every time to get next char of alphas
         currentLetter++;
      }
      //Increments the leeter that starts the row of the alphabets
      currentLetter = ++startingAlpha;
   }
}

// This function makes the dictionary
void makeDictionary(char dictionary[][81], int &numberOfWords){
   ifstream inStream;
   inStream.open( "dictionary.txt");
   if( !inStream.is_open()) {
      cout << "Could not find dictionary.txt.  Exiting..." << endl;
      exit( -1);
   }
   char theWord[ 81];    // declare input space to be clearly larger than largest word
   while( inStream >> theWord) {
      //lowers every word
      int tempCounter = strlen(theWord)-1;
      for(int i = 0; i < tempCounter; i++){
         theWord[i] = tolower(theWord[i]);
      }
      //Makes length of word less than 3
      if(tempCounter + 1 >= 3){
         for(int i = 0; theWord[i] != '\0'; i++){
            dictionary[numberOfWords][i] = theWord[i];
         }
         numberOfWords++;
      }
   }
   inStream.close();
   cout << numberOfWords<<" words of size >= 3 were read in from dictionary. " << endl;
   cout << endl;
}

// This function lets use extract words from secret text and use for decryption
void makeSecretAgentDictionary(char encryptKey[], char userWord[], char secretMessage[], char alphas[27][27], 
                               char keyWordEncrypted[81], char dictionary[][81], int numberOfWords, int &numWordsInDecode, 
                               int &theNumOfEnglishWords)
{                                  
   int max = 0; 
   ifstream inStream;
   inStream.open( "TheSecretAgentByJosephConrad.txt");
   if( !inStream.is_open()) {
      cout << "Could not find TheSecretAgentByJosephConrad.txt.  Exiting..." << endl;
      exit( -1);
   }
   char textWords[ 81];    // declare input space to be clearly larger than largest word
   //char *pointer = textWords;
   while( inStream >> textWords) {
      //lowers every word
      int temp = strlen(textWords);
      for(int i = 0; i < temp; i++){
         textWords[i] = tolower(textWords[i]);
      }
      if(isalpha(*textWords) && strlen(textWords) >= 3){
         
         decodeSecretMessage(textWords, userWord, secretMessage, alphas, 
                             keyWordEncrypted, dictionary, numberOfWords, numWordsInDecode, 
                             theNumOfEnglishWords);
                             
         if(theNumOfEnglishWords > max){
            max = theNumOfEnglishWords;
            cout << max << " words found using keyword: " << textWords << " giving:" << endl;
            int length = strlen(secretMessage);
            secretMessage[length] = '\0';
            cout << "   " << secretMessage << endl;
         }
         theNumOfEnglishWords = 0;
      }
   }
   inStream.close();
}

//---------------------------------------------------------------------------
int main(){
   //This is the message that the person will recieve after going through option 2
   int numWordsInDecode;
   char secretMessage[81];                //The final output of decoding or ecoding
   char userWord[81];                     // What user puts in, either to encode or decode
   char encryptKey[81];                   // The word to be repeated
   char keyWordEncrypted[81];             // encryptkey when it is repeated 
   char secretAgentDictionary[93297][81]; //Array to store The words in the secret agent text
   char dictionary[21736][81];            // the 2d dict array
   int numberOfWords = 0;
   int theNumOfEnglishWords = 0;
   int menuOption;                   // Userinput for menu option
   char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
   char alphas[27][27];		          // the 2d alphabet array
   makeDictionary(dictionary,numberOfWords); // makes the 2d dict array
   makeAlphaArray(alphas);	          // makes the alpha array in the beginning
 //-----------------------------------------------------------------------------------
   
   // Display menu and handle menu options
   cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
    cin >> menuOption;
    returnCharacter = cin.get();  
    // Read and discard the return character at the end of the above input line.
    // This is necessary because otherwise a subsequent cin.getline() reads it as
    // an empty line of input.
    // declare an input stream

    switch (menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
        {
           cout << "Enter a word to be looked up in dictionary: ";
           cin >> userWord;
           int tempUser2 = strlen(userWord);
           for (int i = 0; i < tempUser2 - 1; i++) {
              userWord[i] = tolower(userWord[i]);
            }
            if (binarySearch(userWord, numberOfWords, dictionary)) {
               cout << userWord << " IS in the dictionary.\n";
            }
            else{
               cout << userWord << " is NOT in the dictionary.\n";
            }
            break;
         }
        case 2: // Encode some text
        {
           cout << "Enter the text to be encoded: ";
           fgets(userWord, 81, stdin);
           int tempUser = strlen(userWord);
           for (int i = 0; i < tempUser; i++) { // makes the word lowercase
              userWord[i] = tolower(userWord[i]);
            }
            for (int i = 0; i < tempUser; i++) {
               if (userWord[i] == '\n') {
                  userWord[i] = '\0';
               }
            }
            cout << "Enter a keyword for Vigenere encryption: ";
            fgets(encryptKey, 81, stdin);
            int tempEnc = strlen(encryptKey);
            for (int i = 0; i < tempEnc; i++) {
               encryptKey[i] = tolower(encryptKey[i]);
            }
            for (int i = 0; i < tempEnc; i++) { // makes the word lowercase
               if (encryptKey[i] == '\n') {
                  encryptKey[i] = '\0';
               }
            }
            encodeSecretMessage(encryptKey, userWord, secretMessage, alphas, keyWordEncrypted, dictionary);
            cout << "Keyword, plainText and ciphertext are:  \n";
            cout << keyWordEncrypted << endl;
            cout << userWord << endl;
            cout << secretMessage << endl;
            break;
        }
        case 3:
        {// Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            fgets(userWord, 81, stdin);
            int tempUser = strlen(userWord);
            for (int i = 0; i < tempUser; i++) {
               userWord[i] = tolower(userWord[i]);
            }
            for (int i = 0; i < tempUser; i++) {
               if (userWord[i] == '\n') {
                  userWord[i] = '\0';
               }
            }
            cout << "Enter a Vigenere keyword to be tried: ";
            fgets(encryptKey, 81, stdin);
            int tempEnc = strlen(encryptKey);
            for (int i = 0; i < tempEnc; i++) {
               encryptKey[i] = tolower(encryptKey[i]);
            }
            for (int i = 0; i < tempEnc; i++) {
               if (encryptKey[i] == '\n') {
                  encryptKey[i] = '\0';
               }
            }
            decodeSecretMessage(encryptKey, userWord, secretMessage, alphas, keyWordEncrypted, 
                                 dictionary, numberOfWords, numWordsInDecode, theNumOfEnglishWords);

            cout << theNumOfEnglishWords << " words found using keyword: " << encryptKey << " giving:" << endl;
            cout << "   " << secretMessage << endl;
            break;
        }
        case 4:{ // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            fgets(userWord, 81, stdin);
            int tempUser = strlen(userWord);
            for (int i = 0; i < tempUser; i++) {
               userWord[i] = tolower(userWord[i]);
            }
            for (int i = 0; i < tempUser; i++) {
               if (userWord[i] == '\n') {
                  userWord[i] = '\0';
               }
            }
            makeSecretAgentDictionary(encryptKey, userWord, secretMessage, alphas, 
                                      keyWordEncrypted, dictionary, numberOfWords, numWordsInDecode, 
                                      theNumOfEnglishWords);
            break;
         }
        case 5:{ // exit program
            cout << "Exiting program" << endl;
            exit(0);
        }

        default:{
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
         }// end switch( menuOption)
    return 0;
   }//end main()
}
