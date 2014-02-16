int led1 = A4;
int led2 = 9;
int button = A5;
int voltage = LOW;

void setup () {
  pinMode(led1, OUTPUT);
//  pinMode(led2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}


void loop(){
  int buttonState = digitalRead(button);
  
  if (buttonState == LOW) {  
    if (voltage == HIGH) {
      voltage = LOW;
    } else {
      voltage = HIGH;
    }   
  }
  
  digitalWrite(led1, voltage);
  //delay(1000);
   //delay(1000);
}


