#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CSQ");
  updateSerial();

  mySerial.println("AT+CCID");
  updateSerial();

  mySerial.println("AT+CREG?");
  updateSerial();

  mySerial.println("AT+CMGF=1\r");
  updateSerial();
}

void loop() {
  updateSerial();
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }

  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}