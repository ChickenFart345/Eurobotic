// biblioteke
#include "Keypad.h"

// definicija pinova
#define X1 A0
#define Y1 A1
#define X2 A2
#define Y2 A3
#define B1 2
#define B2 3
#define B3 4

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
 {{'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {9, 10, 11, 12};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(38400);

  pinMode(X1, INPUT);
  pinMode(Y1, INPUT);
  pinMode(X2, INPUT);
  pinMode(Y2, INPUT);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
}

bool baner = false;
void loop(){
  int x1 = analogRead(X1);
  int y1 = analogRead(Y1);
  int x2 = analogRead(X2);
  int y2 = analogRead(Y2);
  int b1 = digitalRead(B1);
  int b2 = digitalRead(B2);
  int b3 = digitalRead(B3);
  char key = keypad.getKey();
	
	if (baner && b1 == 1) { Serial.write(11); baner = false; }
	else if (key != NO_KEY) {
  	if (key >= '0' && key <= '9') Serial.write(key - '0');
	}
	else if (b1 == 0) baner = true;
	else if (b2 == 0) Serial.write(12);
	else if (b3 == 0) Serial.write(13);

	else if (x1 < 200) Serial.write(14);
	else if (x1 > 823) Serial.write(15);
	else if (y1 < 200) Serial.write(16);
	else if (y1 > 823) Serial.write(17);
	else Serial.write(18);

}
