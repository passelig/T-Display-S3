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
  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorLeftPin2, OUTPUT);
  pinMode(pwmRight, OUTPUT);
  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorRightPin2, OUTPUT);

  digitalWrite(pwmLeft, HIGH); // use these two lines to test a single motor at a time
  digitalWrite(pwmRight, HIGH);
  delay(3000);
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
