#include <TM1637Display.h>
// #include "initProg.h"

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

#define CLK_A 3
#define DIO_A 2

#define CLK_B 9
#define DIO_B 8

#define CLK_C 7
#define DIO_C 6

unsigned long prev_mill;
int interval = 1000;
int cycle = 10;
int y_interval = 3;
int g_interval = 4;
int global_time;

int holdA;
int holdB;
int holdC;

int counterA = cycle;
int counterB = cycle;
int counterC = cycle;
int counterH;

int global_lock = 1;
int a_lock = 1;
int b_lock;
int c_lock;

int statusA;
int statusB;
int statusC;

int g_lock;

TM1637Display displayA = TM1637Display(CLK_A, DIO_A);
TM1637Display displayB = TM1637Display(CLK_B, DIO_B);
TM1637Display displayC = TM1637Display(CLK_C, DIO_C);

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

  initialize();
}

void loop() {
  while (global_lock == 0) {
    displayA.showNumberDec(counterH, true, 4, 0);
    displayB.showNumberDec(counterH, true, 4, 0);
    displayC.showNumberDec(counterH, true, 4, 0);
    setLampGA(1, 0, 0);
    setLampGB(1, 0, 0);   
    setLampGC(1, 0, 0);

    delay(1000);
    if (counterH == 5) {
      displayA.showNumberDec(0000, true);
      displayB.showNumberDec(0000, true);
      displayC.showNumberDec(0000, true);
      global_lock = 1;
    }
    counterH++;
  }
  if (global_lock == 1) {
    global_time = millis();
    if (a_lock == 1) countA();
    if (b_lock == 1) countB();
    if (c_lock == 1) countC();
  }
}
void TrafficInterrupt() {
  global_lock = 0;
}
