#include "TFT_eSPI.h"

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// Motor A connections
const int pwmLeft = 43; 
const int motorLeftPin1 = 18;  // Input 1 of L298N for Motor Left
const int motorLeftPin2 = 44;  // Input 2 of L298N for Motor Left

// Motor B connections
const int pwmRight = 16; 
const int motorRightPin1 = 17; // Input 1 of L298N for Motor Right
const int motorRightPin2 = 21; // Input 2 of L298N for Motor Right

void setup() {
  // Define motor control pins as OUTPUT
  pinMode(pwmLeft, OUTPUT);
  pinMode(pwmRight, OUTPUT);
  
  digitalWrite(pwmLeft, HIGH); // use these two lines to test a single motor at a time
  digitalWrite(pwmRight, HIGH);
  
  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorLeftPin2, OUTPUT);

  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorRightPin2, OUTPUT);

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("MOTOR TEST",60,24); 
  sprite.drawString("Edit line 21,22 to",50,74); 
  sprite.drawString("test single motor",50,104);
  sprite.pushSprite(0,0);

  pinMode(15, OUTPUT); // enable boot with battery...
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB

  delay(2000);
}

void loop() {
  // Run both motors forward
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
  delay(1000); // Run forward for 1 second

  // Run both motors backward
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);
  delay(1000); // Run backward for 1 second

  // Stop both motors
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, LOW);
  delay(500); // Pause for 0.5 seconds
}
