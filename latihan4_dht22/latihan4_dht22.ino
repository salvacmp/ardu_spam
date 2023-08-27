#include <DHT.h>
#define DHT_PIN  8
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);
float humi, temp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp) || humi ==0 || temp == 0) {  //jika tidak berhasil  
    return;//kembali
  }else{
  Serial.print("\nKelembaban: ");
  Serial.print(humi);
  Serial.print("\nSuhu: ");
  Serial.print(temp);
  }

  delay(1000);
}
