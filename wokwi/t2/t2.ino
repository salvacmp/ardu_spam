#include <Keypad.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <TM1637Display.h>
#include <Ultrasonic.h>

#define DHT_PIN 5
#define TRIG 23
#define ECHO 25
#define CLK 11
#define DIO 10

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {52, 50, 48, 46}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {53, 51, 49, 47}; //connect to the column pinouts of the keypad

int temp,humi;
int distance;
int menu;
int hold;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(13,12,9,8,7,6);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
DHT dht(DHT_PIN, DHT22);
TM1637Display display = TM1637Display(CLK, DIO);
Ultrasonic ultrasonic(TRIG,ECHO);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  display.setBrightness(5);
  keypad.addEventListener(keypadEvent);

}

void loop() {
  char key = keypad.getKey();
  distance = ultrasonic.read();

  // display.showNumberDec(distance);
  if(menu == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Halo Dunia!");
    lcd.setCursor(0,1);
    lcd.print("Saya Wenz");
    delay(100);
  }
  if(menu == 1){
    humi = dht.readHumidity();
    temp = dht.readTemperature();

    display.clear();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kelembaban");
    lcd.setCursor(0,1);
    lcd.print(humi);
    display.showNumberDec(temp);
    delay(100);
  }
  if(menu == 2){
    lcd.clear();
    lcd.print("Halo Servo!");
    for(hold; hold<=2; hold++){
      display.showNumberDec(hold);
      delay(1000);
    }
    delay(1000);
    
  }

}

void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == PRESSED || keypad.getState() == HOLD) {
    Serial.println(key);
    switch (key) {
      case '1':
        menu = 1;
        break;
      case '2':
        menu = 2;
        break;
      case '3':
        menu = 3;
        break;
      case '4':
        menu = 4;
        break;
      case '*':
        menu = 0;
        break;
    }
  }
}
