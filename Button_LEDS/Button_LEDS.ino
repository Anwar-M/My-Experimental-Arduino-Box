#include "PCD8544_SPI.h"

PCD8544_SPI lcd;

boolean LButton = 1;
boolean RButton = 1;
boolean YButton = 1;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW); 
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW); 
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 
  
  lcd.begin(false, 0xB5, 0x04, 0x13);
  lcd.print(F("Anwar's       experimental   box v2"));

  delay(2000);
  lcd.clear();
}

void loop() {
/*  LButton = digitalRead(3);
  RButton = digitalRead(4);
  YButton = digitalRead(2);
  
  if (!LButton) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    lcd.clear();
    lcd.print("L button is pressed niggah!");
  }
  if (!RButton) {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    lcd.clear();
    lcd.print("R button is pressed faggot!");
  }
  if (!YButton) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    lcd.clear();
    lcd.print("Y button is pressed retard!");
  }

  */
  short button_value;
  button_value = checkButtonPress();

  switch(button_value) {
    case 1:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      lcd.clear();
      lcd.print("Off you go!");
      lcd.print(button_value);
      delay(500);
      break;
    case 2:
      break;
    case 3:
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      lcd.clear();
      lcd.print("R button is pressed :(");
      lcd.print(button_value);
      break;
    case 4:
      break;
    case 5:
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      lcd.clear();
      lcd.print("L button is pressed :)!");
      lcd.print(button_value);
      break;
    case 6:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      lcd.clear();
      lcd.print("Y button is pressed :S!");
      lcd.print(button_value);
      break;
    case 7:
      break;
    case 8:
      lcd.print("exit");
      lcd.clear();
      break;
  }

  delay(5);
}

short checkButtonPress() {
  short combo = 0;
  YButton = digitalRead(2);
  LButton = digitalRead(3);
  RButton = digitalRead(4);
  combo = YButton + 2*LButton + 4*RButton;
  return combo;
}

