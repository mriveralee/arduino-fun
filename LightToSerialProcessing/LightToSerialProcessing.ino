/* Prototype from making an image from analog light sensor */



#include "pitches.h"
//DEBUG_MODE prints to the serial monitor
boolean DEBUG_MODE = false;
//Play sounds created from the light when captured
boolean PLAY_CAPTURED_SOUNDS = false;
//Play sounds sent from processing's serial port
boolean PLAY_DECODED_SOUNDS = true;
int NUM_MAX_OUTPUT = 100;
int NUM_CURRENT_OUTPUT = 0;

// to calculate the note duration, take one second
// divided by the note type. e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
int noteDuration = 1000/4;  // quarter note

//-----Instance Variables ---------------------------
int ALL_NOTES[] = {
   NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2, 
   NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, 
   NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, 
   NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, 
   NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, 
   NOTE_A6, NOTE_AS6, NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, 
   NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8
 };
//Size of all notes array
int MAX_NUM_NOTES = (sizeof(ALL_NOTES)/sizeof(int));

//Pin Location of the Speaker
int SPEAKER_PIN = 7;

// Light Sensor Pin
int LIGHT_SENSOR_PIN = A6;  //Pin "20"
//------------------------------------------


//Does initialization & sets up variables
void setup() {
  //Initialize the Serial Port for Writing
  Serial.begin(9600);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  delay(4000);
}

//the Main Loop of our program
void loop() {    
  
 // if (NUM_CURRENT_OUTPUT < NUM_MAX_OUTPUT)
    //Read Analog input from light sensor
    int lightValue = getAnalogLight();
    //Print to the Serial for reading in Processing
    printLightToSerial(lightValue);
    //Play the note frequency value with the noteDuration from captured Light
    playCapturedSounds(lightValue);
   // NUM_CURRENT_OUTPUT += 1;
  //}
  //else {
    //Play sound frequency sent from Processing (the decoded images)
    playDecodedSounds();
  //}
}

//Reads light from the sensor on the Arduino, prints it to the 
//Serial (for Processing to capture), then returns the lightValue
void printLightToSerial(int lightValue) {
  //Write to Serial (USB) output for reading in Processing
  Serial.println(lightValue); 
}

void playCapturedSounds(int lightValue) {
  //Get note-value index from analog light   
  int noteValue = mapToNote(lightValue);   
  
  //Print more information about mapping if debugging
  if (DEBUG_MODE) printMappedValue(lightValue, noteValue);
  
  if (PLAY_CAPTURED_SOUNDS) {
      tone(SPEAKER_PIN, ALL_NOTES[noteValue], noteDuration); 
      //Pause between notes 
      pauseBetweenNotes(noteDuration);
    } 
}

void playDecodedSounds() {
  if (PLAY_DECODED_SOUNDS) {
    //Get note-value index from processing
    if (Serial.available() > 0) {
      int decodedValue = Serial.read();
      if (decodedValue >= 0) {
        int noteValue = mapToNote(decodedValue);
        Serial.println("Decoded Value: ");
        Serial.print(decodedValue);
        tone(SPEAKER_PIN, ALL_NOTES[noteValue], noteDuration); 
        //Pause between notes 
        pauseBetweenNotes(noteDuration);
      }
    }
  }
}
//Convert a analog value into a note value depending on the max number of notes we have
int mapToNote(float analogValue) {
        return round(analogValue)%MAX_NUM_NOTES;
}

//Places a rest between notes while playing so that they are distinguishable
void pauseBetweenNotes(int noteDuration) {
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing: (uncomment to use
    // noTone(9);
}


//Prints an analog value and its corresponding note value to the serial monitor
void printMappedValue(float analogValue, int noteValue) {
 ///String(analogValue) + String("| Note Value: ") + String(noteValue); 
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print("| Note Value: ");
  Serial.print(noteValue);
  Serial.println();
}

int getAnalogLight() {
  return analogRead(LIGHT_SENSOR_PIN);
}


