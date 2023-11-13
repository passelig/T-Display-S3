const int startButton = 14;
const int pwmENAPin = 43;  // Define the GPIO pin for PWM output
const int pwmENBPin = 16;  // Define the GPIO pin for PWM output
const int IN1Pin = 44;  // Define the GPIO pins for motor A
const int IN2Pin = 18;  // Define the GPIO pins for motor A
const int IN3Pin = 17;  // Define the GPIO pins for motor B
const int IN4Pin = 21;  // Define the GPIO pins for motor B
const int delayTime = 1000;
int pwmSpeed = 255;

void setup() {
  // Configure the PWM pin as an OUTPUT
  pinMode(pwmENAPin, OUTPUT);
  pinMode(pwmENBPin, OUTPUT);
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);
  Serial.begin(9600);
  stop() ;
  pinMode(startButton, INPUT);
  delay(200);
  Serial.println("Waiting for startButton to be pressed...");
  while (digitalRead(startButton)){};
  delay(delayTime);
}

void loop() {
  analogWrite(pwmENAPin, pwmSpeed); // 255 = full speed
  analogWrite(pwmENBPin, pwmSpeed); // 255 = full speed
  rightMotorForward();
  delay(delayTime);
  stop();
  rightMotorReverse();
  Serial.println("Reverse...");
  delay(delayTime);
  stop();
  leftMotorForward();
  delay(delayTime);
  stop();
  leftMotorReverse();
  delay(delayTime);
  stop();
  pwmSpeed = toggleSpeed(pwmSpeed);
}

void rightMotorForward() {
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
}

void rightMotorReverse() {
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
}

void leftMotorForward() {
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
}

void leftMotorReverse() {
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
}

void stop() {
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
}

int toggleSpeed ( int pwmSpeed){
  if (pwmSpeed == 255){
    return 150;
  } else {
    return 255;
  }
}
