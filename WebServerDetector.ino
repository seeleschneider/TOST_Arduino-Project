//define from ParkingDetectorSensor
#define echoPin 8 // echopin
#define trigPin 7 //triggerpin

int maximumRange = 200;
int minimumRange = 0;
long duration =0;
long distance =0;
//end define from ParkingDetectorSensor

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT); //define from ParkingDetectorSensor
  pinMode(echoPin,INPUT); //define from ParkingDetectorSensor
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

//define from ParkingDetectorSensor
void AntoDectector(unsigned char distance){
  int piezopin = 9;
  tone(piezopin,1000,50);
  delay(1000-distance*100);
  }
  //end define from ParkingDetectorSensor
void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

//define from ParkingDetectorSensor
          digitalWrite(trigPin,LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin,HIGH);
          delayMicroseconds(10);
          duration = pulseIn(echoPin,HIGH);
          distance = duration/58.2;
          Serial.println(duration);
          Serial.println(distance);
          delay(50);

          if(distance<10){
            tone(9,1000,50);
            delay(distance*100-distance*75);
//end define from ParkingDetectorSensor
          client.println(duration);
          client.println(distance);
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    }
  }
}

