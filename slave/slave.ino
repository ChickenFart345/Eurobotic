#include <String.h>

int x;
String receivedData = "";

void setup() {
  Serial.begin(38400);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
void parseData(String data) {
  x = data.toInt();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseData(receivedData);
      receivedData = "";
    } 
    else receivedData += c;
  }

  if(x>812)
  {
    digitalWrite(7, HIGH);

    digitalWrite(6, HIGH);
    delayMicroseconds(500);
    digitalWrite(6, LOW);
    delayMicroseconds(500);
  }
  if(x<212)
  {
    digitalWrite(7, LOW);

    digitalWrite(6, HIGH);
    delayMicroseconds(500);
    digitalWrite(6, LOW);
    delayMicroseconds(500);
  }
}