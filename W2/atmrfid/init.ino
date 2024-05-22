void initialize() {
  lcd.print("ATM");
  lcd.setCursor(0, 1);
  lcd.print("Initializing..");
  lcd.blink();
  setLamp(0, 0, 0);
  delay(250);
  setLamp(1, 0, 0);
  delay(100);
  setLamp(1, 1, 0);
  delay(100);
  setLamp(1, 1, 1);
  delay(100);
  setLamp(1, 1, 0);
  delay(100);
  setLamp(1, 0, 0);
  delay(100);
  setLamp(0, 0, 0);
  delay(100);
  setLamp(1, 1, 1);
  delay(500);
  setLamp(0, 0, 0);
  delay(500);
  display.setBrightness(5);
  display.clear();
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    display.showNumberDec(checksgs);
    delay(50);
  }
  display.clear();
  setLamp(1, 0, 0);
  lcd.clear();
  lcd.noBlink();
showStart();
}