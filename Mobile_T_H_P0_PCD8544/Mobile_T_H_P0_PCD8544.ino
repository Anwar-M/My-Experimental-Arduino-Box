#include "PCD8544_SPI.h"
#include <SFE_BMP180.h>

PCD8544_SPI lcd;
SFE_BMP180 bmp180;
#include "ClosedCube_HDC1080.h"
ClosedCube_HDC1080 hdc1080;

char status;
double T, P;

void setup() {
  lcd.begin(false, 0xB5, 0x04, 0x13);
  lcd.print(F("Anwar's       measurement   box v1"));

  delay(2000);
  lcd.clear();
  
  if (!bmp180.begin()) {
    lcd.print(F("BMP180 sensor fail!"));
    while (1) delay(1);
  }
  else {
    lcd.print(F("BMP180 sensor O.K.!"));
  }
  hdc1080.begin(0x40);
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  status = bmp180.startTemperature();
  delay(status);
  bmp180.getTemperature(T);
  status = bmp180.startPressure(3);
  delay(status);
  status = bmp180.getPressure(P,T);

  lcd.print("T= ");
  lcd.print(T);
  lcd.print(" C");
  lcd.gotoXY(0,1);
  lcd.print("p");
  lcd.print("= ");
  lcd.print(P/10, 3);
  lcd.print(" kPa");

  lcd.gotoXY(0,3);
  lcd.print("T= ");
  lcd.print(hdc1080.readTemperature());
  lcd.print(" C");
  lcd.gotoXY(0,4);
  lcd.print("RH= ");
  lcd.print(hdc1080.readHumidity());
  lcd.print("%");
  delay(1000);
  
  lcd.clear();
}
