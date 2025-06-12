int potPin = 34; 
int potValue = 0; 
int led=4;

void setup() {
  Serial.begin(115200);    
  pinMode(potPin, INPUT);  
  pinMode(led,OUTPUT); 
}

void loop() {
  potValue = analogRead(potPin);     
  int ledValue=map(potValue,0,4935,0,255);      
  analogWrite(led,ledValue);
  Serial.print("Potentiometer Value: ");   
  Serial.println(potValue);             
 
  delay(500);                         
}

