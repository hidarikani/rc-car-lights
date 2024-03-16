const int MODE_BACK_PIN = 6;
const int MODE_FORWARD_PIN = 7;
int LATCH_PIN = 11;          // (11) ST_CP [RCK] on 74HC595
int CLOCK_PIN = 9;           // (9) SH_CP [SCK] on 74HC595
int DATA_PIN = 12;           // (12) DS [S1] on 74HC595
const int BLINKER_LEFT = 3;  // on 74HC595
const int BLINKER_RIGHT = 4; // on 74HC595
const unsigned long BLINK_INTERVAL = 500;

enum BlinkerMode
{
  OFF,
  LEFT,
  RIGHT,
  HAZARD
};

bool parkingOn = true;
bool dayOn = true;
bool headOn = false;
bool breakOn = false;
bool reverseOn = false;
BlinkerMode blinkerMode = HAZARD;
bool blinkerOn = false;
unsigned long blinkerPreviousMillis = 0;

int currentMode = 0;
byte leds = 0;

void updateShiftRegister()
{
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
  digitalWrite(LATCH_PIN, HIGH);
}

// void allBlinkersOff()
// {
//   leds &= ~(0 << BLINKER_LEFT);
//   leds &= ~(0 << BLINKER_LEFT);
// }

void blinkerToggleLeft()
{
  leds &= ~(1 << BLINKER_LEFT);
  leds |= (blinkerOn << BLINKER_LEFT);
}

void blinkerToggleRight()
{
  leds &= ~(1 << BLINKER_RIGHT);
  leds |= (blinkerOn << BLINKER_RIGHT);
}

// void handleUserInput()
// {
//   if (digitalRead(MODE_BACK_PIN) == LOW)
//   {
//     currentMode--;
//   }
//   if (digitalRead(MODE_FORWARD_PIN) == LOW)
//   {
//     currentMode++;
//   }
// }

void setup()
{
  pinMode(MODE_BACK_PIN, INPUT_PULLUP);
  pinMode(MODE_FORWARD_PIN, INPUT_PULLUP);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (blinkerMode == HAZARD)
  {
    if (currentMillis - blinkerPreviousMillis >= BLINK_INTERVAL)
    {
      blinkerPreviousMillis = currentMillis;
      blinkerOn = !blinkerOn;
    }
  }
  else
  {
    blinkerOn = false;
  }

  blinkerToggleLeft();
  blinkerToggleRight();

  updateShiftRegister();
}
