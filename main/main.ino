#define step1 22
#define dir1 23
#define step2 24
#define dir2 25
#define step3 26
#define dir3 27
#define step4 28
#define dir4 29

#define step5 30
#define dir5 31

#define RX 0
#define TX 1

#define servo_levo 32
#define servo_desno 33
#define servo_grab_grab 34
#define servo_vakuum 35

const int t = 500;

void setup() {
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
}

void loop() {
  OneStep(1);
  Dir0(1);
  OneStep(1);
  Dir1(1);
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
