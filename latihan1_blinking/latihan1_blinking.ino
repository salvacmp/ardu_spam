int m = 4;
int k = 3;
int h = 2;
int pb1 = 18;
int x=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(m, OUTPUT);
  pinMode(k, OUTPUT);
  pinMode(h, OUTPUT);
  pinMode(pb1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pb1),buttonHelper, FALLING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

//  if (digitalRead(pb1))
//  {
//    (x <= 3) ? x++ : x=0; 
//    //if(x>3) x=0; 
//    
//  }
  switch (x) {
    case 0:
      digitalWrite(m, LOW);
      digitalWrite(k, LOW);
      digitalWrite(h, LOW);
      break;
    case 1:
      digitalWrite(m, HIGH);
      digitalWrite(k, LOW);
      digitalWrite(h, LOW);
      break;
    case 2:
      digitalWrite(m, LOW);
      digitalWrite(k, HIGH);
      digitalWrite(h, LOW);
      break;
    case 3:
      digitalWrite(m, LOW);
      digitalWrite(k, LOW);
      digitalWrite(h, HIGH);
      break;
  }
  delay(100);
}
void buttonHelper(){
  delay(1000);
  Serial.println("TRIG");
  (x <= 3) ? x++ : x=0;
  
}
