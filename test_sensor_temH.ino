#include <stdio.h>

#include "DHT.h"



DHT dht;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(2); // data pin 2

  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
 
}

void loop()
{
  delay(1500);

  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);

  if (dht.getTemperature() <= 26){
    digitalWrite (10,HIGH);
    digitalWrite (11,LOW);
  }
  if (dht.getTemperature() > 28){
    digitalWrite (10,LOW);
    digitalWrite (11,HIGH);
  }
}
