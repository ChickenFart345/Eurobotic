//definisanje pinova
#define stepL 7
#define servo 6
#define dirL 5
#define stepR 4
#define dirR 3
#define stepsPerRevolution 200

int diameter = 98;

void setup() {
  //definisanje pinmodova
  pinMode(stepL, OUTPUT);
  pinMode(servo, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(stepR, OUTPUT);
  pinMode(dirR, OUTPUT);

  //definisanje pocetnog smera
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
}

//napravi jedan step na oba motora
void step() {
  digitalWrite(stepL, HIGH);
  digitalWrite(stepR, HIGH);
  delayMicroseconds(2000);
  digitalWrite(stepL, LOW);
  digitalWrite(stepR, LOW);
  delayMicroseconds(2000);
}

void forward(int numberOfSteps) {
  for(int i = 0; i < numberOfSteps; i++){
    step();
  }
}

void rotate30(bool right) {
  if(right){
    digitalWrite(dirL, LOW);
    digitalWrite(dirR, LOW);
  }
  else{
    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, HIGH);
  }

  forward(520);

  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
}

void rotate90(bool right) {
  rotate30(right);
  rotate30(right);
  rotate30(right);
}
void loop() {
  // put your main code here, to run repeatedly:
  rotate30(520);
  delay(5000);
}
