#include <Stepper.h>
#include <Ultrasonic.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define POTENTIO A1
#define MERAH 53
#define TRIGPIN 4
#define ECHOPIN 3


const byte ROWS = 4;
const byte COLS = 4;
int stepsPerRevolution = 48;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 44, 42, 40, 38 };
byte colPins[COLS] = { 36, 34, 32, 30 };

int menu;
int distance;

Stepper myStepper(stepsPerRevolution, 45, 43, 41, 39);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);
Ultrasonic ultrasonic(TRIGPIN, ECHOPIN);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(MERAH, OUTPUT);
  customKeypad.addEventListener(keypadEvent);
}

void loop() {
  char key = customKeypad.getKey();
  if (menu == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Welcome...");
    lcd.blink();
  }
  if (menu == 1) {
    lcd.clear();
    distance = ultrasonic.read();
    if (distance <= 10) {
      lcd.noBlink();
      lcd.print("WARNING");
      digitalWrite(MERAH, HIGH);
      delay(100);
      digitalWrite(MERAH, LOW);
      delay(100);
    } else {
      lcd.print(distance);
      digitalWrite(MERAH, HIGH);
      delay(500);
      digitalWrite(MERAH, LOW);
      delay(500);
    }
  }
  if (menu == 2) {
    lcd.clear();
    int potval = analogRead(POTENTIO);
    int motorSpeed = map(potval, 0, 1023, 0, 100);
    stepsPerRevolution = map(potval,0,1023,0,48);
    
    if (motorSpeed > 0) {
      lcd.print(motorSpeed);
      myStepper.setSpeed(motorSpeed);
      myStepper.step(stepsPerRevolution);
    }
  }
}
void keypadEvent(KeypadEvent key) {
  if (customKeypad.getState() == PRESSED || customKeypad.getState() == HOLD) {
    Serial.println(key);
    switch (key) {
      case '1':
        menu = 1;
        break;
      case '4':
        menu = 2;
        break;
      case '*':
        menu = 0;
        break;
    }
  }
}
