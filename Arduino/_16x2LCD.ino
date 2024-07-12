  /*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 9;

int increaseSpeed = 20;
bool gameSetUp = false;

int buttonPlayer1 = 7;
int buttonPlayer2 = 8;

String mode[3] = {"Intro", "Game", "Score"};
String currentMode = "Intro";
bool playerOneClicked;
bool playerTwoClicked;
bool in = true;

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup() {
  createBarsL_R();
  createBarsR_L();

  //createBarsSideL();
  lcd.begin(16, 2);

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);

  pinMode(buttonPlayer1, INPUT);
  pinMode(buttonPlayer2, INPUT);

  leds(1, 1, 1, 1);
}

void loop() {
  /*
     Intro
  */
  if (currentMode == mode[0]) {
    checkDoublePress(); //Checks if both buttons are pressed for two or more seconds and switches to the game if true.
    incrementL_R(); //Fills and empties the upper row.
    incrementR_L(); //Fills and empties the lower row.
    //characterSideL();
  }

  /*
     Game
  */
  else if (currentMode == mode[1]) {
    /*
       Game set-up
       Happens only once when the mode is set to mode[1]/"Game".
    */
    if (gameSetUp) {
      clearScreen();

      setUpL(); //Sets the values for the upper row(Player 1) to default.
      setUpR(); //Sets the values for the lower row(Player 2) to default.

      leds(1, 0, 1, 0); //Turns on all leds

      for (int i = 3; i >= 1; i--) {
        lcd.setCursor(6, 0);
        lcd.print(i);
        delay(1000);
        if (i == 1) {
          gameSetUp = false;
          clearScreen();
        }
      }
    }

    /*
       In game
    */
    if (!gameSetUp) {
      buttonChange(); //Reads if the player 1 or 2 button is presed.
      gamePlayer1(playerOneClicked); // Handles the event when a player presses the button
      playerOneClicked = false;      //
      gamePlayer2(playerTwoClicked); //
      playerTwoClicked = false;      //

      if (p1Reverse() && !p2Reverse()) {
        if (p1Done()) {
          leds(0, 1, 1, 0);
          Serial.println("Player 1 won while player 2 didn't steel the light");
        }
        else {
          leds(0, 0, 1, 0);
        }
      }
      else if (!p1Reverse() && p2Reverse()) {
        if (p2Done()) {
          leds(1, 0, 0, 1);
          Serial.println("Player 2 won while player 1 didn't steel the light");
        }
        else {
          leds(1, 0, 0, 0);
        }
      }
      else if (p1Reverse() && p2Reverse()) {
        if (p1Done()) {
          leds(0, 1, 0, 0);
          Serial.println("Player 1 won while player 2 stole the light");
        }
        else if (p2Done()) {
          leds(0, 0, 0, 1);
          Serial.println("Player 2 won while player 1   stole the light");
        }
        else {
          leds(0, 0, 0, 0);
        }
      }

      if (p1Done() || p2Done()) {
        currentMode = mode[2];
        in = true;
      }
    }
  }

  /*
     Score
  */
  else if (currentMode == mode[2]) {
    while (in) {
      clearScreen();
      lcd.setCursor(0, 0);
      if (p1Done()) {
        lcd.write("Player 1 wins!!!");
      }
      else if (p2Done()) {
        lcd.write("Player 2 wins!!!");
      }
      lcd.setCursor(0, 1);
      lcd.write("Hold to restart");
      in = false;
    }
    checkDoublePress();
  }
}


void clearScreen() {
  lcd.setCursor(0, 0);           //Clears the upper row
  lcd.write("                "); //
  lcd.setCursor(0, 1);           //Clears the lower row
  lcd.write("                "); //
}


