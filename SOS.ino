// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(13, HIGH);
  delay(1000);
    digitalWrite(13, LOW);
  
  delay(1000);                // 1 second delay wich acts 1: before loop to make sure your ready and 2: act as a delay for when it starts all over again :)

  digitalWrite(13, HIGH);   //"S" signal starts after the one second delay
    delay(300);                  
      digitalWrite(13, LOW);    
    delay(100);   
      digitalWrite(13, HIGH);
    delay(300);
      digitalWrite(13, LOW);
    delay(100);
      digitalWrite(13, HIGH);
    delay(300);
      digitalWrite(13, LOW);
  
    delay(1000);                  //1 second delay for the second letter (fisrt of 2)
    
      digitalWrite(13, HIGH);
    delay(2000);                  // First dash of 3 wich represents the O
      digitalWrite(13, LOW);
    delay(500);
      digitalWrite(13, HIGH);
    delay(2000);
      digitalWrite(13, LOW);
    delay(500);
      digitalWrite(13, HIGH);
    delay(2000);                   
      digitalWrite(13, LOW);

    delay(1000);                  //second 1 second delay for the third letter 
      
      digitalWrite(13, HIGH);   
    delay(300);                  
      digitalWrite(13, LOW);    
    delay(100);   
      digitalWrite(13, HIGH);
    delay(300);
      digitalWrite(13, LOW);
    delay(100);
      digitalWrite(13, HIGH);
}
