#include <TM1637Display.h>

#define CLK 3
#define DIO 2
#define PBS 4
#define PBP 5
#define PBT 6

const uint8_t allON[] = { 0xff, 0xff, 0xff, 0xff };

unsigned long prev_mill;
int min, second;
int counter = 0000;
int interval = 1000;
int state;
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(PBS, INPUT_PULLUP);
  pinMode(PBP, INPUT_PULLUP);
  pinMode(PBT, INPUT_PULLUP);
  display.setBrightness(5);
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDecEx(checksgs,0b01000000);
    delay(100);
  }
  display.showNumberDec(allON);
  delay(1000);
  display.clear();
}

void loop() {
  if (digitalRead(PBS) == HIGH) {
    Serial.println("START");
    state = 1;
  }
  if (digitalRead(PBT) == HIGH) {
    Serial.println("STOP TRIG");
    if (state == 0) {
      counter = 0;
      min = 0;
      prev_mill = 0;
      counter = 0000;
      display.showNumberDecEx(0000, 0b01000000, true, 4, 0);
    }
  }
  if (state == 1) {
    if (digitalRead(PBP) == HIGH) {
      Serial.println("Pause Trig");
      state = 0;
    }
    unsigned long currentMillis = millis();
    if (currentMillis - prev_mill >= interval) {
      // Serial.println("MILLIS POLL");
      prev_mill = currentMillis;
      counter++;
      if (counter == 60) {
        counter = 0;
        min++;
      }
      showDisplay(counter);
    }
  }
}
void showDisplay(int value) {
  // Serial.println(value/60);
  display.showNumberDecEx(min, 0b01000000, true, 2, 0);
  display.showNumberDec(value, true, 2, 2);
  
}
