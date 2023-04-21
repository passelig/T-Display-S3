#include "wiring_detail.h"
#include "TFT_eSPI.h"
#include <DHT.h>


TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
//#define LCDpin 15
#define DHTpin 16
DHT dht(DHTpin, DHT22);

void setup() {
  tft.init();
  dht.begin();
  
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  tft.pushImage(160,0,161,170,wiring_detail);

  sprite.createSprite(146,170);
 
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.setTextDatum(4);
}

//temperature bar variables
int progress=0;
int w=120;
int h=18;
int x=12;
int y=90;
int blocks=0;

void loop() {
 sprite.fillSprite(TFT_WHITE);
 float temperature = dht.readTemperature();
 sprite.setFreeFont(&Orbitron_Light_32);
 sprite.drawString(String(temperature),75,54);

 progress++;
 if(progress==101)
 progress=0;

 blocks = temperature - 20;
 sprite.drawRoundRect(x,y,w,h,3,TFT_BLACK);
 for(int i=0;i<blocks;i++)
 sprite.fillRect(i*5+(x+2)+(i*1),y+4,5,10,TFT_BLACK);
 sprite.setFreeFont(&Orbitron_Light_24);
 sprite.drawString("Temperature",75,16,4);
 sprite.setTextFont(0);
 sprite.drawString("Reading temperature ",80,150);
 sprite.drawString("from DHT22 on pin 16 ",80,160);
 sprite.pushSprite(0,0);
delay(100);
}
