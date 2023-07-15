/*
   1- Author: Aqsa Arif 677417263
   2- Lab: Lab 2 - The LCD
   3- Description: Implement a racing game between two players with an LCD screen
   4- LCD Pins: List what each of the following LCD pins are for, i.e. “D4: Data pin 4”. (Read the prelab)
     VSS(GND): Ground connection
     VDD(+5V): Power connection
     V0: Connected to potentiometer
     RS: Data pin 12
     RW: connected to ground
     E(Enable): Data pin 11
     D4: Data pin 4
     D5: Data pin 5
     D6: Data pin 6
     D7: Data pin 7
     A(BKlt+): connected to power through transistor
     K(BKlt-): connected to ground
   5- References: 
   https://www.programmingelectronics.com/using-the-print-function-with-arduino-part-1/
   https://docs.arduino.cc/learn/electronics/lcd-displays
   https://www.arduino.cc/reference/en/libraries/liquidcrystal/
   https://docs.arduino.cc/built-in-examples/digital/Debounce
   6- Demo: in-Person during office hours with Prof Diaz, 11 AM 3/6/2023
*/


/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// button 1 and 2 pin numbers
int buttonPin=8; // player 1
int buttonPin1=7; // player 2

// button 1 variables
// player 1 buttons
int buttonNew;
int buttonOld=1;
int counterOne=0;
int buttonState; 
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    

// button 2 variables
// player 2 buttons
int buttonNew1;
int buttonOld1=1;
int counterTwo=0;
int buttonState1; 
int lastButtonState1 = LOW;
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay1 = 50;   


void setup() {
   //Initiate Serial communication.
  Serial.begin(9600);
  //Serial.print(("Hello World"));
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0); // top left
  lcd.print("Player One (1)");
  lcd.setCursor(0, 1); // bottom left
  lcd.print("Player Two (2)");
  // pins for both buttons
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin1, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
  int reading = digitalRead(buttonPin);

  // read input for first button
  buttonNew=digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
    }
  }

  // For debugging
  Serial.println(buttonNew);

  // Check button state for first button
  // Player 1 code
  if(buttonOld == 0 && buttonNew==1){
    lcd.clear();
    lcd.setCursor(counterOne%16, 0); // first row
    // Increment player one counter
    counterOne+=1;
    lcd.print("$");
    // display player two at the same time
    lcd.setCursor(counterTwo%16, 1); // bottom row
    lcd.print("%");

    if(counterTwo>15){
      // display # for second lap for player two
      lcd.setCursor(15, 1); // bottom right
      lcd.print("#");
      if(counterTwo>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left dislay
        lcd.print("Player Two Wins!");
      }
      if(counterOne>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left dislay
        lcd.print("Player One Wins!");
      }
    }
    if(counterOne>15){
       // display # for second lap for player one
      lcd.setCursor(15, 0); // bottom left
      lcd.print("#");
      // win condition
      if(counterTwo>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left dislay
        lcd.print("Player Two Wins!");
      }
      if(counterOne>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left dislay
        lcd.print("Player One Wins!");
      }
    }
    
  }
  buttonOld=buttonNew;
  lastButtonState = reading;

  Serial.println(counterOne);

  int reading1 = digitalRead(buttonPin);
  // read input for second button
  buttonNew1=digitalRead(buttonPin1);

  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay1) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
    }
  }
  
  // Check button state for first button
  if(buttonOld1 == 0 && buttonNew1==1){
    lcd.clear();    
    lcd.setCursor(counterOne%16, 0); // first row
    lcd.print("$");
    lcd.setCursor(counterTwo%16, 1); // bottom row
    counterTwo+=1;
    lcd.print("%");

    if(counterTwo>15){
      // display # for second lap for player two
      lcd.setCursor(15, 1); // bottom right
      lcd.print("#");
      if(counterTwo>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Player Two Wins!");
      }
      if(counterOne>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Player One Wins!");
      }
    }
    if(counterOne>15){
      // display # for second lap for player one
      lcd.setCursor(15, 0); // top right
      lcd.print("#");
      // win condition
      if(counterTwo>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Player Two Wins!");
      }
      if(counterOne>31){
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Player One Wins!");
      }
    }
  }
   buttonOld1=buttonNew1;
   lastButtonState1 = reading1;
}