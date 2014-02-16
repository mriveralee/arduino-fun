int led = 5;

void setup () {
  pinMode(led, OUTPUT);
  pinMode(A6, INPUT);
  //pinMode(9, OUTPUT);
  Serial.begin(9600);
}


void loop(){
int analog_value = analogRead(A6);
Serial.println(analog_value);

if (analog_value > 100) {
  digitalWrite(led, LOW);
} else {
  digitalWrite(led, HIGH);
}
//analogWrite(9, analog_value);

}


