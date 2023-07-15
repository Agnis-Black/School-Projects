// 1- Aqsa Arif - 677417263
// 2- Lab 1 -  Toggle button
// 3- Description - The code identifies the connected pins and LEDs and sets a toggle button to light up LEDs. The code checks state of button, depending on button it changes state of LED from on to off. If both blue LEDs are set as on, it lights up red LED. The code can be edited to act as AND and an OR logic gate.
// 4- PIN numbers: Blue LED pin = 8 (output)
// second Blue LED pin = 9 (output)
// Red LED pin = 11 (output)
// Button pin = 10 (input)
// second Button pin = 12 (input)
// 5- References - https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
// https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
// https://www.youtube.com/watch?v=aMato4olzi8
// 6- Diana Diaz in person during Office hours 

int LEDState=0;
int LEDState1=0;

// pin numbers for LED blue 1, blue 2, and red
int LEDPinB1=9;
int LEDPinB2=8;
int LEDPinR=11;

// button 1 and 2 pin numbers
int buttonPin=12;
int buttonPin1=10;

// button 1 variables
int buttonNew;
int buttonOld=1;

// button 2 variables
int buttonNew1;
int buttonOld1=1;


int dt=100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // pins for LEDs, Blue1 Blue2 Red
  pinMode(LEDPinB1, OUTPUT); 
  pinMode(LEDPinB2, OUTPUT);
  pinMode(LEDPinR, OUTPUT);

  // pins for both buttons
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin1, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read input for first button
  buttonNew=digitalRead(buttonPin);

  // Check button state for first button
  if(buttonOld == 0 && buttonNew==1){

    // conditional statement to turn blue LED on or off
    if(LEDState==0){
      digitalWrite(LEDPinB1,HIGH);
      LEDState=1;
    }
    else{
      digitalWrite(LEDPinB1,LOW);
      LEDState=0;
    }

  }

  buttonOld=buttonNew;

  // read input for second button
  buttonNew1=digitalRead(buttonPin1);
  
  // Check button state for second button
  if(buttonOld1 == 0 && buttonNew1==1){


    // conditional statement to turn second blue LED on or off
    if(LEDState1==0){
      digitalWrite(LEDPinB2,HIGH);
      LEDState1=1;
    }
    else{
      digitalWrite(LEDPinB2,LOW);
      LEDState1=0;
    }

  }

  buttonOld1=buttonNew1;

  // Logic gate like code that changes Red LED based on states of both blue LEDs

  if(LEDState == 1 || LEDState1 ==1){

    digitalWrite(LEDPinR,HIGH);
  }
  else{
    digitalWrite(LEDPinR,LOW);
  }

}
