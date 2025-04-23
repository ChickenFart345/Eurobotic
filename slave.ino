String receivedData = "";

void setup() {
  Serial.begin(38400);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseData(receivedData);
      receivedData = "";
    } else {
      receivedData += c;
    }
  }
}

void parseData(String data) {
  int firstComma = data.indexOf(',');
  int secondComma = data.indexOf(',', firstComma + 1);

  int broj1 = data.substring(0, firstComma).toInt();
  int broj2 = data.substring(firstComma + 1, secondComma).toInt();
  int broj3 = data.substring(secondComma + 1).toInt();
}
