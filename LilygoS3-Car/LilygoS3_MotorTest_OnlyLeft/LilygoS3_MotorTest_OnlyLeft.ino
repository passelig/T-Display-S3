void setup() {
  // Set GPIO pins as output
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(18, OUTPUT);
  // Må sette utgangene til høyre motor eksplisitt til lav for at de ikke skal begynne å kjøre
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  //Setter pwm signal for VENSTRE motor høy (full fart)
  digitalWrite(43, HIGH);
  Serial.begin(9600);
}

void loop() {
	Serial.println("Fremover i tre sekunder");
  digitalWrite(44, LOW);
  digitalWrite(18, HIGH);
  delay(3000);

  Serial.println("Bakover i tre sekunder");
  digitalWrite(44, HIGH);
  digitalWrite(18, LOW);
  delay(3000);
}
