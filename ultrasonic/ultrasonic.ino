#include <Ultrasonic.h>
Ultrasonic ultrasonic(8, 9);
int distance;
int merah = 4;
int kuning = 3;
int hijau = 2;

void setup() {
  pinMode(merah, OUTPUT);
  pinMode(kuning, OUTPUT);
  pinMode(hijau, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = ultrasonic.read();
  distance = map(distance, 0, 30, 1, 3);
  Serial.println(distance);
  switch (distance) {
    case 1:
      digitalWrite(merah, HIGH);
      digitalWrite(kuning, LOW);
      digitalWrite(hijau, LOW);
      break;
    case 2:
      digitalWrite(merah, LOW);
      digitalWrite(kuning, HIGH);
      digitalWrite(hijau, LOW);
      break;
    case 3:
      digitalWrite(merah, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(hijau, HIGH);
      break;
    default:
      digitalWrite(merah, HIGH);
      digitalWrite(kuning, HIGH);
      digitalWrite(hijau, HIGH);
      break;
  }
  delay(50);
}
