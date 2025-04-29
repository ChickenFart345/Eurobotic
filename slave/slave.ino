#include <String.h>
#include <TM1637Display.h>

// stepper motori za kretanje
#define step1 22
#define dir1 23
#define step2 24
#define dir2 25
#define step3 26
#define dir3 27
#define step4 28
#define dir4 29

// stepper motor za dizanje sprata
#define step5 30
#define dir5 31

// bluetooth komunikacija
#define RX 0
#define TX 1

// servo motori
#define servo_levo 32
#define servo_desno 33
#define servo_grab_grab 34
#define servo_vakuum 35

// score screen
#define CLK 3
#define DIO 4

// promenljive koje dolaze sa bluetootha
int x1, y1, x2, y2, b1, b2, cifra;
// podaci sa bluetootha
String receivedData = "";
// promenljive za kretanje
const int t = 300;
const int speed = 2;
// promenljiva za score
int score = 0;

// 4-digit 7-segment display
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  Serial.begin(38400);

  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(step3, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(step4, OUTPUT);
  pinMode(dir4, OUTPUT);
  pinMode(step5, OUTPUT);
  pinMode(dir5, OUTPUT);

  digitalWrite(step1, LOW);
  digitalWrite(dir1, LOW);
  digitalWrite(step2, LOW);
  digitalWrite(dir2, LOW);
  digitalWrite(step3, LOW);
  digitalWrite(dir3, LOW);
  digitalWrite(step4, LOW);
  digitalWrite(dir4, LOW);
  digitalWrite(step5, LOW);
  digitalWrite(dir5, LOW);

  Serial.println('r');
  display.setBrightness(5);
  display.showNumberDec(score, true);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseData(receivedData);
      receivedData = "";
      Serial.println('r');
    } 
    else receivedData += c;
  }

  int stanje = CalculateState();

  if (stanje == 1) {
    Dir1(2);
    Dir0(3);
    Step(2);
    Step(3);
  }
  if (stanje == 2) {
    Dir0(2);
    Dir1(3);
    Step(2);
    Step(3);
  }
  if (stanje == 3) {
    Dir0(1);
    Dir1(4);
    Step(1);
    Step(4);
  }
  if (stanje == 4) {
    Dir1(1);
    Dir0(4);
    Step(1);
    Step(4);
  }
  if (stanje == 5) {
    Dir0(1);
    Dir0(2);
    Dir0(3);
    Dir0(4);
    Step(1);
    Step(2);
    Step(3);
    Step(4);
  }
  if (stanje == 6) {
    Dir1(1);
    Dir1(2);
    Dir1(3);
    Dir1(4);
    Step(1);
    Step(2);
    Step(3);
    Step(4);
  }

  if (cifra != -1) {
    if (cifra == -2) score = 0;
    else {
      score = score * 10 + cifra;
      score %= 1000;
    }

    cifra = -1;
    
    display.clear();
    display.showNumberDec(score);
  }
}

int CalculateState(){
  // u slucaju da su pinovi od joystick-a okrenuti na gore
  if (x1 < 150) return 1; // napred
  if (x1 > 873) return 2; // nazad
  if (y1 < 150) return 3; // levo
  if (y1 > 873) return 4; // desno
  if (y2 < 150) return 5; // pivot levo
  if (y2 > 873) return 6; // pivot desno
  return 0;
}

void parseData(String data) {
  int z1 = data.indexOf(',');
  int z2 = data.indexOf(',', z1 + 1);
  int z3 = data.indexOf(',', z2 + 1);
  int z4 = data.indexOf(',', z3 + 1);
  int z5 = data.indexOf(',', z4 + 1);
  int z6 = data.indexOf(',', z5 + 1);

  x1 = data.substring(0, z1).toInt();
  y1 = data.substring(z1 + 1, z2).toInt();
  x2 = data.substring(z2 + 1, z3).toInt();
  y2 = data.substring(z3 + 1, z4).toInt();
  b1 = data.substring(z4 + 1, z5).toInt();
  b2 = data.substring(z5 + 1, z6).toInt();

  cifra = data.substring(z6 + 1).toInt();
}

void Dir0(int i)
{
  if (i == 1) digitalWrite(dir1, LOW);
  if (i == 2) digitalWrite(dir2, LOW);
  if (i == 3) digitalWrite(dir3, LOW);
  if (i == 4) digitalWrite(dir4, LOW);
  if (i == 5) digitalWrite(dir5, LOW);
}

void Dir1(int i)
{
  if (i == 1) digitalWrite(dir1, HIGH);
  if (i == 2) digitalWrite(dir2, HIGH);
  if (i == 3) digitalWrite(dir3, HIGH);
  if (i == 4) digitalWrite(dir4, HIGH);
  if (i == 5) digitalWrite(dir5, HIGH);
}

void OneStep(int i)
{
  if (i == 1)
  {
    digitalWrite(step1, HIGH);
    delayMicroseconds(t);
    digitalWrite(step1, LOW);
    delayMicroseconds(t);
  }

  else if (i == 2)
  {
    digitalWrite(step2, HIGH);
    delayMicroseconds(t);
    digitalWrite(step2, LOW);
    delayMicroseconds(t);
  }

  else if (i == 3)
  {
    digitalWrite(step3, HIGH);
    delayMicroseconds(t);
    digitalWrite(step3, LOW);
    delayMicroseconds(t);
  }

  else if (i == 4)
  {
    digitalWrite(step4, HIGH);
    delayMicroseconds(t);
    digitalWrite(step4, LOW);
    delayMicroseconds(t);
  }

  else if (i == 5)
  {
    digitalWrite(step5, HIGH);
    delayMicroseconds(t);
    digitalWrite(step5, LOW);
    delayMicroseconds(t);
  }
}

void Step(int i){
  for (int j = 0; j < speed; j++) OneStep(i);
}
