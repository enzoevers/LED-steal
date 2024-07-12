long buttonsPressedTime = 0;
long startButtonPressTimer  = 0;

long debounce = 0;
long debouncePlayerOne = 0;
long debouncePlayerTwo = 0;
bool lastPlayer1oneButtonState = false;
bool lastPlayer2oneButtonState = false;
bool player1ButtonState;
bool player2ButtonState;

bool btnPlayer1Reader;
bool btnPlayer2Reader;

int debounceTime = 20;

bool buttonsWherePressed = false;


void checkDoublePress() {
  getbuttonChange();
  goInGameMode();
  /*Serial.print("startButtonPressTimer: ");
    Serial.println(startButtonPressTimer);
    Serial.print("buttonsPressedTime: ");
    Serial.println(buttonsPressedTime);
    Serial.print("btn1: ");
    Serial.println(player1ButtonState);
    Serial.print("btn2: ");
    Serial.println(player2ButtonState);
    Serial.print("buttonsWherePressed: ");
    Serial.println(buttonsWherePressed);
    Serial.println();*/
  assignLastButtonState();
}

void readButtonState() {
  btnPlayer1Reader = digitalRead(buttonPlayer1);
  btnPlayer2Reader = digitalRead(buttonPlayer2);
}

void getbuttonChange() {
  readButtonState();

  if (btnPlayer1Reader != lastPlayer1oneButtonState && btnPlayer2Reader != lastPlayer2oneButtonState) {
    debounce = millis();
  }

  if (millis() - debounce >= debounceTime) {
    if (btnPlayer1Reader != player1ButtonState) {
      player1ButtonState = btnPlayer1Reader;
    }
    if (btnPlayer2Reader != player2ButtonState) {
      player2ButtonState = btnPlayer2Reader;
    }
  }
}

void assignLastButtonState() {
  lastPlayer1oneButtonState = player1ButtonState;
  lastPlayer2oneButtonState = player2ButtonState;
}

void goInGameMode() {
  if (currentMode != mode[1]) {
    //Serial.println(currentMode);
    if (player1ButtonState && player2ButtonState && !buttonsWherePressed) {
      buttonsWherePressed = true;
      startButtonPressTimer = millis();
    }

    if (!player1ButtonState && !player2ButtonState && buttonsWherePressed) {
      buttonsPressedTime = millis() - startButtonPressTimer;
      if (buttonsPressedTime >= 2000) {
        currentMode = mode[1];
        gameSetUp = true;
      }
      buttonsWherePressed = false;
    }
  }
}

void buttonChange() {
  readButtonState();

  if (millis() - debouncePlayerOne >= debounceTime) {
    if (btnPlayer1Reader != lastPlayer1oneButtonState) {
      debouncePlayerOne = millis();
      if (btnPlayer1Reader) {
        //Serial.println("One");
        playerOneClicked = true;
      }
      lastPlayer1oneButtonState = btnPlayer1Reader;
    }
  }

  if (millis() - debouncePlayerTwo >= debounceTime) {
    if (btnPlayer2Reader != lastPlayer2oneButtonState) {
      debouncePlayerTwo = millis();
      if (btnPlayer2Reader) {
        //Serial.println("Two");
        playerTwoClicked = true;
      }
      lastPlayer2oneButtonState = btnPlayer2Reader;
    }
  }
}
