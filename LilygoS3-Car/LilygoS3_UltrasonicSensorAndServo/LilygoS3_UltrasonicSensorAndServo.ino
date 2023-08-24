#include <ESP32Servo.h>
#include "TFT_eSPI.h"

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int trigPin = 12;
int echoPin = 13;
int servoPin = 11;
float distance;
float distanceToTheRight;
float distanceToTheLeft;
int toTheLeft =180;
int toTheRight = 0;
int straitAhead = 90;

Servo servoMotor;

void setup()
{ 
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("LILYGO EXT 5V",60,24); 
  sprite.drawString("Ultrasonic Sensor",30,74); 
  sprite.drawString("with Servoz",80,104); 
  sprite.pushSprite(0,0);

  pinMode(15, OUTPUT); // to boot with battery...
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(115200);
  servoMotor.attach(servoPin, 500, 2500);
  servoMotor.write(straitAhead);

  delay(1000);
}

void loop()
{
  delay(500);
  distance = readDistance();
  Serial.println("Distance = " + String(distance));
 
  if (distance <= 30){
    servoMotor.write(toTheLeft); 
    delay(500);
    distanceToTheLeft = readDistance();
    servoMotor.write(toTheRight);
    delay(500); 
    distanceToTheRight= readDistance();
    delay(500);
    servoMotor.write(straitAhead); 
    delay(300);   
    Serial.println("distanceToTheLeft = " + String(distanceToTheLeft));
    Serial.println("distanceToTheRight = " + String(distanceToTheRight));
    if (distanceToTheLeft >  distanceToTheRight){
      turnLeft();
    } else {
      turnRight();
    }
   }
}

void turnLeft () {
  Serial.println("Turning Left");
}

void turnRight () {
  Serial.println("Turning Right");
}

float readDistance() {
  int pingTravelTime;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pingTravelTime = pulseIn(echoPin,HIGH);
  distance = ((pingTravelTime-200.)/60.)+1;
  return distance;
}