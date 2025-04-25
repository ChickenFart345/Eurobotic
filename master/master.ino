#define X1 A0
#define Y1 A1
#define X2 A2
#define Y2 A3
#define B1 6
#define B2 7

void setup() {
  Serial.begin(38400);

  pinMode(X1, INPUT);
  pinMode(Y1, INPUT);
  pinMode(X2, INPUT);
  pinMode(Y2, INPUT);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
}

bool ready = false;
void loop() {
  if (Serial.available() > 0){
    char r = Serial.read();
    if (r == 'r') ready = true;
  }

  if (ready) {
    int x1 = analogRead(X1);
    int y1 = analogRead(Y1);
    int x2 = analogRead(X2);
    int y2 = analogRead(Y2);
    int b1 = digitalRead(B1);
    int b2 = digitalRead(B2);

    //Serial.println(x1 + ',' + y1 + ',' + x2 + ',' + y2 + ',' + b1 + ',' + b2);
    Serial.print(x1);
    Serial.print(',');
    Serial.print(y1);
    Serial.print(',');
    Serial.print(x2);
    Serial.print(',');
    Serial.print(y2);
    Serial.print(',');
    Serial.print(b1);
    Serial.print(',');
    Serial.println(b2);
    ready = false;
  }
}
