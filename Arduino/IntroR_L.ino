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

byte oneOut5R[8] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
};

byte twoOut5R[8] = {
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
};

byte threeOut5R[8] = {
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
};

byte fourOut5R[8] = {
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
};

byte fiveOut5R[8] = {
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

int lineR = 4;
int columnR = 15;
long lastMillisR = 0;
bool reverseR = false;
bool capturedP1 = false;
bool capturedP1AndDeliverd = false;

void setUpR() {
  lineR = 4;
  columnR = 15;
  lastMillisR = 0;
  reverseR = false;
  capturedP1 = false;
  capturedP1AndDeliverd = false;
}

void createBarsR_L() {
  //lcd.createChar(0, oneOut5R);
  lcd.createChar(4, twoOut5R);
  lcd.createChar(5, threeOut5R);
  lcd.createChar(6, fourOut5R);
  lcd.createChar(7, fiveOut5R);
}

void incrementR_L() {
  if (millis() - lastMillisR >= increaseSpeed) {
    upAndDownR();
    lastMillisR = millis();
  }
}

void gamePlayer2(bool pressed) {
  if (pressed) {
    upAndDownR();
  }
}

void upAndDownR() {
  //resets the cursor on order to overwrite to precious character.
  lcd.setCursor(columnR, 1);

  //Displays an increasing bar
  lcd.write(byte(lineR));

  if (reverseR) {
    lineR--;

    if (lineR == 3) {
      lcd.setCursor(columnR, 1);
      lcd.write(" ");
      lineR = 7;
      nextColumnR_L();
    }
  }
  else if (!reverseR) {
    lineR++;

    if (lineR == 8) {
      lineR = 4;
      nextColumnR_L();
    }
  }
}

void nextColumnR_L() {
  if (reverseR) {
    columnR++;
  }
  else if (!reverseR) {
    columnR--;
  }
  if (columnR < 0 && !reverseR) {
    columnR = 0;
    reverseR = true;
    capturedP1 = true;
    /*lcd.setCursor(0, 1);
      lcd.write("                "); // Clears the screen.*/
  }
  else if (columnR == 16 && reverseR && capturedP1) {
    columnR = 15;
    if (currentMode == mode[0]) {
      reverseR = false;
    }
    capturedP1AndDeliverd = true;
    /*lcd.setCursor(0, 1);
      lcd.write("                "); // Clears the screen.*/
  }
  /*else if(columnL == 16 && reverseR && capturedP1){
    capturedP1AndDeliverd = true;
    }*/
}

bool p2Reverse() {
  return reverseR;
}

bool p2Done() {
  return capturedP1AndDeliverd;
}
