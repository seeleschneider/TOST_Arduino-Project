
#define echoPin 8 // echopin
#define trigPin 7 //triggerpin
#define buzzPin 12 //buzzpin

int maximumRange = 200;
int minimumRange = 0;
long duration,distance;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzPin,OUTPUT);
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin,HIGH);
  digitalWrite(buzzPin,HIGH);
  distance = duration/58.2;
  //Serial.println(duration);
  Serial.println(distance);
  delay(50);
}

