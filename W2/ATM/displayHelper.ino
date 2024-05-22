void showStart() {
  lcd.setCursor(0, 0);
  lcd.print("ATM");
  lcd.setCursor(0, 1);
  lcd.print("Press A to Start");
}
void showMenu() {
  int curr = millis();
  if (curr - prev_mill >= 5000) {
    prev_mill = curr;
    menuCycle = !menuCycle;
    lcd.clear();
  }
  switch (menuCycle) {
    case 0:
      
      lcd.setCursor(0, 0);
      lcd.print("A: Cek Saldo");
      lcd.setCursor(0, 1);
      lcd.print("B: Tarik Tunai");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("C: ______");
      lcd.setCursor(0, 1);
      lcd.print("D: Logout");
      break;
  }
}