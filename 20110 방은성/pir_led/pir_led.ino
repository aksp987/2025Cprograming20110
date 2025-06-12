const int pirPin = 27;
const int ledPin = 15;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("시스템 준비 완료. 움직임을 기다립니다...");
}

void loop() {
  int pirState = digitalRead(pirPin);

  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("움직임 감지! >> LED 켜짐");
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("움직임 없음. >> LED 꺼짐");
  }

  delay(200);
}

