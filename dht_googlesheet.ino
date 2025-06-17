/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이 코드는 DHT11 온습도 센서를 사용하여 데이터를 측정하고,
// 이를 WiFi를 통해 Google Sheets로 JSON 형식으로 전송하며, 수신된 정보를 OLED에 표시하는 예제입니다.
// Google Apps Script는 JSON POST 요청을 처리하도록 설정되어 있어야 합니다.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------라이브러리 포함
#include <WiFi.h>        // ESP32 WiFi 라이브러리
#include <HTTPClient.h>  // HTTP 요청 라이브러리
#include <ArduinoJson.h> // JSON 생성 라이브러리

#include <Wire.h>             // I2C 통신 라이브러리 (OLED에 필요)
#include <Adafruit_GFX.h>     // Adafruit 그래픽 라이브러리
#include <Adafruit_SSD1306.h> // SSD1306 OLED 디스플레이 라이브러리

#include <DHT.h> // DHT 온습도 센서 라이브러리

//----------------------------------------

// DHT 센서 설정
#define DHTPIN 4      // DHT 센서가 연결된 GPIO 핀 번호
#define DHTTYPE DHT11 // 사용하는 DHT 센서 타입 (DHT11, DHT22 등)
DHT dht(DHTPIN, DHTTYPE);

// OLED 화면 설정
#define SCREEN_WIDTH 128 // OLED 너비 (픽셀)
#define SCREEN_HEIGHT 64 // OLED 높이 (픽셀)
#define OLED_RESET -1    // 리셋 핀 번호 (-1이면 ESP32 리셋 공유)
#define SCREEN_ADDRESS 0x3C // OLED I2C 주소
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ESP32 보드의 내장 LED 핀 정의 (선택 사항)
#define On_Board_LED_PIN 2

//----------------------------------------WiFi 네트워크 SSID 및 비밀번호
const char *ssid = "USE_WIFI"; // 실제 사용하는 WiFi SSID로 변경하세요.
const char *password = ""; // 실제 사용하는 WiFi 비밀번호로 변경하세요.
//----------------------------------------

const char* Web_App_URL = "https://script.google.com/macros/s/AKfycbyVb9Ns_Na9KQ_uaOdJyq2noWHUZBRanEiqnjlaUyH1bscrjLD-FCVXRN2gujvbDg97vw/exec"; // 실제 Google Apps Script URL로 변경하세요.
const char* Station_Id = "스마일버그"; 

// 전역 변수
String Status_Read_Sensor = "Initializing..."; // 초기 상태
float Temp = 0.0; // 측정될 온도 값
float Humd = 0.0; // 측정될 습도 값

unsigned long previousMillis = 0;
const long interval = 60000; // 60초 간격으로 센서 측정 및 데이터 전송

// OLED 화면에 정보 업데이트하는 함수
void updateOLED() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 5);
    display.print("Status: ");
    display.println(Status_Read_Sensor);

    display.setCursor(0, 25);
    display.setTextSize(2); // 큰 글씨로 표시
    display.print(Temp, 1);
    display.print(" C");

    display.setCursor(0, 45);
    display.print(Humd, 1);
    display.print(" %");

    display.display();
}

// Google Sheets로 데이터를 전송하는 함수
void sendToSheets() {
    if (WiFi.status() == WL_CONNECTED) {
        if (Status_Read_Sensor == "Success") { // 성공적으로 측정되었을 때만 전송

            StaticJsonDocument<256> jsonDoc;
            jsonDoc["전송명"] = Station_Id;
            jsonDoc["온도"] = Temp;
            jsonDoc["습도"] = Humd;

            String jsonString;
            serializeJson(jsonDoc, jsonString);

            Serial.println("\n-------------");
            Serial.println("Sending JSON data to Google Spreadsheet...");
            Serial.println("JSON data: " + jsonString);

            HTTPClient http;
            http.begin(Web_App_URL); // [개선] const char*를 직접 사용
            http.addHeader("Content-Type", "application/json");

            int httpCode = http.POST(jsonString);

            Serial.print("HTTP Status Code : ");
            Serial.println(httpCode);

            if (httpCode > 0) {
                String payload = http.getString();
                Serial.println("Response payload: " + payload);
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == 302) {
                    Serial.println("Google Sheets upload success (assumed).");
                } else {
                    Serial.println("Check Google Sheets response.");
                }
            } else {
                Serial.printf("HTTP POST failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
            Serial.println("-------------");
        } else {
            Serial.println("Skipping send to Google Sheets: Sensor read was not successful.");
        }
    } else {
        Serial.println("WiFi Disconnected. Cannot send data.");
        Status_Read_Sensor = "WiFi Down";
        updateOLED();
    }
}

// DHT 센서에서 온습도를 읽는 함수
void readSensor() {
    Humd = dht.readHumidity();
    Temp = dht.readTemperature(); // 섭씨

    if (isnan(Humd) || isnan(Temp)) {
        Serial.println("Failed to read from DHT sensor!");
        Status_Read_Sensor = "Sensor Fail";
        // 실패 시 값을 초기화하여 OLED에 0이 아닌 이전 값이 표시되는 것을 방지
        Temp = 0.0;
        Humd = 0.0;
        return;
    }

    Status_Read_Sensor = "Success";
    Serial.print("Sensor Read Success: ");
    Serial.print("Temp: ");
    Serial.print(Temp);
    Serial.print(" C, Humid: ");
    Serial.print(Humd);
    Serial.println(" %");

    digitalWrite(On_Board_LED_PIN, HIGH);
    delay(100);
    digitalWrite(On_Board_LED_PIN, LOW);
}

//________________________________________________________________________________VOID SETUP()
void setup() {
    Serial.begin(115200);
    Serial.println("\nESP32 DHT Sensor to Google Sheets Uploader");
    delay(1000);

    pinMode(On_Board_LED_PIN, OUTPUT);
    digitalWrite(On_Board_LED_PIN, LOW);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
    }
    Serial.println(F("OLED Initialized"));
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("DHT Sensor Uploader");
    display.display();
    delay(1000);

    dht.begin();
    Serial.println("DHT sensor started.");

    display.println("WiFi Connecting...");
    display.display();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    // [개선] WiFi 연결 타임아웃(20초) 및 재부팅 로직 추가
    int wifi_timeout_count = 40; // 0.5초 * 40 = 20초
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
        if (wifi_timeout_count-- <= 0) {
            Serial.println("\nWiFi connection timed out. Restarting...");
            ESP.restart();
        }
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("------------");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Connected!");
    display.print("IP: ");
    display.println(WiFi.localIP().toString().substring(0, 15));
    display.display();
    delay(2000);

    // [개선] 부팅 후 첫 데이터 바로 전송
    previousMillis = millis() - interval; // 루프가 바로 실행되도록 설정
}
//________________________________________________________________________________

//________________________________________________________________________________VOID LOOP()
void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        Serial.println("Reading sensor data...");
        readSensor();
        updateOLED();
        sendToSheets();
    }
}
//________________________________________________________________________________
