#include <SPI.h>
#include <RAS.h> // Rugged Audio Shield library

//###### Rugged Audio State Variables ######
RAS RAS;                             // Declare the Rugged Audio Shield object  
int lastVolume;                      //Last volume read from the potentiometer

//Tell us whether we should record sound or if we already are


//###### Recording State Variables ######
boolean SHOULD_RECORD_AUDIO;         //Just started recording?
boolean IS_RECORDING;                //Are we recording?
int MAX_RECORD_TIME = 1;            //Max Number of seconds to record

unsigned long currentTime;           //Time since the Program has been running
unsigned long startRecordTime;       //Time at which recording has started

//###### File Saving State Variables ######
String WAV_FOLDER;
int randStartDigit;                  //Start Folder name for saving files
int recordCount;                     //Number of recorded sounds this session

//###### Serial Monitor ######
int serialPort = 9600;               //Serial port for receiving stop/start cmds

//###### Initial Set Up ######
void setup(void) {
  Serial.begin(serialPort);
  //Initialize Variables
  RAS.begin(); // Default SPI select on D8
  SHOULD_RECORD_AUDIO = false;
  IS_RECORDING = false;
  recordCount = 0;
  randStartDigit = random(0,1235853);
  //Create a folder for output
  WAV_FOLDER = "./" + String(randStartDigit) + "/";
  
 
  
   RAS.InitSD(/*SPI_RATE_4MHz*/);
  
  //RAS.InitSD(/*SPI_RATE_4MHZ*/);
  //RAS.WaitForIdle();
 // RAS.
  // PLAYBACK AUDIO
  // Adjust these to 1X, 2X, 4X, or 8X depending on your source material
  //RAS.SetInputGainLine(INPUT_GAIN_1X); delay(10);
  RAS.SetInputGainMic(INPUT_GAIN_2X); delay(10);
  RAS.OutputEnable(); delay(10);
  // Start pass-through of mic+line (left channel) to output at 32 kHz
  //RAS.AudioEffect(EFFECT_NONE, 32000, SOURCE_MONO, SOURCE_MIC);
  //RAS.PlayStream(32000, SOURCE_MONO); delay(10);
  //Start App
  Serial.println("Playing Live audio..");
  Serial.println("Press 'r' to record a sample...");

  
}

//###### App Loop ######
void loop(void) {
  //Update the current Time
  currentTime = millis();\
  //Check status of recording - should we start or stop?
  checkRecordingStatus();
  //Recording
  
  //Update the volume if necessary
  //updateVolume(); 
}
  
  
//###### Check Recording Status ######
void checkRecordingStatus() {
  //Check for user input
  if (Serial.available() > 0) { 
    char pressed = Serial.read();
    if (pressed == 'r' && !IS_RECORDING) {
      // say what you got:
      startRecording();
      }
    else if (pressed == 's' && IS_RECORDING) {
      stopRecording();
    }
    //Print the char pressed
    //if (pressed >= 0) Serial.println("Pressed: " + pressed);  
  }
  //Stop recording if we've recorded for longer than MAX_RECORD_TIME seconds
  if (IS_RECORDING) {
    unsigned long timeRecording = abs(currentTime-startRecordTime)/1000;
    if (timeRecording >= MAX_RECORD_TIME) {
      Serial.println("Reached Max Recording Time!");
      stopRecording();
    }
  }

}
 
//###### StartRecording ######
void startRecording() {
  IS_RECORDING = true;
  SHOULD_RECORD_AUDIO = true;
  startRecordTime = millis();
  //Start recording to file
  String fileName = WAV_FOLDER + String(recordCount) + ".wav";
  char charBuf[70];
  fileName.toCharArray(charBuf, 70);
  RAS.RecordWAV(32000, SOURCE_MONO, SOURCE_MIC, charBuf);
  Serial.println("Recording as  - Press 's' to stop.");
  Serial.println(fileName);
  Serial.println(charBuf);
}

//###### Stop recording ######
void stopRecording() {
  Serial.println("Stopped Recording - Press 'r' to start.");
  IS_RECORDING = false;
  SHOULD_RECORD_AUDIO = false;
  recordCount++;
  //Stop the recording
  RAS.Stop();
}

//###### Update Volume ######
//Updates the volume from the potentiometer reading
void updateVolume() {
  int reading;
    // Update the volume every 300ms (not to overwhelm the SPI bus), and
    // don't bother sending a volume update unless the potentiometer reading
    // changed by more than 16 counts.
    delay(300);
    reading = analogRead(3); // Read shield potentiometer
    if (abs(reading - lastVolume) > 16) {
      lastVolume = reading;
      // Potentiometer reads 0V to 3.3V, which is 0 to about 700
      // when using the default 5V analog reference. So we map the range
      // 0<-->700 to the OutputVolumeSet() range of 0 to 31.
      RAS.OutputVolumeSet(map(reading, 0, 700, 0, 31));
    }   
}
