int pot=35;
int led=4;
int potValue=0;

void setup() {
pinMode(pot,INPUT);
pinMode(pot,OUTPUT);
Serial.begin(115200);    
pinMode(pot, INPUT);
}
void loop() {
potValue=analogRead(pot);
int ledValue=map(potValue,0,4095,0,255);
analogWrite(led,ledValue);
  Serial.print("Potentiometer Value: "); 
  Serial.println(potValue);  
delay(500);
}
