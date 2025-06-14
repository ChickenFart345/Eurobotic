// biblioteke
#include <AccelStepper.h>
#include <Servo.h>
#include <TM1637Display.h>

// Stepper motori
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
// sprat
#define dirSprat 10
#define stepSprat 11

// en pinovi za steppere
#define enPrednji 44
#define enDesni 45
#define enLevi 46
#define enZadnji 47

// relej
#define PumpaRelejPin 48
#define EMRelejPin 49

// Servo motori
#define ServoLevi 50
#define ServoDesni 51
#define BanerPin 52

// displej
#define CLK 12
#define DIO 13

// brzina
const int brzina = 1200;
const int brzina_sprat = 3600;
// ubrzanje
const int ubrzanje = 200;
const int ubrzanje_sprat = 1200;
// promenljive
bool banerBool = false;
bool pumpaBool = false;
bool rukiceBool = false;
int bodovi = 0;

//Servo motori
Servo baner, rukica_levo, rukica_desno;
//Step motori
AccelStepper prednji(AccelStepper::DRIVER, stepPrednji, dirPrednji);
AccelStepper desni(AccelStepper::DRIVER, stepDesni, dirDesni);
AccelStepper levi(AccelStepper::DRIVER, stepLevi, dirLevi);
AccelStepper zadnji(AccelStepper::DRIVER, stepZadnji, dirZadnji);
AccelStepper sprat(AccelStepper::DRIVER, stepSprat, dirSprat);

TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
    Serial.begin(38400);
		
		pinMode(PumpaRelejPin, OUTPUT);
		pinMode(EMRelejPin, OUTPUT);

    prednji.setMaxSpeed(brzina);
    desni.setMaxSpeed(brzina);
    levi.setMaxSpeed(brzina);
    zadnji.setMaxSpeed(brzina);
    sprat.setMaxSpeed(brzina_sprat);

		prednji.setAcceleration(ubrzanje);
    desni.setAcceleration(ubrzanje);
    levi.setAcceleration(ubrzanje);
    zadnji.setAcceleration(ubrzanje);
    sprat.setAcceleration(ubrzanje_sprat);

		UpaliMotore();

		baner.attach(BanerPin);
    baner.write(90);
		rukica_levo.attach(ServoLevi);
		rukica_levo.write(30);
		rukica_desno.attach(ServoDesni);
		rukica_desno.write(150);
    
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
		UpaliMotore();
    napred(brzina);
  }
  else if(c == 15){
		UpaliMotore();
    nazad(brzina);
  }
  else if(c == 16){
		UpaliMotore();
    levo(brzina);
  }
  else if(c == 17){
		UpaliMotore();
    desno(brzina);
  }
	
	else if (c == 18){
		UgasiMotore();
		gore(brzina_sprat);
	}
	else if (c == 19){
		UgasiMotore();
		dole(brzina_sprat);
	}
	else if (c == 20){
		UpaliMotore();
		rlevo();
	}
	else if (c == 21){
		UpaliMotore();
		rdesno();
	}

  else if(c == 11){
		UgasiMotore();
    banerFja();
  }
	else if(c == 12){
		UgasiMotore();
		pumpaFja();
	}
	else if (c == 13){
		UgasiMotore();
		rukiceFja();
	}
  else if(c < 10){
		UgasiMotore();
    dodajBroj(c);
  }

	else {
		UgasiMotore();
		Stani();
	}

	prednji.run();
	zadnji.run();
	levi.run();
	desni.run();
	sprat.run();
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

void pumpaFja(){
  if(!pumpaBool){
    digitalWrite(PumpaRelejPin, HIGH);
		digitalWrite(EMRelejPin, HIGH);
  }
  else{
    digitalWrite(PumpaRelejPin, LOW);
		digitalWrite(EMRelejPin, LOW);
  }
  pumpaBool = !pumpaBool;
}

void rukiceFja(){
	if(!rukiceBool){
		rukica_levo.write(120);
		rukica_desno.write(60);
	}
	else {
		rukica_levo.write(30);
		rukica_desno.write(150);
	}
	rukiceBool = !rukiceBool;
}

void dole(float brzina) {
	if (sprat.speed() == 0) sprat.moveTo(-1e6);
}

void gore(float brzina) {
	if (sprat.speed() == 0) sprat.moveTo(1e6);
}

void napred(float brzina) {
	if (desni.speed() == 0) desni.moveTo(1e6);
	if (levi.speed() == 0) levi.moveTo(-1e6);
}

void nazad(float brzina){
	if (desni.speed() == 0) desni.moveTo(-1e6);
	if (levi.speed() == 0) levi.moveTo(1e6);
}

void levo(float brzina){
	if (prednji.speed() == 0) prednji.moveTo(1e6);
	if (zadnji.speed() == 0) zadnji.moveTo(-1e6);
}

void desno(float brzina){
	if (prednji.speed() == 0) prednji.moveTo(-1e6);
	if (zadnji.speed() == 0) zadnji.moveTo(1e6);
}

void rdesno(){
	if (prednji.speed() == 0) prednji.moveTo(-1e6);
	if (zadnji.speed() == 0) zadnji.moveTo(-1e6);
	if (desni.speed() == 0) desni.moveTo(-1e6);
	if (levi.speed() == 0) levi.moveTo(-1e6);
}

void rlevo(){
	if (prednji.speed() == 0) prednji.moveTo(1e6);
	if (zadnji.speed() == 0) zadnji.moveTo(1e6);
	if (desni.speed() == 0) desni.moveTo(1e6);
	if (levi.speed() == 0) levi.moveTo(1e6);
}

void Stani(){
	prednji.setCurrentPosition(0);
	prednji.setSpeed(0);
	prednji.runToPosition();
	
	zadnji.setCurrentPosition(0);
	zadnji.setSpeed(0);
	zadnji.runToPosition();
	
	levi.setCurrentPosition(0);
	levi.setSpeed(0);
	levi.runToPosition();
	
	desni.setCurrentPosition(0);
	desni.setSpeed(0);
	desni.runToPosition();

	sprat.setCurrentPosition(0);
	sprat.setSpeed(0);
	sprat.runToPosition();
}

void dodajBroj(int c){
  bodovi *= 10;
  bodovi += c;
  bodovi %= 1000;
  display.showNumberDec(bodovi, true);
}

void UpaliMotore(){	
    digitalWrite(enPrednji, LOW);
    digitalWrite(enZadnji, LOW);
    digitalWrite(enLevi, LOW);
    digitalWrite(enDesni, LOW);
}

void UgasiMotore(){	
    digitalWrite(enPrednji, HIGH);
    digitalWrite(enZadnji, HIGH);
    digitalWrite(enLevi, HIGH);
    digitalWrite(enDesni, HIGH);
}
