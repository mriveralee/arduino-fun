/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
int SWITCH_PIN = 2;
int OUTPUT_PIN = 6;
boolean hasConnectedOutput = false;
boolean IS_STANDALONE = true;

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 if (IS_STANDALONE) {
   handleStandalone();
 } else {
   handleSerialConnection();
    //Update the write value
   updateConnectedOutput();
 }

}

void handleSerialConnection() {
   int keyPressed = Serial.read();
    updateState(keyPressed); 
}

void handleStandalone() {
 digitalWrite(OUTPUT_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

}

//Updates the state of the 
void updateState(int keyPressed) {
  if (keyPressed != -1) {
    hasConnectedOutput = !hasConnectedOutput;
    if (hasConnectedOutput) {
      Serial.println("Output is on!");
    } else { 
      Serial.println("Output is off!");
    }
  } 
}

//Updates the output value
void updateConnectedOutput() {
  if (hasConnectedOutput) {
    digitalWrite(OUTPUT_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
   digitalWrite(OUTPUT_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}
