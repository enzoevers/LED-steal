/*struct bar {
  byte line1 : 5;
  byte line2 : 5;
  byte line3 : 5;
  byte line4 : 5;
  byte line5 : 5;
  byte line6 : 5;
  byte line7 : 5;
  byte line8 : 5;
  };

  typedef struct bar Bar;*/



byte oneOut5L[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};

byte twoOut5L[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};

byte threeOut5L[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};

byte fourOut5L[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};

byte fiveOut5L[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

/*Bar bars[] = {one, two};*/

int lineL = 0;
int columnL = 0;
long lastMillisL = 0;
bool reverseL = false;
bool capturedP2 = false;
bool capturedP2AndDeliverd = false;

void setUpL() {
  lineL = 0;
  columnL = 0;
  lastMillisL = 0;
  reverseL = false;
  capturedP2 = false;
  capturedP2AndDeliverd = false;
}

void createBarsL_R() {
  //lcd.createChar(0, oneOut5L);
  lcd.createChar(0, twoOut5L);
  lcd.createChar(1, threeOut5L);
  lcd.createChar(2, fourOut5L);
  lcd.createChar(3, fiveOut5L);
}

void incrementL_R() {
  if (millis() - lastMillisL >= increaseSpeed) {
    upAndDownL();
    lastMillisL = millis();
  }
}

void gamePlayer1(bool pressed) {
  if (pressed) {
    upAndDownL();
  }
}

void upAndDownL() {
  //resets the cursor on order to overwrite to precious character.
  lcd.setCursor(columnL, 0);

  //Displays an increasing bar
  lcd.write(byte(lineL));

  if (reverseL) {
    lineL--;

    if (lineL < 0) {
      lcd.setCursor(columnL, 0);
      lcd.write(" ");
      lineL = 3;
      nextColumnL_R();
    }
  }
  else if (!reverseL) {
    lineL++;

    if (lineL == 4) {
      lineL = 0;
      nextColumnL_R();
    }
  }
}

void nextColumnL_R() {
  if (reverseL) {
    columnL--;
  }
  else if (!reverseL) {
    columnL++;
  }
  if (columnL == 16 && !reverseL) {
    columnL = 15;
    reverseL = true;
    capturedP2 = true;
    /*lcd.setCursor(0, 1);
      lcd.write("                "); // Clears the screen.*/
  }
  else if (columnL < 0 && reverseL && capturedP2) {
    columnL = 0;
    if (currentMode == mode[0]) {
      reverseL = false;
    }
    capturedP2AndDeliverd = true;
    /*lcd.setCursor(0, 0);
      lcd.write("                "); // Clears the screen.*/
  }
  /*else if(columnL < 0 && reverseL && capturedP2){
    capturedP2AndDeliverd = true;
    }*/
}

bool p1Reverse() {
  return reverseL;
}

bool p1Done() {
  return capturedP2AndDeliverd;
}
