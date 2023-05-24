#include "Arduino.h"
#include "TFT_eSPI.h"/* Please use the TFT library provided in the library. */
#include "DHT.h"

TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd);

float values[24]={0};
float values2[24]={0};

int gw=294;
int gh=102;
int gx=20;
int gy=144;
float current=0;
#define gray 0x6B6D
#define blue 0x0967
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9
DHT dht(16,DHT22);    

int deb=0;
int Mode=0;


void setup(void)
{
  //pinMode(RIGHT,INPUT_PULLUP);
 dht.begin();  
  Serial.begin(115200);
  lcd.init();
  lcd.fillScreen(TFT_BLACK);
  lcd.setRotation(1);
  Serial.println("");
  Serial.println("WiFi connected.");
   
  sprite.createSprite(320, 170);
  sprite.setTextDatum(3);
  sprite.setSwapBytes(true);
  values[23]=gh/2;
  analogReadResolution(10);
}

int counter=0;
int Min=gh/2;
int Max=gh/2;
int average=0;
String minT="";
String maxT="";

void loop()
{
  current = dht.readTemperature(); 
  if (current > 100){
    current=88.66  ; 
  }
  
 
 for(int i=0;i<24;i++)
 values2[i]=values[i];

 for(int i=23;i>0;i--)
 values[i-1]=values2[i];
 values[23]=current;
 
  for(int i=0;i<24;i++)
  average=average+values[i];
  average=average/24;

  sprite.fillSprite(TFT_BLACK);
  sprite.setTextColor(TFT_WHITE,blue);
  sprite.fillRoundRect(6,5,78,35,4,blue);
  sprite.fillRoundRect(120,5,76,35,4,purple);
  sprite.drawString(String(current),10,24,4);
  sprite.setTextColor(TFT_WHITE,purple);
  sprite.drawString("Mode: "+String(Min),126,16,2);
  sprite.setFreeFont();

  // Vertical grid lines
  for(int i=1;i<20;i++){
   sprite.drawLine(gx+(i*17),gy,gx+(i*17),gy-gh,gray);
  }
  // Horizontal grid lines
  for(int i=1;i<6;i++){
   sprite.drawLine(gx,gy-(i*17),gx+gw,gy-(i*17),gray);
   sprite.drawString(String(i*17),gx-16,gy-(i*17));
  }

  sprite.drawLine(gx,gy,gx+gw,gy,TFT_WHITE);  //Horizontal axis line
  sprite.drawLine(gx,gy,gx,gy-gh,TFT_WHITE);    // Vertical axis line
  
  // Draw the graph  
  for(int i=0;i<23;i++){
    sprite.drawLine(gx+(i*17),gy-values[i],gx+((i+1)*17),gy-values[i+1],TFT_RED);
  }
  sprite.pushSprite(0,0);
  delay(1000);
}

  