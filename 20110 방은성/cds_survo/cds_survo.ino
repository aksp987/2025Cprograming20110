#include<ESP32Servo.h>
Servo myservo;
int servoPin=18;
int angle=0;
int potPin =35;
int led=4;
int potValue=0;

void setup() { 
myservo.attach(servoPin);
pinMode(potPin,INPUT);
Serial.begin(115200);  
}
void loop() {
potValue=analogRead(potPin);
if(potValue>800){
angle=0;
}
else{
  angle=180;
}
myservo.write(angle);
  Serial.print("Potentiometer Value: "); 
  Serial.println(potValue);  
}