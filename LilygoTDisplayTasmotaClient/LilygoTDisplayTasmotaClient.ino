#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>  // TFT library
#include <SPI.h>

// Wi-Fi credentials
const char* ssid = "Sommerro";
const char* password = "";

// Tasmota HTTP URL
const char* tasmotaURL = "http://192.168.1.108/cm?cmnd=Status%208";

// TFT instance
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  // Initialize screen
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Load the largest font (Font 8)
  tft.loadFont("Font4");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 40);
  tft.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tft.print(".");
  }

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 40);
  tft.print("WiFi Connected");
  delay(1000);
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(tasmotaURL);

    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      float temp = doc["StatusSNS"]["DS18B20"]["Temperature"];

      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setTextDatum(MC_DATUM);  // Middle center for alignment
      tft.setTextFont(7);          // Large built-in font
      tft.drawString(String(temp, 1) + " C", 120, 80);  // Adjust X/Y to your screen
    } else {
      Serial.printf("HTTP GET failed, code: %d\n", httpCode);
      tft.fillScreen(TFT_RED);
      tft.setTextFont(2);
      tft.setCursor(10, 40);
      tft.setTextColor(TFT_WHITE, TFT_RED);
      tft.print("HTTP Error");
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
    tft.fillScreen(TFT_RED);
    tft.setTextFont(2);
    tft.setCursor(10, 40);
    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.print("WiFi Error");
  }

  delay(10000);  // Update every 10 seconds
}
