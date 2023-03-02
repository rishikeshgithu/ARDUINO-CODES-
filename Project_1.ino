#include <ESP8266WiFi.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


#include <ThingSpeak.h>

const char* ssid     = "appa";
const char* password ="appaappa";

WiFiClient client;
unsigned long myChannelNumber = 2045411;
const char * myWriteAPIKey = "BCCDH2DKZFYGT8T9";

const int trigPin = 12;
const int echoPin = 14;
const int D1 = 5;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.println("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.println("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(1000);

  ThingSpeak.writeField(myChannelNumber, 1, distanceCm, myWriteAPIKey);
  delay(100);
}