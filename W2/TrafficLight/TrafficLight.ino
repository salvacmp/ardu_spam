#include <TM1637Display.h>

#define A_RED 23
#define A_YELLOW 25
#define A_GREEN 27

#define B_RED 29
#define B_YELLOW 31
#define B_GREEN 33

#define C_RED 35
#define C_YELLOW 37
#define C_GREEN 39

#define INTR_PB 18

#define CLK 3
#define DIO 2

const uint8_t groupA[] = {
  SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,  // char G
  SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_G   //char A
};

const uint8_t groupB[] = {
  SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,         // char G
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G  //char B
};
const uint8_t groupC[] = {
  SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,  // char G
  SEG_A | SEG_F | SEG_E | SEG_D                   //char C
};

unsigned long prev_mill;
int interval = 1000;
int cycleStep = 5;
int counter;
int cycleGroup;
int setGroup;
int enableCycle;
bool goCount = true;
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(A_RED, OUTPUT);
  pinMode(A_YELLOW, OUTPUT);
  pinMode(A_GREEN, OUTPUT);

  pinMode(B_RED, OUTPUT);
  pinMode(B_YELLOW, OUTPUT);
  pinMode(B_GREEN, OUTPUT);

  pinMode(C_RED, OUTPUT);
  pinMode(C_YELLOW, OUTPUT);
  pinMode(C_GREEN, OUTPUT);
  pinMode(INTR_PB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTR_PB), TrafficInterrupt, FALLING);
  display.setBrightness(5);
  display.clear();
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDec(checksgs);
    delay(250);
  }
  display.showNumberDec(0000);
  cycleInit();
  allRed();
}

void loop() {
  unsigned long currentMillis = millis();

  if (cycleGroup > 3) cycleGroup = 1;
  if (counter == cycleStep) {
    counter = 0;
    cycleGroup += 1;
    enableCycle = 1;
  }
  if (cycleGroup == 1 && enableCycle == 1) {
    trafficGA();
    enableCycle = 0;
  }
  if (cycleGroup == 2 && enableCycle == 1) {
    shutdownGA();
    trafficGB();
    enableCycle = 0;
  }
  if (cycleGroup == 3 && enableCycle == 1) {
    trafficGC();
    enableCycle = 0;
  }
    if (currentMillis - prev_mill >= interval && goCount == true) {
      // Serial.println("MILLIS POLL");
      Serial.println(counter);
      prev_mill = currentMillis;
      counter++;
      display.showNumberDec(counter, true, 2, 2);
    }
}
void cycleInit() {
  setLampGA(0, 0, 0);
  setLampGB(0, 0, 0);
  setLampGC(0, 0, 0);
  delay(100);
  setLampGA(1, 0, 0);
  setLampGB(1, 0, 0);
  setLampGC(1, 0, 0);
  delay(100);
  setLampGA(1, 1, 0);
  setLampGB(1, 1, 0);
  setLampGC(1, 1, 0);
  delay(100);
  setLampGA(1, 1, 1);
  setLampGB(1, 1, 1);
  setLampGC(1, 1, 1);
  delay(100);
  setLampGA(1, 1, 1);
  setLampGB(1, 1, 1);
  setLampGC(1, 1, 1);
  delay(100);
  setLampGA(1, 1, 0);
  setLampGB(1, 1, 0);
  setLampGC(1, 1, 0);
  delay(100);
  setLampGA(1, 0, 0);
  setLampGB(1, 0, 0);
  setLampGC(1, 0, 0);
  delay(100);
  setLampGA(0, 0, 0);
  setLampGB(0, 0, 0);
  setLampGC(0, 0, 0);
  delay(100);
  setLampGA(1, 1, 1);
  setLampGB(1, 1, 1);
  setLampGC(1, 1, 1);
  delay(500);
  setLampGA(0, 0, 0);
  setLampGB(0, 0, 0);
  setLampGC(0, 0, 0);
  delay(500);
}
void setLampGA(int r, int y, int g) {
  digitalWrite(A_RED, r);
  digitalWrite(A_YELLOW, y);
  digitalWrite(A_GREEN, g);
}
void setLampGB(int r, int y, int g) {
  digitalWrite(B_RED, r);
  digitalWrite(B_YELLOW, y);
  digitalWrite(B_GREEN, g);
}
void setLampGC(int r, int y, int g) {
  digitalWrite(C_RED, r);
  digitalWrite(C_YELLOW, y);
  digitalWrite(C_GREEN, g);
}
void allRed() {
  setLampGA(1, 0, 0);
  setLampGB(1, 0, 0);
  setLampGC(1, 0, 0);
}
void trafficGA() {
  setLampGB(1, 0, 0);
  setLampGC(1, 0, 0);
  setLampGA(0, 1, 0);
  delay(3000);
  setLampGA(0, 0, 1);
}
void trafficGB() {
  setLampGA(1, 0, 0);
  setLampGC(1, 0, 0);
  setLampGB(0, 1, 0);
  delay(3000);
  setLampGB(0, 0, 1);
}
void trafficGC() {
  setLampGB(1, 0, 0);
  setLampGA(1, 0, 0);
  setLampGC(0, 1, 0);
  delay(3000);
  setLampGC(0, 0, 1);
}
void shutdownGA() {
  setLampGA(0, 1, 0);
  delay(3000);
  setLampGB(1, 0, 0);
}
void TrafficInterrupt() {
  goCount = false;
  display.showNumberDec(0000, true, 4, 0);
  setLampGA(1, 0, 0);
  setLampGB(1, 0, 0);
  setLampGC(1, 0, 0);
  delay(5000);
  goCount = true;
}