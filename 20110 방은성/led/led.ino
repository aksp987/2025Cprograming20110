const int r = 2;
const int g = 4;
const int b = 15;

void setup() {
  Serial.begin(115200);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  Serial.println("1이면 빨강, 2이면 초록, 3이면 파랑, 0이면 끄기~.");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      digitalWrite(r, HIGH); 
      digitalWrite(g, LOW); 
      digitalWrite(b, LOW); 
      Serial.println("빨강 is ON");

    }
    else if (input == '2') {
      digitalWrite(g, HIGH); 
      digitalWrite(r, LOW); 
      digitalWrite(b, LOW); 
      Serial.println("초록 is ON");

    }
    else if (input == '3') {
      digitalWrite(b, HIGH); 
      digitalWrite(g, LOW); 
      digitalWrite(r, LOW); 
      Serial.println("파랑 is ON");

    }
    else if (input == '0') {
      digitalWrite(r, LOW);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      Serial.println("모두 is OFF");
    }
  }
}


