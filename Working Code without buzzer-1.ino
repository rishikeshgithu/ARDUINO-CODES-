#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ThingSpeak.h>
#include <WiFiClient.h>


const char* ssid     = "appa";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "appaappa";     // The password of the Wi-Fi network
WiFiClient client;
unsigned long myChannelNumber = 2045411;
const char * myWriteAPIKey = "BCCDH2DKZFYGT8T9";

const int trigPin = 12;
const int echoPin = 14;
const int D2 = 4;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(D2,OUTPUT);
  ThingSpeak.begin(client);
}

void loop() { 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

  if (distanceCm < 50){
    digitalWrite(D2, HIGH);
    delay(500+(5*distanceCm));
    digitalWrite(D2, LOW);
  }
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.println("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.println("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(10);
  ThingSpeak.writeField(myChannelNumber, 1, distanceCm, myWriteAPIKey);
   
}