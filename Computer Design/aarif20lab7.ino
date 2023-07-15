/*
   1- Author: Aqsa Arif - 677417263
   2- Lab: Lab 7 - Interrupts
   3- Description: In your own words, what is this code supposed to do?
   This lab is a game where a player sees numbers going from 0 to 9 and upon press of a button
   if timed according to the display and the random number generated, player wins if not
   the loop of numbers from 0 to 9 keeps going and keeps the same random number it generated until 
   the player pushes button at that specific random number display on digit LED.
   4-Lab Questions:
What is the purpose of a current-limiting resistor in a seven-segment display circuit?
It is to limit the current going through the digit LED displays. To prevent the LED in digit display from being destroyed.
Can you display special characters? If yes, How?
Special characters depend on whether they can be displayed in the given lines. Complicated characters like 
&, * , %, @, probably cannot be displayed but specific characters like the capital A or L probably could because it 
could be represented with a bunch of straight lines.
 _
|_|   and  |
| |        |_    like this.

What are some common applications of seven-segment displays?
It is used in scorekeeping in sports
it can be used in games
it can be used as a counter or general display
   5- References: 
   https://www.youtube.com/watch?v=9VZUb5cMrV0
   https://core-electronics.com.au/guides/arduino-workshop-for-beginners/   
   https://lastminuteengineers.com/seven-segment-arduino-tutorial/
   https://www.tutorialspoint.com/arduino/arduino_random_numbers.htm
   6- Demo: in person 12 PM 4/17/2023 michael
*/

#include "SevSeg.h"
SevSeg sevseg;

int buttonPin = 2; // button set to pin 2

int currNum; // integer that keeps track of current number display on LED
int lastButtonState = 1;
long unsigned int lastPress;
volatile int buttonFlag;
int debounceTime = 2;
// random number generated holder
int ranNum;
bool newLoop = true; // win/lose boolean

void setup()
{

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), ISR_button, CHANGE);
  randomSeed(analogRead(1)); // random number generator
	
  //Set to 1 for single digit display
	byte numDigits = 1;

	//defines common pins while using multi-digit display. Left empty as we have a single digit display
	byte digitPins[] = {};

	//Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
	byte segmentPins[] = {5, 4, 10, 9, 8, 6, 7, 11};
	bool resistorsOnSegments = true;

	//Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
	sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
	sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);

	sevseg.setBrightness(50);  
  Serial.begin(9600);
}

void loop() 
{ 
   if(newLoop == true){
     newGame();
   }
   //Display numbers one by one with 2 seconds delay
   for(int i = 0; i < 10; i++) {
     // win flag display function
      if(newLoop == true){
       newGame();
      }
      // gamplay loop
      buttonPressed();
      delay(125);  // delay set and spread out so that in 2 seconds 4 numbers display and sufficient gap between interrupts
      sevseg.setNumber(i);
      currNum = i; // set player number only after it has been displayed
      buttonPressed();
      delay(125);
      sevseg.refreshDisplay(); 
      delay(125);
      buttonPressed();
      delay(125);
      buttonPressed();
    }
}

// function that checks upon button push whether player won/lose
void checkPress(){
  if(currNum == ranNum){ // if current display is the same as random number player win
    Serial.print("\nCongratulations! You pressed at the correct number.");
    Serial.print("\nGame is restarting");
    newLoop = true; // set win flag to true
  } else { // random number not the same as display run lose function and displays
    lose();
  }
}

// If a player wins start new game with new random number
void newGame() {
  ranNum = random(0, 9); // generate new random number from 0 to 9
  Serial.print("\n");
  Serial.print("The selected random number is: ");
  Serial.print(ranNum);
  newLoop = false;  // reset win flag
}

// keep same random number upon lose condition
void lose(){
  Serial.print("\nOops! You stopped at the wrong number. Resuming the game.");
  Serial.print("\nThe selected random number is: ");
  Serial.print(ranNum);  
}

// button interrupt flag
void ISR_button()
{
  buttonFlag = 1;
}

// button interrupt function
void buttonPressed(){
  if((millis() - lastPress) > debounceTime && buttonFlag) {
       lastPress = millis();   //update lastPress                                                     
       if(digitalRead(buttonPin) == 0 && lastButtonState == 1)    //if button is pressed and was released last change
       {
         //Serial.print("\n");
         //Serial.print(currNum);
         checkPress(); // only check win/lose condition after button is pressed
         lastButtonState = 0;    //record the lastButtonState
        } else if(digitalRead(buttonPin) == 1 && lastButtonState == 0)    //if button is not pressed, and was pressed last change
         {
           lastButtonState = 1;    //record the lastButtonState
          }
          buttonFlag = 0;
      }
}