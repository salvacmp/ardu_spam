#include <LiquidCrystal.h>
#include <DHT.h>
#include <Keypad.h>
#include <TM1637Display.h>
#include <MsTimer2.h>

#define DHT_PIN 13
#define DHT_TYPE DHT22
#define MERAH 53
#define KUNING 51
#define HIJAU 49
#define BUZZER 45
#define POTENTIO A1
#define CLK 52
#define DIO 50

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
const uint8_t allON[] = { 0xff, 0xff, 0xff, 0xff };
const uint8_t allOFF[] = { 0x00, 0x00, 0x00, 0x00 };

LiquidCrystal lcd(6, 7, 9, 10, 11, 12);
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
TM1637Display display = TM1637Display(CLK, DIO);

String pin;
int menu;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  display.setBrightness(5);
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDec(checksgs);
    delay(250);
  }
  display.showNumberDec(allON);
  delay(1000);
  display.clear();
  lcd.print("1: Masukan PIN:");
}

void loop() {
  char key = keypad.getKey();
  if(menu == 1){
    while (menu == 1){
      char keyPressed = keypad.waitForKey();
      Serial.println(keyPressed);
      if(keyPressed >= '0' && keyPressed <= '9' && pin.length() < 4){
        pin += keyPressed;
        display.showNumberDec(pin.toFloat());
      }
      if(keyPressed == 'C'){
        pin = "";
        display.clear();
      }
    }
  }

}
void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == PRESSED || keypad.getState() == HOLD) {
    switch (key) {
      case '1':
        menu = 1;
        break;
      case '*':
        menu = 0;
        break;
    }
  }
}
