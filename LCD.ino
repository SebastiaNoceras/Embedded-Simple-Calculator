#include <stdio.h>
#include "LCD.h"
#include "Keypad.h"

#define PIN_RS 53
#define PIN_RW 50
#define PIN_EN 49

#define PIN_DB4 46
#define PIN_DB5 45
#define PIN_DB6 42
#define PIN_DB7 41

#define KEYPAD_COL0_PIN 6
#define KEYPAD_COL1_PIN 8
#define KEYPAD_COL2_PIN 7
#define KEYPAD_COL3_PIN 9

#define KEYPAD_ROW0_PIN 2
#define KEYPAD_ROW1_PIN 3
#define KEYPAD_ROW2_PIN 4
#define KEYPAD_ROW3_PIN 5

#define DISPLAY_AREA 15
#define DISPLAY_MEMORY 40

Keypad keypad; // KEYPAD OBJECT

LCD lcd(
  PIN_RS, PIN_RW, PIN_EN,
  PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7
  );

void setup() //INICIALITATION
{
  keypad.initKeypad(KEYPAD_COL0_PIN, KEYPAD_COL1_PIN, KEYPAD_COL2_PIN, KEYPAD_COL3_PIN,
                    KEYPAD_ROW0_PIN, KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN);
  lcd.init();
}

void loop()
{
  // DECLARATIONS
  char *keys[] = {"7","8","9","+","4","5","6","-","1","2","3","x"," "," "," ","/"}; //VALUES TO PRINT
  uint8_t key = KEYPAD_NO_KEY;
  uint8_t lastkey = KEYPAD_NO_KEY;
  uint8_t col = 1;
  uint8_t memoryFull = false; //INDICATES THE MEMORY OF THE FIRST ROW IS FULL

  while (1)
  {
    while (key == KEYPAD_NO_KEY)  key = keypad.readKeypad(NO_BLOCK); //
    switch (key) {
      
      case 13: // IF CLEAR (C) IS PRESSED
        lcd.clear();
        col = 1;
        memoryFull = false;
        break;

      case 12: // IF <- CLEAR LAST CHARACTER IS PRESSED
        if (col != 1){
          if (col > 16) lcd.shiftDisplayLeft();
          col--;
          lcd.setCursor(1, col);
          lcd.print(" ");
          lcd.setCursor(1, col);
        }
        break;
      
      default: // IF ANY OTHER BUTTON IS PRESSED
        if (memoryFull == false) lcd.print(keys[key]);
        if ((col > DISPLAY_AREA) && (col < DISPLAY_MEMORY)) lcd.shiftDisplayRight();
        if(col <= DISPLAY_MEMORY) col++;
        else{ // SHOWS "MEMORY FULL!" WHEN THE THERE IS NO MORE MEMORY IN THE FIRS ROW 
          lcd.setCursor(2, 27);
          lcd.print("MEMORY FULL!");
          memoryFull = true;
        }
      }
    while (key != KEYPAD_NO_KEY) key = keypad.readKeypad(NO_BLOCK); //UNTIL YOU DONT UNPRESS THE BUTTON IT WONT COME OUT
    delay(20);
  }
  
}
