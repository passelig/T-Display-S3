#include "TFT_eSPI.h"

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("LILYGO EXT 5V",60,44); 
  sprite.drawString("T-Display-S3",70,104); 
  sprite.pushSprite(0,0);
  pinMode(15, OUTPUT); // to boot with battery...
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB
}


void loop() {
}

