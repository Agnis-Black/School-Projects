/*
   1- Author1: Lili Velazquez - 663484718
    - Author2: Aqsa Arif - 677417263
   2- Lab: Lab 6 - Serial Communication 
   3- Description: 
   a) In your own words, what is this code supposed to do? 
      This is a racing game where two arduinos use serial communication to send the their characters position on the lcd. This code is for player 2. 
   b) Explain the division of labor between the teammates. 
      We helped each other with the wiring. We used my (Lili) code from Lab 2 and Aqsa helped debug code for new implementation for lab 6. We worked on the code together in-person.
   4- Serial Communication: describe how serial communication works in this lab. (include in this description the pin numbers you used)
      Serial communication works by reading serial monitor in an array buffer.
      The pin numbers are Tx (1) , Rx (0) , and GRD  
   5- References: 
      For the prelab and also to understand and use serial communication between two arduinos
		https://iot-guider.com/arduino/serial-communication-between-two-arduino-boards/     
      For the buzzer sound 3 2 1 Go!!
		https://littlebirdelectronics.com.au/guides/53/make-a-sound-with-a-piezo-buzzer
      For receiving a single number from the Serial Monitor
      	https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
   6- Demo: in-person demonstration - 4/3/23, 10AM, Jude 
*/


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 5, d5 = 4, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// button pin 
int buttonPin = 11;

// buzzer pin 
int buzzer = 10;

// red led pin and initial state
int rPin = 13;
int rState = LOW;

// green led pin and initial state
int gPin = 12;
int gState = LOW;

// old state of the first button 
int bOld = HIGH; 

// flag for ready players 
int readyOne = 0;
int readyTwo = 0;

// ___
// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
const byte numChars = 2;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;
int dataNumber = 0;   
// ___

char send[3] = "1\n";

// flags needed for the initial messages 
int firstClick = 1; // the player is ready 
int racing = 0; // start the game 
int firstPrint = 0; // to send the ready signal if its the first button press 
int count = 6; // counter for the initial messages
int msg;

// variables to increment the position of each player 
int i = -1; // p1
int j = -1; // p2

// flag - second lap
int s1 = 0; // p1
int s2 = 0; // p2

// flag to display which player won 
int w1 = 0; // p1
int w2 = 0; // p2

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600); 
  // set up button pin as input
  pinMode(buttonPin, INPUT);
  // set up buzzer pin as output
  pinMode(buzzer, OUTPUT);
  // set up lcd 
  lcd.begin(16, 2);
  // lcd.setCursor(0, 0);
  // lcd.print("Player 2, Press");
  // lcd.setCursor(0, 1); // bottom left
  // lcd.print("button to start");

  // set up leds as output 
  pinMode(gPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  msg = 1;
}

void loop() {
  recvWithEndMarker();
  showNewNumber();

  int bNew = digitalRead(buttonPin);
  
  if (msg == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 2, Press");
    lcd.setCursor(0, 1); // bottom left
    lcd.print("button to start");
    msg = 0;
    count = 6;
  }

  if (racing == 1 && count == 0) {    
    lcd.clear(); 
    lcd.setCursor(i, 0); 
    lcd.print("%"); 
    lcd.setCursor(j, 1);    
    lcd.print("@");   
  }

  // if button is pressed 
  if ((bOld == LOW && bNew == HIGH)) {
    // Serial.println("button"); 
    if (firstClick == 1) {
      readyTwo = 1;
      Serial.write(send, 3);
      lcd.clear();  
      firstClick = 0;  
    } else {    
      j++;  // increment the position of player 1 
      Serial.write(send, 3);
    }
  }    
  bOld = bNew; 

  if (readyTwo == 1 && readyOne == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Ready, waiting");
    lcd.setCursor(0, 1);
    lcd.print("for Player 1");
  } 

  if (readyTwo == 1 && readyOne == 1 && count == 6) {
    if (count == 6) {
      delay(1000);
      lcd.clear();
      count -= 1;
    }
    if (count == 5) {
      lcd.setCursor(0, 0);
      lcd.print("Ready");
      delay(1000);
      count -= 1;
    }
    if (count == 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("3");
      tone(buzzer, 2000);
      delay(500);        // on for 1 sec
      noTone(buzzer);     // Stop sound
      delay(500);
      count -= 1;    
    }
    if (count == 3) { 
      // delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2");
      tone(buzzer, 2000);
      delay(500);        // on for 1 sec
      noTone(buzzer);     // Stop sound 
      delay(500);
      count -= 1;   
    }
    if (count == 2) { 
      // delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1");
      tone(buzzer, 2000);
      delay(500);        // on for 1 sec
      noTone(buzzer);     // Stop sound 
      delay(500);
      count -= 1;
    }
    if (count == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Go!!");
      tone(buzzer, 2000);
      delay(1500);        // on for 1 sec
      noTone(buzzer);     // Stop sound
      count -= 1;      
      racing = 1;
    }

  }

  // if player 1 finished the first lap...  
  if (i == 15 && s1 == 0) {
    i = 0;  // ...set the player to the left side of the lcd screen to start the second lap...
    s1 = 1; // ...and show the finish line 
  }
  // if player 2 finished the first lap...  
  if (j == 15 && s2 == 0) {
    j = 0;  // ...set the player to the left side of the lcd screen to start the second lap...
    s2 = 1; // ...and show the finish line 
  }  

  // show the finish line 
  if (s1 == 1) { // if in 2nd lap for 1st player...
    lcd.setCursor(15, 0);
    lcd.print("!"); // ...show finish line 
  } 
  // show the finish line 
  if (s2 == 1) { // if in 2nd lap for 2nd player...
    lcd.setCursor(15, 1);
    lcd.print("!"); // ...show finish line 
  } 

  if (s1 == 1 && i == 15) { // if 1st player reaches the finish line 
    w1 = 1; // set the winner to player 1
    s1 = 0; // turn off finish line 
    delay(1500); 
  } 
  else if (s2 == 1 && j == 15) { // if 2nd player reaches the finish line 
    w2 = 1; // set the winner to player 2
    s2 = 0; // turn off finish line 
    delay(1500);
  } 

  // Display the winner 
  if (w1 == 1) { 
    s2 = 0;
    s1 = 0;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Player 1 wins!"); 
    w1 = 0;
    i = -1;    
    j = -1;
    rState = HIGH;
    digitalWrite(rPin, rState);
    delay(2000);
    rState = LOW; 
    digitalWrite(rPin, rState);
    msg = 1;    
    firstClick = 1;  
    racing = 0;  
    firstPrint = 0; 
    count = 6;
    readyOne = 0;
    readyTwo = 0;
  } 
  else if (w2 == 1) {
    s1 = 0;
    s2 = 0;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Player 2 wins!");
    w2 = 0;  
    i = -1;
    j = -1;  
    gState = HIGH;
    digitalWrite(gPin, gState);
    delay(2000);
    gState = LOW; 
    digitalWrite(gPin, gState);
    msg = 1;  
    firstClick = 1;  
    racing = 0;  
    firstPrint = 0; 
    count = 6;
    readyOne = 0;
    readyTwo = 0;
  } 
}

// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
void showNewNumber() {
    if (newData == true) {   
        i++;
        dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        if (firstPrint == 0) {
          readyOne = 1;
          firstPrint = 1;
        }
        newData = false;
    }
}