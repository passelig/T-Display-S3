#include "TFT_eSPI.h"

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
int loopCounter = 0;

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "CP-S_Norway-2GHz";
const char* password = "robotino";

//Your Domain name with URL path or IP address with path
String serverName = "http://172.21.11.90/fcgi-bin/?{%22TYPE%22:%22getBatteryInfo%22,%22A%22:0}";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
String myIp = "";

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  
  sprite.createSprite(320,170);  
  sprite.fillSprite(TFT_WHITE);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("NO WIFI, yet..",60,44);
  sprite.drawString("ssid: " + String(ssid),60,80);  
  sprite.pushSprite(0,0);  
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  myIp = WiFi.localIP().toString().c_str();
  Serial.println(myIp);
 
  Serial.println("it will take 5 seconds before publishing the first reading.");

 
}

void loop() {
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName.c_str());
      int httpResponseCode = http.GET();// Send HTTP GET request
      
      if (httpResponseCode>0) {
        sprite.drawString("HTTP Response " + String(httpResponseCode),10,77);
        String payload = http.getString();
        Serial.println(payload);
        delay(2000);
      } else {
        sprite.drawString("HTTP Error " + String(httpResponseCode),10,77);
      }
      http.end();// Free resources
    } else {
      sprite.drawString("WiFi Disconnected ",10,77);
    }
    lastTime = millis();
  }

 sprite.drawString("Connected to: " + String(ssid) ,10,10);
 sprite.drawString("MyIp: " + myIp,10,44); 
 sprite.pushSprite(0,0);
 delay(500);
 loopCounter +=1;
 Serial.println("MyIp: " + myIp );
}
