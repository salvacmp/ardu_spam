#include <LiquidCrystal.h>
#include <DHT.h>
#define DHT_PIN 8
#define DHT_TYPE DHT22
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
DHT dht(DHT_PIN, DHT_TYPE);
float humi, temp;
void setup() {
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  // Serial.print("\nKelembaban: ");
  // Serial.print(humi);
  // Serial.print("\nSuhu: ");
  // Serial.print(temp);
  lcd.setCursor(0,0);
  lcd.print("Humid : "+String(humi));
  lcd.setCursor(0,1);
  lcd.print("Temp  : "+String(temp));
  delay(1000);
  // lcd.noBlink();
  lcd.clear();
}
