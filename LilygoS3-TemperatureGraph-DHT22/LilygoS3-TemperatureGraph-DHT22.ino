#include "Arduino.h"
#include "TFT_eSPI.h"/* Please use the TFT library provided in the library. */
#include "DHT.h"

TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd);
#define numOfValues 20
float measurmentPoints[numOfValues]={0};
int gw=294;
int gh=102;
int gx=20;
int gy=154;
float current=0;
float pixelsPerDegree = gh /12;
int yStartTemp = 18;

#define grey 0xDF7E
#define blue 0x0967
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9
#define black 0x0000
DHT dht(16,DHT22);    




void setup(void)
{
  dht.begin();  
  Serial.begin(115200);
  lcd.init();
  lcd.fillScreen(TFT_BLACK);
  lcd.setRotation(1);
   
  sprite.createSprite(320, 170);
  sprite.setTextDatum(3);
  sprite.setSwapBytes(true);
  measurmentPoints[numOfValues-1]=yStartTemp;
  analogReadResolution(10);
}



void loop()
{
  current = dht.readTemperature(); 
  if (current > 100){
    current=28.66  ; 
  }
  
 for(int i=0; i<numOfValues ;i++){
  measurmentPoints[i]=measurmentPoints[i+1];
 }
 measurmentPoints[numOfValues-1]=current;

  sprite.fillSprite(TFT_WHITE);
  sprite.setTextColor(TFT_WHITE,blue);
  sprite.fillRoundRect(6,5,250,35,4,blue);
  sprite.drawString("Temperature " + String(current),10,24,4);
  sprite.setFreeFont();

  // Vertical grid lines
  for(int i=1;i<20;i++){
   sprite.drawLine(gx+(i*17),gy,gx+(i*17),gy-gh,grey);
  }
  // Horizontal grid lines
sprite.setTextColor(TFT_BLACK,TFT_WHITE);  
  for(int i=1;i<6;i++){
   sprite.drawLine(gx,gy-(i*17),gx+gw,gy-(i*17),grey);
   sprite.drawString(String(yStartTemp+(i*2)),gx-16,gy-(i*17));
  }

  sprite.drawLine(gx,gy,gx+gw,gy,TFT_BLACK);  //Horizontal axis line
  sprite.drawLine(gx,gy,gx,gy-gh,TFT_BLACK);    // Vertical axis line
  
  // Draw the graph  
  for(int i=0;i<numOfValues;i++){
    sprite.drawLine(gx+(i*17),gy-(measurmentPoints[i]-yStartTemp)*pixelsPerDegree,gx+((i+1)*17),gy-(measurmentPoints[i+1]-yStartTemp)*pixelsPerDegree,TFT_RED);
  }
  sprite.pushSprite(0,0);
  delay(1000);
}

  