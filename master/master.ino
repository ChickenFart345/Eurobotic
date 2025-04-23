int x = 0;

void setup() {
  Serial.begin(38400);

  pinMode(A0, INPUT);
}

void loop() {
  x = analogRead(A0);
  Serial.println(x);
  delay(10);
}
