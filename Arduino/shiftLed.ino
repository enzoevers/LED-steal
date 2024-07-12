bool registers[4];
int introDelay = 50;
long lastIntroLight = 0;

bool p1_p1 = false;
bool p1_p2 = false;
bool p2_p2 = false;
bool p2_p1 = false;


void leds(bool p1p1, bool p1p2, bool p2p2, bool p2p1) {
  p1_p1 = p1p1;
  p1_p2 = p1p2;
  p2_p2 = p2p2;
  p2_p1 = p2p1;

  assignLeds();
  writereg();
}

void assignLeds() {
  registers[0] = p1_p1;
  registers[1] = p1_p2;
  registers[2] = p2_p2;
  registers[3] = p2_p1;
}

void writereg()
{
  digitalWrite(latchPin, LOW);

  for (int i = 3; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, registers[i]);
    digitalWrite(clockPin, HIGH);
  }

  digitalWrite(latchPin, HIGH);
}



