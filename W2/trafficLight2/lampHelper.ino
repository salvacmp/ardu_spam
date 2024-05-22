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