void initialize() {
  displayA.setBrightness(5);
  displayA.clear();

  displayB.setBrightness(5);
  displayB.clear();

  displayC.setBrightness(5);
  displayC.clear();
  int checksgs = 0000;
  for (checksgs; checksgs <= 9999; checksgs += 1111) {
    displayA.showNumberDec(checksgs);
    displayB.showNumberDec(checksgs);
    displayC.showNumberDec(checksgs);
    delay(100);
  }
  displayA.showNumberDec(0000, true);
  displayB.showNumberDec(0000, true);
  displayC.showNumberDec(0000, true);
  cycleInit();
  allRed();
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
