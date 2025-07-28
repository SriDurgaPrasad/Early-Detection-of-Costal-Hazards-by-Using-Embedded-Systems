#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>

// Define sensor pins
#define DHTPIN D4  
#define DHTTYPE DHT11
#define ADXL335_X A0  
const char* ssid = "YourWiFiSSID";  
const char* password = "YourWiFiPassword";  
const char* thingSpeakAPI = "YOUR_THINGSPEAK_WRITE_API_KEY";

// Create sensor objects
Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);

// SIM800L serial communication
SoftwareSerial sim800(D7, D6); //rx,tx

// Structure to hold sensor data
typedef struct struct_message {
  float temperature;
  float humidity;
  float pressure;
  float altitude;
  float accelerationX;
  bool fallDetected;
} struct_message;

struct_message sensorData;

// MAC address of receiver NodeMCU
uint8_t receiverMAC[] = {0xc8, 0xc9, 0xa3, 0x2e, 0xfa, 0x71}; 

void sendData(uint8_t *mac, uint8_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == 0 ? "Success" : "Fail");
}

// Function to send SMS using SIM800L
void sendSMS() {
  Serial.println("Sending SMS...");
  sim800.println("AT+CMGF=1");  
  delay(1000);
  sim800.println("AT+CMGS=\"+7036838379\""); // Replace with recipient phone number
  delay(1000);
  sim800.println("ABNORMAL CONDITIONS IDENTIFIED AT SEA SHORE SO PLEASE BE ALERT!!!");
  delay(1000);
  sim800.write(26); // Send SMS (CTRL+Z)
  Serial.println("SMS Sent!");
Serial.println("Sending SMS...");
  sim800.println("AT+CMGF=1");  
  delay(1000);
  sim800.println("AT+CMGS=\"+9553943272\""); // Replace with recipient phone number
  delay(1000);
  sim800.println("ABNORMAL CONDITIONS IDENTIFIED AT SEA SHORE SO PLEASE BE ALERT!!!");
  delay(1000);
  sim800.write(26); // Send SMS (CTRL+Z)
  Serial.println("SMS Sent!");
  Serial.println("Sending SMS...");
  sim800.println("AT+CMGF=1");  
  delay(1000);
  sim800.println("AT+CMGS=\"+8019935367\""); // Replace with recipient phone number
  delay(1000);
  sim800.println("ABNORMAL CONDITIONS IDENTIFIED AT SEA SHORE SO PLEASE BE ALERT!!!");
  delay(1000);
  sim800.write(26); // Send SMS (CTRL+Z)
  Serial.println("SMS Sent!");
  }

void setup() {
  Serial.begin(115200);
  sim800.begin(9600); 
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");


  WiFi.mode(WIFI_STA);

  if (!bmp.begin()) {
    Serial.println("BMP180 not found!");
    while (1);
  }

  dht.begin();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW Initialization Failed!");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(sendData);
}

void loop() {
  sensorData.temperature = dht.readTemperature();
  sensorData.humidity = dht.readHumidity();
  sensorData.pressure = bmp.readPressure() / 100.0;
  sensorData.altitude = bmp.readAltitude();
  Serial.println("Temperature:");
  Serial.println(sensorData.temperature);
  delay(15);
Serial.println("Humidity:");  
  Serial.println(sensorData.humidity);
  delay(15);
Serial.println("Pressure:");
  Serial.println(sensorData.pressure);
    delay(15);
  Serial.println("altitude:");
  Serial.println(sensorData.altitude);
  delay(15);
  int rawX = analogRead(ADXL335_X);
  //float voltageX = (rawX / 1023.0) * 3.3;
  sensorData.accelerationX = (rawX) / 10;
//  sensorData.accelerationX = (voltageX - 1.65) / 0.3;
Serial.println("Fall:");
  Serial.println(sensorData.accelerationX);
    delay(15);
  if (sensorData.accelerationX > 53 || sensorData.accelerationX < 47 || sensorData.temperature > 35 || sensorData.humidity > 75 || sensorData.pressure > 109) 
  {
    sensorData.fallDetected = true;
    sendSMS();
    Serial.println("Sending data...");
    sendDataToThingSpeak(temperature, humidity, pressure);

    delay(15000);  // ThingSpeak allows updates every 15 seconds
  } else {
    sensorData.fallDetected = false;
  }

  esp_now_send(receiverMAC, (uint8_t *)&sensorData, sizeof(sensorData));

  Serial.println("Data Sent!");
  delay(2000);
}
void sendDataToThingSpeak(float temperature, float humidity, float pressure) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "http://api.thingspeak.com/update?api_key=" + String(thingSpeakAPI) +
                     "&field1=" + String(temperature) +
                     "&field2=" + String(humidity) +
                     "&field3=" + String(pressure);

        http.begin(client, url);
        int httpCode = http.GET();
        if (httpCode > 0) {
            Serial.println("Data Sent to ThingSpeak");
        } else {
            Serial.println("Error sending data");
        }
        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}
