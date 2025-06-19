#include "DHT.h"

#define DHTPIN   25  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#include<ESP32Servo.h>
Servo myservo;
int servoPin=18;
int angle=0;

void setup() {
pinMode(2,OUTPUT);
Serial.begin(115200);
Serial.println(F("DHTxx test!"));
dht.begin();
u8g2.begin();
u8g2.enableUTF8Print();
u8g2.clearBuffer();
u8g2.setFont(u8g2_font_ncenB14_tr);
u8g2.drawStr(0, 15, "hello world!");
u8g2.drawTriangle(27,50, 64,32, 100,50);
u8g2.sendBuffer();
delay(1000);
myservo.attach(servoPin);
}

void loop() {
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t) ) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
}
if(t>=32 && h>=80){
digitalWrite(2,HIGH);
}
else{
digitalWrite(2,LOW);
}
Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("%  Temperature: "));
Serial.println(t);
u8g2.setFont(u8g2_font_unifont_t_korean2);
u8g2.clearBuffer();
u8g2.setCursor(0, 10);
u8g2.print("온도:");  
u8g2.print(t);
u8g2.setCursor(0, 40);
u8g2.print("습도:");  
u8g2.print(h);
u8g2.sendBuffer();
if(potValue>800){
angle=0;
}
else{
  angle=180;
}
myservo.write(angle);
}