#include<Ethernet.h>
#include<SPI.h> 

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x3A, 0xDC };                                       
IPAddress ip(192,168,1,7);
EthernetClient client;
EthernetServer server(80);

const int analogInPin = A0;  // Analog input for water level sensor
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the sensor
int outputValue = 0;        // value output to the PWM (analog out)

String statusValue = "";

void setup() {

  Serial.begin(9600);

  pinMode(9, OUTPUT); //Higher
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT); //Lower
    
  Ethernet.begin(mac, ip);
    
  Serial.println("Water Level Sensor");
  Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  Serial.print("IP Address        : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask       : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
}

void loop() {
    //String stat = getStatus();
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);
  
  delay(2000); // delay for
  
  sensor(); 
  
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
          client.println("Refresh: 2");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<head>");
          client.print("<meta http-equiv=\"refresh\" content=\"2\">");
          client.print("<title>FP TOST</title>");
          client.print("</head>");
          client.print("<body>");
          client.print("<p>");
          client.print(statusValue);
          client.print("</p>");
          client.println( "Connection: close" );
          client.println();
          client.println();
          client.print("</body>");
          client.println("</html>");
          break;
          //client.stop();
          
        }
          else if (c != '\r') {
            // you've gotten a character on the current line
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.print("<head>");
            client.print("<meta http-equiv=\"refresh\" content=\"2\">");
            client.print("<title>FP TOST</title>");
            client.print("</head>");
            client.print("<body>");
            client.print("<p>");
            client.print(statusValue);
            client.print("</p>");
            client.print("</body>");
            client.println("</html>");
            break;

            currentLineIsBlank = false;
        }

        delay(1);
        client.stop();
        }
    }
  }
}

void sensor() {
  if(outputValue==0){
    statusValue="Waiting...";
  }
  else if(outputValue>0){
    statusValue="Air mendekati batas, silakan dimatikan.";
  }
}

