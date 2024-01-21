
#include <SoftwareSerial.h>

byte GET_ADDRESS[8] = { 0xFF, 0x03, 0x02, 0x00, 0x00, 0x01, 0x90, 0x6C };
byte GET_DISTANCE[8] = { 0x01, 0x03, 0x01, 0x00, 0x00, 0x01, 0x85, 0xF6 };
byte highByte = 0x00;
byte lowByte = 0x00;

SoftwareSerial mySerial(10, 13);  //RX-RO, TX-DI
#define RECEIVER_ENABLE 11        // LOW enable
#define DRIVER_ENABLE 12          // HIGH enable

#define TIMEOUT_DELAY 5000

unsigned long myMillis = 0;

void sendData(String note, byte *data) {
  myMillis = millis();
  digitalWrite(RECEIVER_ENABLE, HIGH);
  digitalWrite(DRIVER_ENABLE, HIGH);
  Serial.print(note);
  for (int i = 0; i < 8; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  Serial.flush();
  mySerial.write(data, 8);
  mySerial.flush();
  digitalWrite(RECEIVER_ENABLE, LOW);
  digitalWrite(DRIVER_ENABLE, LOW);
  delay(10);
}

void receiveData() {
  byte data[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  while (mySerial.available() == 0) {
    if (millis() - myMillis > TIMEOUT_DELAY) {
      Serial.println("Request Timed Out...");
      break;
    }
  }
  if (mySerial.available() > 0) {
    mySerial.readBytes(data, 7);
    Serial.print("Distance: ");
    for (int i = 0; i < 7; i++) {
      if (i == 3) {
        highByte = data[i];
      }
      if (i == 4) {
        lowByte = data[i];
      }
    }
    int distance = (highByte << 8) | lowByte;
    Serial.println(String(distance/10.0) + "cm");
  }
  delay(10);
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  Serial.println("Begin Program...");
  pinMode(DRIVER_ENABLE, OUTPUT);
  pinMode(RECEIVER_ENABLE, OUTPUT);
  sendData("Getting Address: ", GET_ADDRESS);
  receiveData();
}

void loop() {
  sendData("Getting Distance: ", GET_DISTANCE);
  receiveData();
  delay(100);
}