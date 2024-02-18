// www.elegoo.com
// 2016.12.9

int tDelay = 500;
int latchPin = 11; // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;  // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;  // (12) DS [S1] on 74HC595

byte leds = 0;

const int TURN_LEFT_BACK = 2;
const int TURN_LEFT_FRONT = 3;

const int TURN_RIGHT_BACK = 4;
const int TURN_RIGHT_FRONT = 5;

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void turnLeft()
{
  for (int i = 0; i < 3; i++)
  {
    leds = 0;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    delay(tDelay);

    digitalWrite(latchPin, LOW);
    bitSet(leds, TURN_LEFT_BACK);
    bitSet(leds, TURN_LEFT_FRONT);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    delay(tDelay);
  }
}

void turnRight()
{
  for (int i = 0; i < 3; i++)
  {
    leds = 0;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    delay(tDelay);

    digitalWrite(latchPin, LOW);
    bitSet(leds, TURN_RIGHT_BACK);
    bitSet(leds, TURN_RIGHT_FRONT);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    delay(tDelay);
  }
}

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop()
{
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
  turnLeft();
  turnRight();
}
