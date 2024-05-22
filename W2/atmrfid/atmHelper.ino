void enterPin() {
  if (time == 0) {
    resetState();
    // setLamp(1, 0, 0);
    // lcd.clear();
    // lcd.print("Timeout...");
    // delay(1000);
    // lcd.clear();
    // showStart();
    // lockState = 0;
    // menu = 0;
  }
  char key = keypad.getKey();
  if (time > 0) {
    lcd.setCursor(0, 0);
    lcd.print("Masukan PIN:");
    if (key >= '0' && key <= '9' && input.length() <= 4) {
      input += key;
    }
    if (key == 'B') {
      input.remove(input.length() - 1);
      lcd.clear();
    }
    cth();
    lcd.setCursor(0, 1);
    lcd.print(input);
    if (key == '#') {
      if (input.toInt() == PIN && input.length() >= 4) {
        setLamp(0, 0, 1);
        logged_in = 1;
        time = -1;
        lockState = 0;
        menu = 0;
        display.showNumberDec(0);
        showMenu();
      } else {
        setLamp(1, 0, 0);
        lcd.clear();
        lcd.print("Wrong PIN");
        delay(1000);
        setLamp(0, 1, 0);
      }
    }
  }
}
void cekSaldo() {
  setLamp(0, 1, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mengecek Saldo...");
  lcd.blink();
  delay(3000);
  lockState = 1;
  lcd.clear();
  while (lockState == 1) {
    setLamp(0, 0, 1);
    char key = keypad.getKey();
    lcd.setCursor(0, 0);
    lcd.print("Saldo Anda:");
    lcd.setCursor(0, 1);
    lcd.print(SALDO);
    if (key == '#') {
      lcd.noBlink();
      showMenu();
      lockState = 0;
      menu = 0;
    }
  }
}

void resetState() {
  mfrc522.PCD_Init();
  lcd.clear();
  display.clear();
  showStart();
  setLamp(1, 0, 0);
  time = 0;
  lockState = 0;
  second = 0;
  min = 0;
  input = "";
  timeout = 0;
  logged_in = 0;
  menuCycle = 0;
  keyTagged = 0;
  tagID = "";
  menu = 0;
  for (uint8_t i = 0; i < mfrc522.uid.size; i++) {
    mfrc522.uid.uidByte[i] = 0;
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
  }

}