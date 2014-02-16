int led1 = A4;
int led2 = 9;

void setup () {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}


void loop(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(1000);
}


