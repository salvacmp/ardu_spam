#include <LiquidCrystal.h>
#include <DHT.h>
#include <Keypad.h>
#define DHT_PIN 13
#define DHT_TYPE DHT22
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 44, 42, 40, 38 };
byte colPins[COLS] = { 36, 34, 32, 30 };
float humi, temp;
int menu = 0;
int pos = 90;

int selected = 1;
String input;

LiquidCrystal lcd(6, 7, 9, 10, 11, 12);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
DHT dht(DHT_PIN, DHT_TYPE);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo servo;

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  customKeypad.addEventListener(keypadEvent);
  Serial.begin(9600);
  servo.attach(5);
  servo.write(0);
}

void loop() {
  char key = customKeypad.getKey();

  if (menu == 0) {
    lcd.setCursor(0, 0);
    lcd.print("1: Temp");
    lcd.setCursor(0, 1);
    lcd.print("4: SRV");
    delay(500);
    lcd.clear();
  }

  if (menu == 1) {
    humi = dht.readHumidity();
    temp = dht.readTemperature();
    lcd.setCursor(0, 0);
    lcd.print("Humid : " + String(humi));
    lcd.setCursor(0, 1);
    lcd.print("Temp  : " + String(temp));
    // lcd.noBlink();
    delay(500);
    lcd.clear();
  }
  if (menu == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Input Servo: ");
    selected = 1;
    char key2 = customKeypad.getKey();
    while (selected) {
      char keyPressed = customKeypad.waitForKey();
      if (keyPressed) {
        if (keyPressed == '*') {
          if (input.toInt() <= 180) {
            servo.write(input.toInt());
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Input Servo: ");
            input = "";
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Input Servo: ");
            input = "";
          }
        }
        if (keyPressed == '#') {
          selected = 0;
          menu = 0;
          Serial.println("ESC");
          break;
        }
        if (keyPressed >= '0' && keyPressed <= '9') {
          input += keyPressed;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Input Servo: ");
          lcd.setCursor(0, 1);
          lcd.print(input);
        }
      }
      delay(500);
    }
  }
}
void keypadEvent(KeypadEvent key) {
  if (customKeypad.getState() == PRESSED || customKeypad.getState() == HOLD) {
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