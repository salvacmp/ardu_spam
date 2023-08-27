#include <Servo.h>
Servo servo;
int pos = 00;
void setup() {
  // put your setup code here, to run once:
  servo.attach(5);
}

void loop() {
  for (pos = 00; pos < 180; pos += 1)
  {
    servo.write(pos);  
    delay(15);
  }
  for (pos = 180; pos >= 1; pos -= 1) 
  {
    servo.write(pos);
    delay(15);
  }
}
