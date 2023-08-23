#include <Servo.h>
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
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  servoMotor.attach(servoPin, 500, 2500);
  servoMotor.write(straitAhead);
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