#include "TFT_eSPI.h"
TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

const int trigPin = 12;
const int echoPin = 13;

#define SOUND_SPEED 0.034  //define sound speed in cm/uS
long duration;
float distanceCm;
float distanceInch;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("LILYGO EXT 5V",60,44); 
  sprite.drawString("Ultrasonic-HC-SR04",10,104); 
  sprite.pushSprite(0,0);

  pinMode(15, OUTPUT); // to boot with battery...
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB
  
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  delay(1500);
}

void loop() {
  float distance = ReadDistance();
    // Prints the distance in the Serial Monitor
  String message = "Distance : " + String(distance);
  Serial.println(message);
  //writeToDisplay(message);
  delay(500);
  sprite.fillSprite(TFT_WHITE);

  // Prints the distance on the display
  sprite.drawString(message,40,60); 
  sprite.pushSprite(0,0);
 
}

float ReadDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  

  return distanceCm;

}
