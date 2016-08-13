/* 
Erics 3D Printer Safety System
My Youtube Channel  : http://www.youtube.com/mkmeorg
If you use this code or personalize it etc- please consider sharing it back with the world via the forum at http://www.mkme.org/forum


V1 Using MQ2 Smoke sensor digital output and a DHT 11 Temp sensor to monitor the temp inside the printing chamber
If the temp gets higher than DHT limit or smoke is triggered the relay will be de-energized shutting off the power to your printer
NOTE DHT11 only goodf to 50C so use this outside your printer and add a high temp thermistor etc inside the chamber.

*/

#include "DHT.h"  //You need this library
#define DHTPIN 2     // DHT11 Temperature Measurement
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);//unknown needed by DHT11

//MQ2 PIN
#define SMOKEPIN 4

//Power Control
#define RELAYPIN 13 //Pin for power control via relay

//Globalize variables
int t;//temperature 
int SMOKESTATE; //State check for Smoke Pin
int AlarmTemp = 48; // Alarm temp High Limit

void setup() {
Serial.begin(9600);
pinMode(RELAYPIN, OUTPUT);
pinMode(SMOKEPIN, INPUT);

dht.begin();//initialize temp and humidity
}

void loop() {
  TempFunctions();   //Do the temp related stuff
  Alarm();           //Activate alarm if applicable
}

void TempFunctions(){
  // READ Temp
  t = dht.readTemperature();
      Serial.print("Temperature: "); 
      Serial.print(t);
      Serial.println(" *C"); }
   

void Alarm(){
  SMOKESTATE = digitalRead(SMOKEPIN);
  //Shut it off if danger
  if (t >=  AlarmTemp  || SMOKESTATE == LOW ) {digitalWrite (RELAYPIN, HIGH) ;} //Checks over or under alarm OR Smoke sensor triggered
  //Insert code here or method here to stop the code from running again untill you manually reset it ...Eric didnt have time today to do this :)
  else   {digitalWrite (RELAYPIN, LOW) ;
         Serial.println(" System OKay");
  }
}
