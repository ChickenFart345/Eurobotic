
void setup() {
  Serial.begin(38400);
}

void loop() {
  int broj1 = 123;
  int broj2 = 456;
  int broj3 = 789;

  Serial.print(broj1);
  Serial.print(",");
  Serial.print(broj2);
  Serial.print(",");
  Serial.println(broj3);

  delay(1000);
}