// biblioteke
#include <AccelStepper.h>
#include <Servo.h>
#include <TM1637Display.h>

// deklarisanje pinova
// beli
#define dirPrednji 2
#define stepPrednji 3
// zuti
#define dirDesni 4
#define stepDesni 5
// crveni
#define dirLevi 6
#define stepLevi 7
// prazni
#define dirZadnji 8
#define stepZadnji 9
// displej
#define CLK 11
#define DIO 12

// brzina
const int brzina = 200;
// promenljive
bool banerBool = false;
int bodovi = 0;

//Servo motori
Servo baner;
//Step motori
AccelStepper prednji(AccelStepper::DRIVER, stepPrednji, dirPrednji);
AccelStepper desni(AccelStepper::DRIVER, stepDesni, dirDesni);
AccelStepper levi(AccelStepper::DRIVER, stepLevi, dirLevi);
AccelStepper zadnji(AccelStepper::DRIVER, stepZadnji, dirZadnji);

TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
    Serial.begin(38400);
    prednji.setMaxSpeed(1200);
    desni.setMaxSpeed(1200);
    levi.setMaxSpeed(1200);
    zadnji.setMaxSpeed(1200);
    prednji.setAcceleration(200);
    desni.setAcceleration(200);
    levi.setAcceleration(200);
    zadnji.setAcceleration(200);
    baner.attach(10);
    baner.write(90);
    display.setBrightness(5);
    display.showNumberDec(bodovi, true);   
}

void loop() {
    komande(brzina);
}

int c;
void komande(float brzina){
  if (Serial.available()) {
      c = Serial.read();
      calculate(c);
  }
}

void calculate(int c) {
  if(c == 14){
    napred(brzina);
  }
  else if(c == 15){
    nazad(brzina);
  }
  else if(c == 17){
    levo(brzina);
  }
  else if(c == 16){
    desno(brzina);
  }
  else if(c == 13){
    rdesno();
  }
  else if(c == 12){
    rlevo();
  }
  else if(c == 11){
    banerFja();
  }
  else if(c < 10){
    dodajBroj(c);
  }
}

void banerFja(){
  if(!banerBool){
    baner.write(140);
  }
  else{
    baner.write(90);
  }
  banerBool = !banerBool;
}

void napred(float brzina) {
    desni.setSpeed(brzina);
    levi.setSpeed(brzina);
    if (desni.speed() != brzina) {
        desni.run();
        levi.run();
    }
    else {
        desni.runSpeed();
        levi.runSpeed();
    }
}

void nazad(float brzina){
    desni.setSpeed(-brzina);
    levi.setSpeed(-brzina);
    if (desni.speed() != brzina) {
        desni.run();
        levi.run();
    }
    else {
        desni.runSpeed();
        levi.runSpeed();
    }
}

void levo(float brzina){
    zadnji.setSpeed(brzina);
    prednji.setSpeed(brzina);
    if (zadnji.speed() != brzina) {
        zadnji.run();
        prednji.run();
    }
    else {
        zadnji.runSpeed();
        prednji.runSpeed();
    }
}

void desno(float brzina){
    zadnji.setSpeed(-brzina);
    prednji.setSpeed(-brzina);
    if (zadnji.speed() != brzina) {
        zadnji.run();
        prednji.run();
    }
    else {
        zadnji.runSpeed();
        prednji.runSpeed();
    }
}

void rdesno(){
    zadnji.setSpeed(brzina);
    prednji.setSpeed(-brzina);
    desni.setSpeed(brzina);
    levi.setSpeed(-brzina);
    if (zadnji.speed() != brzina) {
        zadnji.run();
        prednji.run();
        desni.run();
        levi.run();
    }
    else {
        zadnji.runSpeed();
        prednji.runSpeed();
        desni.runSpeed();
        levi.runSpeed();
    }
}

void rlevo(){
    zadnji.setSpeed(-brzina);
    prednji.setSpeed(brzina);
    desni.setSpeed(-brzina);
    levi.setSpeed(brzina);
    if (zadnji.speed() != brzina) {
        zadnji.run();
        prednji.run();
        desni.run();
        levi.run();
    }
    else {
        zadnji.runSpeed();
        prednji.runSpeed();
        desni.runSpeed();
        levi.runSpeed();
    }
}

void dodajBroj(int c){
  bodovi *= 10;
  bodovi += c;
  bodovi %= 1000;
  display.showNumberDec(bodovi, true);
}
