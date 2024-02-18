enum BlinkerMode
{
  OFF,
  LEFT,
  RIGHT,
  HAZARD
};

BlinkerMode blinkerMode = OFF;

int tDelay = 500;
int latchPin = 11; // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;  // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;  // (12) DS [S1] on 74HC595

byte leds = 0;

const int BLINKER_LEFT_BACK = 2;
const int BLINKER_LEFT_FRONT = 3;

const int BLINKER_RIGHT_BACK = 4;
const int BLINKER_RIGHT_FRONT = 5;

BlinkerMode blinkerScript[] =
{
    OFF, OFF, OFF,
    LEFT, LEFT, LEFT,
    RIGHT, RIGHT, RIGHT,
    HAZARD, HAZARD, HAZARD
};
int blinkerScriptIndex = 0;

void updateBlinkerScriptIndex()
{
  blinkerScriptIndex++;
  if (blinkerScriptIndex >= sizeof(blinkerScript))
  {
    blinkerScriptIndex = 0;
  }
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void blinkerOff()
{
  leds &= ~(1 << BLINKER_LEFT_BACK);
  leds &= ~(1 << BLINKER_LEFT_FRONT);
  leds &= ~(1 << BLINKER_RIGHT_BACK);
  leds &= ~(1 << BLINKER_RIGHT_FRONT);
}

void blinkerToggleLeft()
{
  leds ^= (1 << BLINKER_LEFT_BACK);
  leds ^= (1 << BLINKER_LEFT_FRONT);

  leds &= ~(0 << BLINKER_RIGHT_BACK);
  leds &= ~(0 << BLINKER_RIGHT_FRONT);
}

void blinkerToggleRight()
{
  leds ^= (1 << BLINKER_RIGHT_BACK);
  leds ^= (1 << BLINKER_RIGHT_FRONT);

  leds &= ~(0 << BLINKER_LEFT_BACK);
  leds &= ~(0 << BLINKER_LEFT_FRONT);
}

void blinkerToggleHazard()
{
  leds ^= (1 << BLINKER_LEFT_BACK);
  leds ^= (1 << BLINKER_LEFT_FRONT);
  leds ^= (1 << BLINKER_RIGHT_BACK);
  leds ^= (1 << BLINKER_RIGHT_FRONT);
}

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop()
{
  switch (blinkerScript[blinkerScriptIndex])
  {
  case OFF:
    blinkerOff();
    break;
  case LEFT:
    blinkerToggleLeft();
    break;
  case RIGHT:
    blinkerToggleRight();
    break;
  case HAZARD:
    blinkerToggleHazard();
    break;
  }

  updateShiftRegister();
  updateBlinkerScriptIndex();
  delay(tDelay);
}
