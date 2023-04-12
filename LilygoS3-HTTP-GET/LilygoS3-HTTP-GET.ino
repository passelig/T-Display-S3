//#include "install.h"
#include "TFT_eSPI.h"
#include <DHT.h>

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
int loopCounter = 0;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
}



void loop() {
 sprite.fillSprite(TFT_WHITE);
 sprite.setFreeFont(&Orbitron_Light_24);
 sprite.drawString("Some long string 10,10",10,10);
 sprite.drawString("Short 10,44",10,44); 
 sprite.drawString("Loop counter " + String(loopCounter),10,77);
 sprite.pushSprite(0,0);
 delay(500);
 loopCounter +=1;
}
