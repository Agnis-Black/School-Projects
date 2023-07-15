/*
   1- Author: Aqsa Arif - 677417263
   2- Lab: Lab 5 - Communication
   3- Description: This is a game that takes an input from user and randomly generates a number and sums it to input of user
   depending on the chosen odd/even outcome by user. The player can win or lose depending on the sum of the random number and their own input 
   which consists of a number between 1 and 5.
   4-Lab Questions:
    What function did you use to change the servo position?
    myservo.write()
    What are the angles of the servo motor for the three directions?
    the servo can rotate a full 360 but for the prelab it rotated from 0 to 180 degrees.
    three possible angles in that range are 0, 90 and 180 degrees or any other value in between.
    What functions/methods did you use to take input?
    analogRead() this read values for my potentiometer
    Serial.parseInt() to get user number 1 to 5
    Serial.readBytes(buf, BUFFER_SIZE) for even and odd string
   5- References: 
   https://www.arduino.cc/reference/en/language/functions/communication/serial/available/
   https://www.arduino.cc/reference/en/language/functions/communication/serial/
   https://www.tutorialspoint.com/arduino/arduino_servo_motor.htm
   https://docs.arduino.cc/learn/electronics/servo-motors
   https://www.tutorialspoint.com/arduino/arduino_random_numbers.htm
   https://docs.arduino.cc/built-in-examples/communication/ReadASCIIString
   https://forum.arduino.cc/t/serial-input-basics-updated/382007
   https://arduinogetstarted.com/reference/serial-readbytes
   6- Demo: in-person 11 AM  Dhwanit
*/


#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int incomingByte = 0; // for incoming serial data
int pos = 0;    // variable to store the servo position
// flags to ensure singular loop in conditional statements
bool inputNum = false;
bool outPrint = false;
bool genPrint = false;
bool odd = false;
bool even = false;
// global variable holders
int num;
int total;

// pin for all LEDs Red and Green
int ledPinR = 13;
int ledPinG = 12;

// random number generated holder
int ranNum;

// char array that holds user input of even or odd 
const int BUFFER_SIZE = 10;
char buf[BUFFER_SIZE];

// bool for reset if input is not valid
bool validInputs = false;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.print("\nWelcome to the Even Odd game!!!");
  Serial.print("\nEnter a number between 1 to 5!!");
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  randomSeed(analogRead(1)); // random number generator
}

void loop() {
  // first check on both number and string input
  if(inputNum == true){
    getChoice();    
  } else {
    getNum();
  }
  // once both values are valid proceed to arithmetics and win condition check
  if(validInputs == true){

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
    // only print once upon servo rotation
    if(genPrint == false){
      Serial.print("\nGenerating...");
      genPrint = true;
    }
    
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
    validInputs = false;
    math(); 
    checkWin();
    delay(1000);
    reset(); 
  }
  
}

// helper function to reset game
void reset(){
  Serial.print("\nWelcome to the Even Odd game!!!");
  Serial.print("\nEnter a number between 1 to 5!!");
  // turn off LEDs
  digitalWrite(ledPinR, LOW);
  digitalWrite(ledPinG, LOW);
  // reset servo to neutral position
  myservo.write(90); 
  // reset flags for conditional loops
  inputNum = false;
  outPrint = false;
  genPrint = false;
  even = false;
  odd = false;

}

// helper function that generates random number 
// adds random number to user input and stores sum in total 
void math(){
  ranNum = random(1, 5);
  Serial.print("\nMy Number: ");
  Serial.print(ranNum);
  total = ranNum + num;
  Serial.print("\nSum is ");
  Serial.print(total);
}

// check if player win/lose based on variables updated in math()
void checkWin(){
  // if player selected even
  if(even){
    // if sum is even player wins
    // set servo to point to green LED and light it up
    if(total % 2 == 0){
      Serial.print("\nSum is Even You win!");
      myservo.write(180); 
      digitalWrite(ledPinG, HIGH);
      delay(500);
    } else {
      // light red LED, set servo to point to red
      Serial.print("\nYou Lose... Better Luck next time!");
      myservo.write(0); 
      digitalWrite(ledPinR, HIGH);
      delay(500);
    }
  }
  // if player chose odd
  if(odd){
    // if sum is odd player wins
    // set servo to point to green LED and light it up    
    if(total % 2 == 1){
      Serial.print("\nSum is Odd You win!");
      digitalWrite(ledPinG, HIGH);
      myservo.write(180); 
      delay(500);
    } else {
      // light red LED, set servo to point to red
      Serial.print("\nYou Lose... Better Luck next time!");
      myservo.write(0); 
      digitalWrite(ledPinR, HIGH);
      delay(500);
    }
  }
  
}

// this is the initial serial function to get user 
// number between 1 to 5
void getNum(){
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    // look for the next valid integer in the incoming serial stream:
    num = Serial.parseInt();
    inputNum = false;
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      //Serial.println(num);
      if(num > 0 and num < 6 ){
        inputNum = true;
        Serial.print("\nI received: ");
        Serial.print(num);
      }
    }
    // if user input not within given range or not a number
    if(inputNum == false){
      Serial.print("\nwrong input");
      reset(); // reset game
    }

  }
}

// this is a helper function that stores whether selected chose even or odd
// stores selection for other functions in booleans
void getChoice(){
  // initial print
  if(outPrint == false){
    Serial.println("\nNow choose even or odd! Type even or odd");
    outPrint = true;
  }
  
  while (Serial.available() > 0) {
    
    // read the incoming bytes:
    int rlen = Serial.readBytes(buf, BUFFER_SIZE);
    // hard conditional on odd string
    // update relative flags and prints
    if(buf[0] == 'o' and buf[1] == 'd' and buf[2] == 'd' and buf[3] == '\n'){
      Serial.print("I received: ");
      Serial.print("odd");
      validInputs = true;
      odd = true;

    } else {
      // hard conditional on even string
      // update relative flags      
      if(buf[0] == 'e' and buf[1] == 'v' and buf[2] == 'e' and buf[3] == 'n' and buf[4] == '\n'){
        Serial.print("I received: ");
        Serial.print("even");
        validInputs = true;
        even = true;
        } else {
          // if user did not type even or odd strings all other inputs rejected
          Serial.print("wrong input");
          reset(); // reset game
        }
    }
        
  }
}
