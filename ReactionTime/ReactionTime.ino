#include "PCD8544_SPI.h"

PCD8544_SPI_FB lcd;

boolean LButton = 1;
boolean RButton = 1;
boolean YButton = 1;

boolean option1 = 1;
boolean option2 = 0;

unsigned long before_ms;
unsigned long reaction_ms;

short button_value, random_ms;

void elapsed_time(){               //procedure for capturing events from Geiger Kit
  reaction_ms = millis();
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), elapsed_time, FALLING);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW); 
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW); 
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 
  
  lcd.begin(false, 0xB5, 0x04, 0x13);
  lcd.print(F("Anwar's       experimental   box v3"));
  lcd.renderAll();

  delay(2000);
  lcd.clear();
}

void loop() {

  loop1();
  loop2();
}

void loop1 () {
  if (option1) {
    button_value = checkButtonPress();

    switch(button_value) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        lcd.clear();
        lcd.print("Press Y if LED goes GREEN");
        lcd.renderAll();
        random_ms = random(500, 5000);
        delay(random_ms);
        digitalWrite(5, HIGH);
        before_ms = millis();
        option2 = 1;
        option1 = 0;
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        lcd.clear();
        lcd.print("Press R to start reaction test..");
        lcd.renderAll();
        break;
      case 8:
        break;
      default:
        break;
    }
    delay(5);
  }
}

void loop2 () {
  if (option2) {
    YButton = digitalRead(2);
    if (YButton==0) {
      reaction_ms = millis();
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      lcd.clear();
      lcd.print("Reaction time: ");
      lcd.print(reaction_ms - before_ms);
      lcd.print(" ms");
      lcd.renderAll();
      delay(5000);
      option2 = 0;
      option1 = 1;
    }
  }
}

short checkButtonPress() {
  short combo = 0;
  YButton = digitalRead(2);
  LButton = digitalRead(3);
  RButton = digitalRead(4);
  combo = YButton + 2*LButton + 4*RButton;
  return combo;
}

