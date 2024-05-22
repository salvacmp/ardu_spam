void cth() {
  setLamp(0, 1, 0);
  int curr = millis();
  if (curr - prev_mill >= 1000) {
    prev_mill = curr;
    time--;
    display.showNumberDec(time);
  }
}