#include "PCD8544_SPI.h"
#include <SFE_BMP180.h>
#include "RTClib.h"

SFE_BMP180 bmp180;
double T, P;
char status;

RTC_DS1307 rtc;
PCD8544_SPI_FB lcd;

boolean LButton = 1;
boolean RButton = 1;
boolean YButton = 1;
boolean option1 = 1;
boolean option2 = 0;
boolean option3 = 0;
boolean option4 = 0;
boolean option5 = 0;
boolean option6 = 0;

boolean too_early = 0;

uint8_t menu_choice = 0, k;

unsigned long before_ms, current_ms;

short button_value, random_ms, reaction_times[5], reaction_avg;

char display_buf[] = "Main Menu:      > LED tests     Reactions     Sensors       Date&Time Y: select    ";
char dummy;
size_t len;

void setup() {
  pinMode(2, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(2), elapsed_time, FALLING);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW); 
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW); 
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 

  lcd.begin(false, 0xB5, 0x04, 0x13);

  lcd.print(F("Anwar's       Experimental  Arduino box!                  Enjoy :)"));
  lcd.renderAll();
  delay(4000);
  lcd.clear();
  len = lcd.print(display_buf);
  lcd.renderString(0, 0, len);
}

void loop() {
  if (option1) loopMenu();
  if (option2) loopRGBLED();
  if (option3) loopReactionMenu();
  if (option4) loopReactionTiming();
  if (option5) loopSensor();
  if (option6) loopDateTime();
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
      if (menu_choice==0) {
        lcd.clear();
        lcd.print("RGB LED tests!L: Blue       R: Green      Y: Red        Off: L+R      Exit: L+Y");
        lcd.renderAll();
        option1 = 0;
        option2 = 1;
        option3 = 0;
        delay(200);
      }
      else if (menu_choice==1) {
        k = 0;
        lcd.clear();
        lcd.print("Reaction test!Push Y if the LED goes blue!Test repeats 5times. Press Rto begin!");
        lcd.renderAll();
        option1 = 0;
        option2 = 0;
        option3 = 1;
      }
      else if (menu_choice==2) {
        bmp180.begin();
        lcd.clear();
        lcd.print("Internal      sensors:      T = ...       p = ...       ");
        lcd.renderAll();
        delay(400);
        option1 = 0;
        option5 = 1;
      }
      else if (menu_choice==3) {
        option1 = 0;
        option6 = 1;
      }
      break;
    default:
      break;
  }
  delay(50);
}

void loopRGBLED () {
  button_value = checkButtonPress();
  switch(button_value) {
    case 1:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      delay(500);
      break;
    case 3:
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      break;
    case 4:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      delay(500);
      option1 = 1;
      option2 = 0;
      lcd.clear();
      len = lcd.print(display_buf);
      lcd.renderString(0, 0, len);
      break;
    case 5:
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      break;
    case 6:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      break;
    default:
      break;
  }
  delay(100);
}

void loopReactionMenu() {
  button_value = checkButtonPress();
  if (button_value==3) {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    random_ms = random(1000, 7000);
    lcd.clear();
    lcd.print("Press Y if LEDgoes BLUE.    Time: ... ms");
    lcd.renderAll();
    
    too_early = 0;
    before_ms = millis();
    while ((millis() - before_ms) < random_ms) {
      YButton = digitalRead(2);
      if (!YButton) {
        too_early=1;
        break;
      }
    }
    
    if (too_early) {
      digitalWrite(7, HIGH);
      lcd.clear();
      lcd.print("Press Y if LEDgoes BLUE.    Too early!    Press R to    retry.                Exit:L");
      lcd.renderAll();
      delay(1000);
    }
    else {
      option3 = 0;
      option4 = 1;
      digitalWrite(5, HIGH);
      before_ms = millis();
    }
  }
  else if (button_value==5) {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    option3 = 0;
    option1 = 1;
    
    lcd.clear();
    len = lcd.print(display_buf);
    lcd.renderString(0, 0, len);
  }
  else if (k == 5) {
    delay(2000);
    reaction_avg = (reaction_times[0]+reaction_times[1]+reaction_times[2]+reaction_times[3]+reaction_times[4])/5;
    lcd.clear();
    lcd.print("Test Finished!Your avg.:    ");
    if (reaction_avg<125) {
      lcd.print(reaction_avg);
      lcd.print(" ms: GOD!!!");
    }
    else if (reaction_avg<150) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Robot!");
    }
    else if (reaction_avg<160) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Drugs?");
    }
    else if (reaction_avg<170) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Crazy!");
    }
    else if (reaction_avg<180) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Wow!!!");
    }
    else if (reaction_avg<190) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Fast! ");
    }
    else if (reaction_avg<200) {
      lcd.print(reaction_avg);
      lcd.print(" ms: <200!!");
    }
    else if (reaction_avg<225) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Nicer!");
    }
    else if (reaction_avg<250) {
      lcd.print(reaction_avg);
      lcd.print(" ms: Nice! ");
    }
    else if (reaction_avg<1000) {
      lcd.print(reaction_avg);
      lcd.print(" ms        ");
    }
    else {
      lcd.print(">999 ms, slow!");
    }
    lcd.print("Human avg.:   250 ms        ");
    lcd.print("Redo:R, Exit:L");
    lcd.renderAll();
    k = 0;
  }
  else {
    delay(100);
  }
}

void loopReactionTiming() {
  YButton = digitalRead(2);
    if (YButton==0) {
      reaction_times[k] = millis() - before_ms;
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      lcd.clear();
      lcd.print("Press Y if LEDgoes BLUE.    Time: ");
      if (reaction_times[k++]<1000) {
        lcd.print(reaction_times[k-1]);
      }
      else {
        lcd.print(999);
      }
      lcd.print(" ms                Test ");
      lcd.print(k);
      lcd.print("/5      ");
      lcd.print("Next:R, Exit:L");
      lcd.renderAll();
      delay(100);
      option4 = 0;
      option3 = 1;
    }
}

void loopSensor() {
  status = bmp180.startTemperature();
  delay(status);
  bmp180.getTemperature(T);
  status = bmp180.startPressure(3);
  delay(status);
  status = bmp180.getPressure(P,T);
  
  lcd.clear();
  lcd.print("Internal      sensors:      T = ");
  lcd.print(T);
  lcd.print(" C   p = ");
  lcd.print(P/10, 3);
  lcd.print(" kPa              Exit: Hold L");
  lcd.renderAll();
  
  LButton = digitalRead(3);
  if (!LButton) {
    option1 = 1;
    option5 = 0;
    
    lcd.clear();
    len = lcd.print(display_buf);
    lcd.renderString(0, 0, len);
  }
  delay(500);
}

void loopDateTime() {
  DateTime now = rtc.now();
  
  lcd.clear();
  lcd.print("Current time: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  lcd.print("       ");
  
  lcd.print(now.year());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.day());

  lcd.print("     Exit: Hold L");
  
  lcd.renderAll();
  
  LButton = digitalRead(3);
  if (!LButton) {
    option1 = 1;
    option6 = 0;
    
    lcd.clear();
    len = lcd.print(display_buf);
    lcd.renderString(0, 0, len);
  }
  delay(1000);
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

//void elapsed_time(){
//  //reaction_ms = millis();
//  too_early++;
//}
