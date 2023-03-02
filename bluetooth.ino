#include <SoftwareSerial.h>
#include <DHT.h>
#define intervallo 2000  // intervallo per il millis

DHT dht(10, DHT11);
SoftwareSerial Bluetooth(8, 9); // RX, TX

char Incoming_value = 0;    // LED On = 1 / Off = 0
unsigned long tempo = 0;    // tempo precedente per il millis
String temperatura, umidita; // valore acquisito dal DHT11 dopo casting

void setup() 
{
  Serial.begin(9600);    // seriale USB     
  pinMode(13, OUTPUT);      //LED BuilT In
  dht.begin();  
  Bluetooth.begin(9600); // set the data rate for the SoftwareSerial port
}

void loop()
{
  // gestione dati  
  
   if ((millis()-tempo)>intervallo)
  {
  temperatura = String(dht.readTemperature());
  Bluetooth.print(temperatura); // invia al Bluetooth
  Serial.print("temperatura: ");
  Serial.print(temperatura);

  Bluetooth.print("-");   // invia al Bluetooth come discriminante
  
  umidita = String(dht.readHumidity());
  Bluetooth.print(umidita); // invia al Bluetooth
  Serial.print(" - umidità: ");
  Serial.println(umidita);
  
  tempo = millis();
  }
  
  // gestione LED On/Off
  if(Bluetooth.available() > 0)  
  {
    Incoming_value = Bluetooth.read();      
    Bluetooth.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(13, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(13, LOW);   
  }                            
}