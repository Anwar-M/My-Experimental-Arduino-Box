#include "PCD8544_SPI.h"
PCD8544_SPI_FB lcd;

boolean LButton = 1;
boolean RButton = 1;
boolean YButton = 1;
boolean option1 = 1;
boolean option2 = 0;
boolean option3 = 0;

uint8_t menu_choice = 0;

short button_value;

char display_buf[] = "Main Menu:      > LED test      Reactions     Option 3      Option 4  Y: select    ";
char dummy;
size_t len;

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
  
  len = lcd.print(display_buf);
  lcd.renderString(0, 0, len);
  //lcd.renderAll();
  delay(2000);
  delay(2000);
}

void loop() {
  loopMenu();
  delay(100);
}

void loopMenu() {
  button_value = checkButtonPress();
  switch(button_value) {
    case 3:
      menuDown();
      delay(100);
      break;
    case 5:
      menuUp();
      delay(100);
      break;
    case 6:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      lcd.clear();
      lcd.print("Y button is pressed :S!");
      lcd.renderAll();
      break;
    default:
      break;
  }
}

void menuDown() {
  dummy = display_buf[58];
  lcd.clear();
  display_buf[58] = display_buf[44];
  display_buf[44] = display_buf[30];
  display_buf[30] = display_buf[16];
  display_buf[16] = dummy;
  menu_choice = (menu_choice+1)%4;
  len = lcd.print(display_buf);
  lcd.renderString(0, 0, len);
}

void menuUp() {
  dummy = display_buf[16];
  lcd.clear();
  display_buf[16] = display_buf[30];
  display_buf[30] = display_buf[44];
  display_buf[44] = display_buf[58];
  display_buf[58] = dummy;
  menu_choice = (menu_choice+3)%4;
  len = lcd.print(display_buf);
  lcd.renderString(0, 0, len);
}

short checkButtonPress() {
  short combo = 0;
  YButton = digitalRead(2);
  LButton = digitalRead(3);
  RButton = digitalRead(4);
  combo = YButton + 2*LButton + 4*RButton;
  return combo;
}
