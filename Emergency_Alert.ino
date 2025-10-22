#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define DHTPIN 4       
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);


#define BUZZER 5

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Emergency Exit");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temp);

  if (temp > 26.0) {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GO THIS WAY");

    
    for (int i = 0; i < 16; i++) {
      lcd.setCursor(i, 1);
      lcd.print(">");
      tone(BUZZER, 1000);  
      delay(100);
      lcd.setCursor(i, 1);
      lcd.print(" ");
      noTone(BUZZER);
    }
  } else {
   
    noTone(BUZZER);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("SAFE CONDITION");
    delay(2000);
  }
}
