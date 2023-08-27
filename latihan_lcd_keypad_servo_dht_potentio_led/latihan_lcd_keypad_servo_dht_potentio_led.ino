#include <LiquidCrystal.h>
#include <DHT.h>
#include <Keypad.h>
#include <Servo.h>
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
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};
const uint8_t humid[] = {
  SEG_B | SEG_C | SEG_G | SEG_E | SEG_F,
  SEG_E | SEG_D | SEG_C
};

byte rowPins[ROWS] = { 44, 42, 40, 38 };
byte colPins[COLS] = { 36, 34, 32, 30 };
const uint8_t allON[] = { 0xff, 0xff, 0xff, 0xff };
const uint8_t allOFF[] = { 0x00, 0x00, 0x00, 0x00 };

float humi, temp;
int menu = 100;
int pos = 90;
int y;
int selected = 1;
int tempsg = 00;
int cycle_display = 0;
String input;

LiquidCrystal lcd(6, 7, 9, 10, 11, 12);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
DHT dht(DHT_PIN, DHT_TYPE);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo servo;
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  customKeypad.addEventListener(keypadEvent);
  Serial.begin(9600);
  servo.attach(5);
  servo.write(0);
  pinMode(MERAH, OUTPUT);
  pinMode(KUNING, OUTPUT);
  pinMode(HIJAU, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  display.setBrightness(5);
  display.setSegments(allON);
  delay(2000);
  display.clear();
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDec(checksgs);
    delay(250);
  }
  MsTimer2::set(5000, cycleTemp);
  MsTimer2::start();
}
void cycleTemp() {
  cycle_display = !cycle_display;
  Serial.println(cycle_display);
  if (cycle_display == 0) {
    temp = dht.readTemperature();
    tempsg = dht.readTemperature();
    display.showNumberDec(tempsg, false, 2, 0);
    display.setSegments(celsius, 2, 2);
  } else if (cycle_display == 1) {
    humi = dht.readHumidity();
    tempsg = dht.readHumidity();
    display.showNumberDec(tempsg, false, 2, 0);
    display.setSegments(humid, 2, 2);
  }
}
void loop() {

  char key = customKeypad.getKey();
  if (menu == 100) {
    lcd.setCursor(0, 0);
    lcd.print("Welcome...");
    lcd.blink();
    for (int y = 0; y < 3; y++) {
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(BUZZER, LOW);
      delay(500);
    }
    lcd.noBlink();
    lcd.clear();
    menu = 0;
  }

  if (menu == 0) {
    lcd.setCursor(0, 0);
    lcd.print("1: LED");
    lcd.setCursor(8, 0);
    lcd.print("2: POT");
    lcd.setCursor(0, 1);
    lcd.print("3: TEMP");
    lcd.setCursor(8, 1);
    lcd.print("4: SRV");
    delay(500);
    lcd.clear();
  }
  if (menu == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED Blink");
    for (y = 0; y < 3; y++) {
      Serial.println(y);
      digitalWrite(MERAH, HIGH);
      digitalWrite(KUNING, LOW);
      digitalWrite(HIJAU, LOW);
      delay(100);
      digitalWrite(MERAH, HIGH);
      digitalWrite(KUNING, HIGH);
      digitalWrite(HIJAU, LOW);
      delay(100);
      digitalWrite(MERAH, HIGH);
      digitalWrite(KUNING, HIGH);
      digitalWrite(HIJAU, HIGH);
      delay(100);
      digitalWrite(MERAH, LOW);
      digitalWrite(KUNING, HIGH);
      digitalWrite(HIJAU, HIGH);
      delay(100);
      digitalWrite(MERAH, LOW);
      digitalWrite(KUNING, LOW);
      digitalWrite(HIJAU, HIGH);
      delay(100);
      digitalWrite(MERAH, LOW);
      digitalWrite(KUNING, LOW);
      digitalWrite(HIJAU, LOW);
      delay(100);
      if (y == 2) {
        Serial.println("LOOP END");
        menu = 0;
        break;
      }
    }
  }
  if (menu == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nilai Potentio");
    lcd.setCursor(0, 1);
    int potval = analogRead(POTENTIO);
    lcd.print(potval);
    Serial.println(potval);
    delay(100);
  }
  if (menu == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Humid : " + String(humi));
    lcd.setCursor(0, 1);
    lcd.print("Temp  : " + String(temp));
    // lcd.noBlink();
    delay(500);
    lcd.clear();
  }
  if (menu == 4) {
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
    Serial.println(key);
    switch (key) {
      case '1':
        menu = 1;
        break;
      case '2':
        menu = 2;
        break;
      case '3':
        menu = 3;
        break;
      case '4':
        menu = 4;
        break;
      case '*':
        menu = 0;
        break;
    }
  }
}
