#include <stdio.h> //เรียกคำสั่งทุกชุดมาใช้

#include "DHT.h" //เรียกคำสั่งเซนเซอร์อุณหภูมิ

#include <Wire.h>  //เรียกคำสั่งสื่อสารข้อมูลกับบอร์ด
#include <LiquidCrystal_I2C.h> //เรียกคำสั่งสื่อสารข้อมูลกับบอร์ด

LiquidCrystal_I2C lcd(0x27, 16, 2); //สั่งงานกับจอ LCD
DHT dht; //ตัวแปรแทนคำสั่ง

int buzzer = 7; //ตัวแปรแทนคำสั่ง
void setup() //เรียกฟังชั่นมาทำงาน
{
  Serial.begin(9600); //อัตราการส่งข้อมูล
  Serial.println(); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)"); //แสดงข้อมูล
 
  dht.setup(2); // data pin 2 //ตัวแปรเซ้นเซอร์ที่pin2

  lcd.begin(); //ฟังก์ชั่นการเรียกการส่งข้อมมูลLCD
  pinMode(10,OUTPUT); //ไฟLCDที่pin10
  pinMode(11,OUTPUT); //ไฟLCDที่pin11
  pinMode(buzzer ,OUTPUT);//เครื่องspeaker
  digitalWrite(buzzer , HIGH); // สร้างเสียงเตือน
    
}

void loop() //ฟังก์ชั่นการเรียกการทำวนซ้ำ
{
  delay(1500); //หน่วงเวลาที่ 1.5 วินาที

  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  
  lcd.display (); //ฟังก์ชั่นการเรียกการส่งข้อมูลจอLCD
  
  Serial.print(dht.getStatusString()); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.print("\t"); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.print(humidity, 1); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.print("\t\t"); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.print(temperature, 1); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.print("\t\t"); //ฟังก์ชั่นการแสดงข้อมูล
  Serial.println(dht.toFahrenheit(temperature), 1); //แสดงข้อมูล

  if (dht.getTemperature() <= 24){ //ฟังก์ชั่นเงื่อนไข
    digitalWrite (10,HIGH); //ฟังก์ชั่นการเปิดไฟ
    digitalWrite (11,LOW); //ฟังก์ชั่นการดับไฟ
    lcd.setCursor(4, 0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print(dht.getTemperature());
    lcd.setCursor(10, 0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print(" C"); //ฟังก์ชั่นการแสดงข้อมูล
    lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print("Yellow : LED ON ");  //ฟังก์ชั่นการแสดงข้อมูล
     digitalWrite(buzzer , HIGH); // สร้างเสียงเตือน
    delay(1000); // ร้องค้างไว้ 1 วินาที
    digitalWrite(buzzer , LOW); //หยุดร้อง
    delay(3600000); // หยุดร้อง 1 ชั่วโมง 
   
  }
  if (dht.getTemperature() > 25){ //ฟังก์ชั่นเงื่อนไข
    digitalWrite (10,LOW);//ฟังก์ชั่นการปิดไฟ
    digitalWrite (11,HIGH);//ฟังก์ชั่นการเปิดไฟ
    lcd.setCursor(4, 0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print(dht.getTemperature());
    lcd.setCursor(10, 0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print(" C"); //ฟังก์ชั่นการแสดงข้อมูล
    lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
    lcd.print("  RED : LED ON "); //ฟังก์ชั่นการแสดงข้อมูล
    digitalWrite(buzzer , HIGH); // สร้างเสียงเตือน
    delay(1000); // ร้องค้างไว้ 1 วินาที
    digitalWrite(buzzer , LOW); //หยุดร้อง
    delay(1800000); // หยุดร้อง ครึ่งชั่วโมง
  }

}