byte oneOut5SideL[8] = {
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte twoOut5SideL[8] = {
  B11100,
  B11100,
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte threeOut5SideL[8] = {
  B11110,
  B11110,
  B11100,
  B11100,
  B11000,
  B10000,
  B00000,
  B00000,
};

byte fourOut5SideL[8] = {
  B11110,
  B11110,
  B11110,
  B11100,
  B11100,
  B11100,
  B11100,
  B11000,
};

byte fiveOut5SideL[8] = {
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

int lineSideL = 0;
int columnSideL = 0;
long lastMillisSide = 0;

void createBarsSideL() {
  lcd.createChar(0, oneOut5SideL);
  lcd.createChar(1, twoOut5SideL);
  lcd.createChar(2, threeOut5SideL);
  lcd.createChar(3, fourOut5SideL);
  lcd.createChar(4, fiveOut5SideL);
}

void characterSideL() {
  if (millis() - lastMillisSide >= increaseSpeed) {
    //resets the cursor on order to overwrite to precious character.
    lcd.setCursor(columnSideL, 0);

    //Displays an increasing bar
    lcd.write(byte(lineSideL));

    lineSideL++;
    if (lineSideL == 5) {
      lineSideL = 0;
      nextColumnSideL();
    }

    lastMillisSide = millis();
  }
}

void nextColumnSideL() {
  columnSideL++;
  if (columnSideL == 16) {
    columnSideL = 0;
    lcd.setCursor(0, 0);
    lcd.write("                "); // Clears the screen.
  }
}
