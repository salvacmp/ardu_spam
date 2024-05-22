#include <LiquidCrystal.h>
#include <Keypad.h>
#include <TM1637Display.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 48
#define SS_PIN 53
#define R 30
#define Y 31
#define G 32

#define CLK 3
#define DIO 4

int PIN;
int SALDO;

char global_data[] = "{\"A9151\": {\"saldo\": 50000,\"pin\": 2233},\"40EECF11\": {\"saldo\": 20000, \"pin\": 2323}}";

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
bool keyTagged = 0;
String tagID;
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
MFRC522 mfrc522(SS_PIN, RST_PIN);
StaticJsonDocument<96> doc;
DeserializationError error = deserializeJson(doc, global_data);
JsonObject object = doc.as<JsonObject>();

// void(*resetState) (void) = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  keypad.addEventListener(keypadEvent);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  SPI.begin();
  mfrc522.PCD_Init();
  initialize();
  if (error) {
    Serial.println("Err Parse");
    return;
  }
}

void loop() {
  while (keyTagged == 0) {
    keyTagged = readKey();
  }
  if (keyTagged == 1) menu = 1;
  keypad.getKey();
  if (logged_in == 1) showMenu();
  if (menu == 1 && logged_in == 0) {
    Serial.println(PIN);
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
    if (key == 'B' && logged_in == 1) {
      menu = 3;
    }
    if(key == 'D'){
      resetState();
    }
  }
}