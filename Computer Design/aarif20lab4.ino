/*
   1- Author: Aqsa Arif - 677417263
   2- Lab: Lab 4 - Multiple Inputs and Outputs
   3- Description: In your own words, what is this code supposed to do?
   4-Lab Questions:

    What does the map() function do?
    map() uses these parameters:
    map(value, fromLow, fromHigh, toLow, toHigh)
    to my understanding, it sets boundaries lower and upper bounds for values and then constraints output within a range.
    (lightRaw, 1023, 0, 100, 0); These are the values i used to set my photoresistor to only light up in the dark.
    Upon a light shining on photoresistor, lightRaw becomes value 100+
    no light gives it a value of below 10. My range is between 1023 and 0 and that is mapped unto as 100 and 0.

    How did you change the speed of the melody in your code?
    I got help by a TA and got a suggestion to map raw light input and use it to divide against noteDuration in song.

    What was the hardest part of the lab to implement?
    figuring out how to speed up and slow down song. 
    
   5- References: 
   https://www.circuitbasics.com/how-to-use-photoresistors-to-detect-light-on-an-arduino/
   https://github.com/robsoncouto/arduino-songs
   https://lastminuteengineers.com/joystick-interfacing-arduino-processing/
   https://www.arduino.cc/reference/en/language/functions/math/map/
   6- Demo: dhwanit 4/3/2023 11 AM
*/

/* 
  Jigglypuff's Song
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 85;

// change this to whichever pin you want to use
int buzzer = 5;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Jigglypuff's Song
  // Score available at https://musescore.com/user/28109683/scores/5044153
  
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

// pin number for photoresistor
int photoPin = A0;
// pin for all LEDs Red, Blue, Yellow, Green
int ledPinR = 8;
int ledPinB = 10;
int ledPinY = 9;
int ledPinG = 11;
// Arduino pin numbers
const int SW_pin = 7; // digital pin connected to switch output
const int X_pin = 1; // analog pin connected to X output
const int Y_pin = 2; // analog pin connected to Y output

void setup() {
  Serial.begin(9600);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
}

void loop() {
  // // iterate over the notes of the melody.
  // // Remember, the array is twice the number of notes (notes + durations)
  int thisNote = 0;
  while (thisNote < notes * 2) {
    // void joystick check function
    checkJoy();
    // read raw data from photoresistor
    int lightRaw = analogRead(photoPin);
    // mapping that turns light off on shine
    int light = map(lightRaw, 200, 0, 100, 0);
    Serial.println(light);
    
    
   
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    
    if (divider > 0) {
    
      // regular note, just proceed
      // some duration manipulation based on light
      // on low light increase duration
      if (light < 10) {
        noteDuration = (wholenote) / divider;
        noteDuration +=5;
        // on high light reduce duration
      }else if (light > 40){
        noteDuration = (wholenote) / divider;
        noteDuration -=10;
      } else {
        noteDuration = (wholenote) / divider;
      }
   
    } else if (divider < 0) {
   
      // dotted notes are represented with negative durations!!
      
      // some duration manipulation based on light
      // on low light increase duration
      if (light < 10) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration +=5;
        noteDuration *= 2;
        // on high light reduce duration
      }else if (light > 40){
        noteDuration = (wholenote) / abs(divider);
        noteDuration -=10;
        noteDuration *= 1.1;
      } else {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
    
    }

   
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
 
    // Wait for the specief duration before playing the next note.
    // this section of the code controls the speed of the song
    delay(noteDuration/light);

    // stop the waveform generation before the next note.
    noTone(buzzer);

    thisNote = thisNote + 2;
   
  }

}


void checkJoy(){
  // glow yellow on left
  if(analogRead(X_pin) == 1023){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, HIGH);
    }
    // glow green on right
    if(analogRead(X_pin) == 0){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinY, LOW);

    }
    // glow red on up
    if(analogRead(Y_pin) == 1023){
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, LOW);
    }
    // glow blue on down
    if(analogRead(Y_pin) == 0){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, HIGH);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, LOW);
    }
    // glow blue and yellow
    if(analogRead(Y_pin) == 0 && analogRead(X_pin) == 1023){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, HIGH);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, HIGH);
    }
    // glow blue and green
    if(analogRead(Y_pin) == 0 && analogRead(X_pin) == 0){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, HIGH);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinY, LOW);
    }
    // glow red and yellow
    if(analogRead(Y_pin) == 1023 && analogRead(X_pin) == 1023){
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, HIGH);
    }
    // glow red and green
    if(analogRead(Y_pin) == 1023 && analogRead(X_pin) == 0){
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinY, LOW);
    }
    // neutral position reset all lights
    if(analogRead(Y_pin) > 490 && analogRead(Y_pin) < 510){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, LOW);
    }
    // neutral position reset all lights
    if(analogRead(X_pin) > 500 && analogRead(X_pin) < 520){
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinY, LOW);
    }
    // serial print for debugging
    Serial.print("Switch:  ");
    Serial.print(digitalRead(SW_pin));
    Serial.print(" | ");
    Serial.print("X-axis: ");
    Serial.print(analogRead(X_pin));
    Serial.print(" | ");
    Serial.print("Y-axis: ");
    Serial.print(analogRead(Y_pin));
    Serial.println(" | ");
}
