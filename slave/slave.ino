#include <String.h>
#include <TM1637Display.h>
#include <Servo.h>

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
#define servo_rukica_levo 32
#define servo_rukica_desno 33
#define servo_grab_grab_levo 34
#define servo_grab_grab_desno 35
#define servo_vakuum 36
#define servo_baner 37

// elektromagneti
#define elektromagnet_levo 38
#define elektromagnet_desno 39

// score screen
#define CLK 3
#define DIO 4

// promenljive za bluetooth
int x1, y1, x2, y2, b1, b2, cifra;
String receivedData = "";
bool connected = false;

// promenljive za kretanje
const int t = 900;
const int speed = 2;
int stanje = 0;

// promenljiva za score
int score = 0;

// promenljive za servo motore rukica
const int ugao_rotacija_rukica_levo = 0;
const int ugao_pocetak_rotacija_rukica_levo = 90;
const int ugao_pocetak_igre_rukica_levo = 180;
const int ugao_rotacija_rukica_desno = 180;
const int ugao_pocetak_rotacija_rukica_desno = 90;
const int ugao_pocetak_igre_rukica_desno = 0;

// promenljive za servo motore grab_grab
const int ugao_pocetak_hvatanja = 0;                                // treba testiranje
const int ugao_hvatanja = ugao_pocetak_hvatanja + 0;                // treba testiranje


// promenljive za servo motora vakuum pumpe
const int ugao_dizanja_daske = 0;                                   // treba testiranje
const int ugao_spustanja_daske = 0;                                 // treba testiranje

// promenljive za servo motora banera
const int ugao_pocetak_baner = 0;                                   // treba testiranje
const int ugao_baner = ugao_pocetak_baner + 0;                      // treba testiranje

// promenljiva za podizanje sprata
const int sprat = 800;                                              // treba testiranje

// promenljive za neblokirajuci kod
unsigned long long pocetak, temp;

// 4-digit 7-segment display
TM1637Display display = TM1637Display(CLK, DIO);

// servo motori
Servo rukica_levo, rukica_desno, grab_grab_levo, grab_grab_desno, vakuum, baner;

void setup() {
  // bluetooth komunikacija
  Serial.begin(38400);

  // pinovi za steppere
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

  // servo motori
  rukica_levo.attach(servo_rukica_levo);
  rukica_desno.attach(servo_rukica_desno);
  grab_grab_levo.attach(servo_grab_grab_levo);
  grab_grab_desno.attach(servo_grab_grab_desno);
  vakuum.attach(servo_vakuum);
  baner.attach(servo_baner);

  // pinovi za elektromagnete
  pinMode(elektromagnet_levo, OUTPUT);
  pinMode(elektromagnet_desno, OUTPUT);

  // 4-digit 7-segment display
  display.setBrightness(5);
  display.showNumberDec(score, true);
  
  // postavljanje steppera na nulu
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

  // postavljanje servo motora na nulu
  rukica_levo.write(ugao_pocetak_rotacija_rukica_levo);
  rukica_desno.write(ugao_pocetak_rotacija_rukica_desno);
  grab_grab_levo.write(ugao_pocetak_hvatanja);
  grab_grab_desno.write(ugao_pocetak_hvatanja);
  vakuum.write(ugao_dizanja_daske);
  baner.write(ugao_pocetak_baner);

  // pocetak bluetooth komunikacije
  Serial.println('r');
}

void loop() {
  while (Serial.available()) {
    connected = true;
    char c = Serial.read();
    if (c == '\n') {
      parseData(receivedData);
      pocetak = millis();
      receivedData = "";
      Serial.println('r');
    } 
    else receivedData += c;
  }

  stanje = CalculateState();

  if (stanje == 1) { // napred
    Dir1(2);
    Dir0(3);
    Step(2);
    Step(3);
  }
  if (stanje == 2) { // nazad
    Dir0(2);
    Dir1(3);
    Step(2);
    Step(3);
  }
  if (stanje == 3) { // levo
    Dir0(1);
    Dir1(4);
    Step(1);
    Step(4);
  }
  if (stanje == 4) { // desno
    Dir1(1);
    Dir0(4);
    Step(1);
    Step(4);
  }
  if (stanje == 5) { // pivot levo
    Dir0(1);
    Dir0(2);
    Dir0(3);
    Dir0(4);
    Step(1);
    Step(2);
    Step(3);
    Step(4);
  }
  if (stanje == 6) { // pivot desno
    Dir1(1);
    Dir1(2);
    Dir1(3);
    Dir1(4);
    Step(1);
    Step(2);
    Step(3);
    Step(4);
  }
  if (stanje == 7) { // sprat
    // fiksiranje konzervi za rukice
    digitalWrite(elektromagnet_levo, HIGH);
    digitalWrite(elektromagnet_desno, HIGH);

    // fiksiranje konzervi za grab_grab
    grab_grab_levo.write(ugao_hvatanja);
    grab_grab_desno.write(ugao_hvatanja);

    // okretanje rukica
    rukica_levo.write(ugao_rotacija_rukica_levo);
    rukica_desno.write(ugao_rotacija_rukica_desno);

    // uzimanje daske vakuumom
          // ovde treba da stoji kod za vakuum pumpu
    vakuum.write(ugao_dizanja_daske);

    // podizanje sprata
    for (int temp = 0; temp < sprat; temp++) OneStep(5);

    // vracanje rukica
    rukica_levo.write(ugao_pocetak_rotacija_rukica_levo);
    rukica_desno.write(ugao_pocetak_rotacija_rukica_desno);

    // spustanje daske
    vakuum.write(ugao_spustanja_daske);
          // ovde treba da stoji kod za vakuum pumpu
  }
  if (stanje == 8) { // baner
    // treba iskucati kod ali to tek kad se ljudi dogovore kako cemo raditi
  }
  

  // ukucavanje score-a
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
  if (!connected) return 0;

  // u slucaju da su pinovi od joystick-a okrenuti na gore
  if (x1 < 150) return 1; // napred
  if (x1 > 873) return 2; // nazad
  if (y1 < 150) return 3; // levo
  if (y1 > 873) return 4; // desno
  if (y2 < 150) return 5; // pivot levo
  if (y2 > 873) return 6; // pivot desno
  if (b1 == 1) return 7;  // sprat
  if (b2 == 1) return 8;  // baner  
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
  temp = millis();

  if (temp - pocetak < t) {
    if (i == 1) digitalWrite(step1, HIGH);
    if (i == 2) digitalWrite(step2, HIGH);
    if (i == 3) digitalWrite(step3, HIGH);
    if (i == 4) digitalWrite(step4, HIGH);
    if (i == 5) digitalWrite(step5, HIGH);
  }
  else if (temp - pocetak < 2 * t) {
    if (i == 1) digitalWrite(step1, LOW);
    if (i == 2) digitalWrite(step2, LOW);
    if (i == 3) digitalWrite(step3, LOW);
    if (i == 4) digitalWrite(step4, LOW);
    if (i == 5) digitalWrite(step5, LOW);
  }
}

void Step(int i){
  for (int j = 0; j < speed; j++) OneStep(i);
}
