const int pwmPin = 16;  // Define the GPIO pin for PWM output

void setup() {
  // Configure the PWM pin as an OUTPUT
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Update the PWM duty cycle using analogWrite
  analogWrite(pwmPin, 125);
  Serial.println("dutyCycle1: " + String(125));
  delay(1500);

  // Update the PWM duty cycle using analogWrite
  analogWrite(pwmPin, 200);
  Serial.println("dutyCycle2: " + String(200));
  delay(1500);
}
