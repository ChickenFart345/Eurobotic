#include "Keypad.h"
#include <string.h>

#define X1 A0
#define Y1 A1
#define X2 A2
#define Y2 A3
#define B1 3
#define B2 4

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
 {{'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
byte rowPins[ROWS] = {
  5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  9, 10, 11, 12}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

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
    char key = keypad.getKey();
    
    int ans;
    if (key == NO_KEY) ans = -1;
    else if (key >= '0' && key <= '9') ans = key - '0';
    else ans = -2;

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
    Serial.print(b2);
    Serial.print(',');
    Serial.println(ans);
    ready = false;
  }
}
