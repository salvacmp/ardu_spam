int merah = 4;
int potval;
int potconvert;

void setup() {
  // put your setup code here, to run once:
  pinMode(merah, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potval = analogRead(A1);

  Serial.println(potval);

  potconvert = map(potval, 0, 1023, 0, 255);
  analogWrite(merah, potconvert);
}
