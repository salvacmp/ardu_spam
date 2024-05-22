#include <LiquidCrystal.h>
#include <Keypad.h>
#include <TM1637Display.h>

#define R 30
#define Y 31
#define G 32

#define CLK 3
#define DIO 4
#define PIN 235689
int menu;
int prev_mill;
int interval = 1000;
int time;
int lockState;
int second, min;
String input;
bool timeout;
bool logged_in = 0;
int menuCycle;
//lcd vars
const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

// Keypad vars
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = { 5, 27, 28, 29 };

// class init
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  keypad.addEventListener(keypadEvent);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  initialize();
}

void loop() {
  keypad.getKey();
  if(logged_in == 1) showMenu();
  if (menu == 1 && logged_in == 0) {
    Serial.println("Input PIN!");
    lcd.clear();
    lockState = 1;
    time = 30;
    while (lockState == 1) {
      enterPin();
    }
  }
  if (menu == 2 && logged_in == 1) {
    cekSaldo();
  }
}
void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == PRESSED) {
    Serial.println(key);
    if (key == 'A' && logged_in == 0) {
      menu = 1;
    }
    if (key == 'A' && logged_in == 1) {
      menu = 2;
    }
    if (key == 'B' && logged_in == 2) {
      menu = 3;
    }
  }
}