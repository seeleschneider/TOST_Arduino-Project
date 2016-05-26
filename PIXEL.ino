const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    int test = Serial.parseInt();
      for(int input = 0; input<test; input++){
          digitalWrite(ledPin,HIGH);
          delay(200);
          digitalWrite(ledPin,LOW);
          delay(200);
      }
      digitalWrite(ledPin,LOW);
  }
}

