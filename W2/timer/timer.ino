#include <Keypad.h>
#include <TM1637Display.h>

#define CLK 3
#define DIO 2
#define PBS 4
#define PBP 5
#define PBT 6
#define BUZZER 7

const uint8_t allON[] = { 0xff, 0xff, 0xff, 0xff };

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 23, 25, 27, 29 };
byte colPins[COLS] = { 31, 33, 35, 37 };

unsigned long prev_mill;
int min, second, secs;
String input;
int interval = 1000;
int state;
int inputState;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(PBS, INPUT_PULLUP);
  pinMode(PBP, INPUT_PULLUP);
  pinMode(PBT, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  customKeypad.addEventListener(keypadEvent);
  Serial.println("Timer INIT...");
  display.setBrightness(5);
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDecEx(checksgs, 0b01000000);
    delay(100);
  }
  display.showNumberDec(allON);
  delay(1000);
  display.clear();
}

void loop() {
  customKeypad.getKey();
  if (digitalRead(PBS) == HIGH) {
    Serial.println("START");
    state = 1;
  }
  if (digitalRead(PBT) == HIGH) {
    Serial.println("STOP TRIG");
    if (state == 0) {
      input = "";
      secs = 0;
      min = 0;
      prev_mill = 0;
      display.showNumberDecEx(0000, 0b01000000, true, 4, 0);
    }
  }
  while (inputState == 1) {
    Serial.println("Input Time...");
    char key = customKeypad.getKey();
    if (key >= '0' && key <= '9' && input.length() <= 4) {
      input += key;
      display.showNumberDec(input.toInt());
    }
    if (key == '#') {
      Serial.println("Exit Input...");
      secs = input.toInt();
      showDisplay(secs);
      inputState = 0;
    }
  }
  if (state == 1) {
    if (digitalRead(PBP) == HIGH) {
      Serial.println("Pause Trig");
      state = 0;
    }
    unsigned long currentMillis = millis();
    if (secs == 0) {
      ringBuzzer();
      state = 0;
    }
    if (currentMillis - prev_mill >= interval) {
      // Serial.println("MILLIS POLL");
      prev_mill = currentMillis;
      secs--;
      showDisplay(secs);
    }
  }
}
void showDisplay(int value) {
  // Serial.println(value/60);
  secondsToHMS(value);
  display.showNumberDecEx(min, 0b01000000, true, 2, 0);
  display.showNumberDec(second, true, 2, 2);
}
void ringBuzzer() {
  for (int y = 0; y < 3; y++) {
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(500);
  }
}
void secondsToHMS(const uint32_t seconds) {
  uint32_t t = seconds;
  second = t % 60;
  t = (t - second) / 60;
  min = t % 60;
}
void keypadEvent(KeypadEvent key) {
  if (customKeypad.getState() == PRESSED) {
    Serial.println(key);
    if (key == '#') {
      inputState = 1;
    }
    if (key == 'A') {
      secs = 0;
      input = "";
    }
  }
}