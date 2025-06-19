#include "DHT.h"

#define DHTPIN   25  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
include <Arduino.h>
#include <Adafruit_GFX.h>   
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include<ESP32Servo.h>
Servo myservo;
int servoPin=18;
int angle=0;
float h;
float t;
void updateOLED() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);


    display.setCursor(0, 25);
    display.setTextSize(2); // 큰 글씨로 표시
    display.print(t, 1);
    display.print(" C");

    display.setCursor(0, 45);
    display.print(h, 1);
    display.print(" %");

    display.display();
}
void setup() {
pinMode(2,OUTPUT);
Serial.begin(115200);
Serial.println(F("DHTxx test!"));
dht.begin();

delay(1000);
myservo.attach(servoPin);
}

void loop() {
delay(2000);
h = dht.readHumidity();
t = dht.readTemperature();
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
updateOLED():
if(t>28){
angle=0;
}
else{
  angle=180;
}
myservo.write(angle);
}
