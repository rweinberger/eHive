#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial mySerial(13, 15); 

// ssid, password and host of an AP

const char* ssid     = "The Beehive"; //"NETWORK_SSID"
const char* password = "heythere"; //"NETWORK_PASSWORD"
const char* host = "beetches.herokuapp.com";

String msg;
String msgString;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //receive message from LoRa feather
  
  msg = recvWithStartEndMarkers();
  
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection FAILED");
    Serial.println("------------");
    return;
  }

  // We now create a URI for the request, to push data to the server

  Serial.print("Requesting path: ");
  Serial.println(msg);
  client.print(String("GET ") + String(msg) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(100);
  Serial.println("closing connection");
  Serial.println("------------");
  delay(7000);
}

String recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    msgString = "";

    //check for serial availability
    while (mySerial.available() > 0) {
        // read character from serial
        rc = mySerial.read();
        
        if (recvInProgress == true) {
            // as long as the character does not signal the end of message, append it to the msg string
            if (rc != endMarker) {
                msgString += rc;
            }
            // if the character is the end marker, terminate and return the msg
            else {
                recvInProgress = false;
                return msgString;
            }
        }
        // if character matches the start marker, flag that a message is being received
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }

    return msgString;
}

