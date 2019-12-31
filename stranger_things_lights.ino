#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 150

#define DATA_PIN 3

#define PI 3.14159
#define TIME_MULT 0.001 * 2 * PI * 0.6
#define ASCII_RANGE 128

#define LETTER_DURATION 600

// Define the array of leds
CRGB leds[NUM_LEDS];

CRGB letterColours[ASCII_RANGE];
byte letterPositions[ASCII_RANGE];

#define MIN_BLINK_LAG 0
#define MAX_BLINK_LAG 700

#define MIN_BLINK_PERIOD 300
#define MAX_BLINK_PERIOD 1200

#define BLINK_DURATION 3000
#define BLINK_STRENGTH_MULTIPLIER 0.7

unsigned int blinkLag[ASCII_RANGE];
unsigned int blinkPeriod[ASCII_RANGE];

// https://www.arduino.cc/reference/tr/language/variables/utilities/progmem/
#include <avr/pgmspace.h>

char messageBuffer[280];

/* const char m0[] PROGMEM = "abcdefghijklmnopqrstuvwxyz"; */
const char m0[] PROGMEM = "Run. Run now.";
const char m1[] PROGMEM = "Happy new year!";
const char m2[] PROGMEM = "Never gonna give you up Never gonna let you down Never gonna run around and desert you Never gonna make you cry Never gonna say goodbye Never gonna tell a lie and hurt you ";
const char m3[] PROGMEM = "I like it when the red water comes out ";
const char m4[] PROGMEM = "Can you feel us getting closer ";
const char m5[] PROGMEM = "I am scared. It is so dark in here ";
const char m6[] PROGMEM = "Do you like the taste of poison in your drink?";
const char m7[] PROGMEM = "Wake up! You've been in a coma for the past five years! Please! We miss you! Wake up now!";
const char m8[] PROGMEM = "No, please, no. Im not ready. Please stop. Please.";
const char m9[] PROGMEM = "Litwo, ojczyzno moja! Ty jestes jak zdrowie; Ile cie trzeba cenic ten tylko sie dowie kto cie stracil. Dzis pieknosc twa w calej ozdobie widze i opisuje bo tesknie po tobie.";

const char* const messages[] PROGMEM = {
  m0,
  m1,
  m2,
  m3,
  m4,
  m5,
  m6,
  m7,
  m8,
  m9
};

#define MESSAGE_COUNT 10

void setup() { 
  randomSeed(analogRead(A0));
  seedBlinking();
  letterColours[' '] = CRGB::Black; // For debugging change to something else
  letterColours['A'] = CRGB::LightGoldenrodYellow;
  letterColours['B'] = CRGB::Blue;
  letterColours['C'] = CRGB::Purple;
  letterColours['D'] = CRGB::Green;
  letterColours['E'] = CRGB::Blue;
  letterColours['F'] = CRGB::Yellow;
  letterColours['G'] = CRGB::Purple;
  letterColours['H'] = CRGB::Green;
  letterColours['I'] = CRGB::Purple;
  letterColours['J'] = CRGB::Blue;
  letterColours['K'] = CRGB::Green;
  letterColours['L'] = CRGB::Teal;
  letterColours['M'] = CRGB::Yellow;
  letterColours['N'] = CRGB::Purple;
  letterColours['O'] = CRGB::Purple;
  letterColours['P'] = CRGB::Teal;
  letterColours['Q'] = CRGB::Purple;
  letterColours['R'] = CRGB::Teal;
  letterColours['S'] = CRGB::LightGoldenrodYellow;
  letterColours['T'] = CRGB::Yellow;
  letterColours['U'] = CRGB::Blue;
  letterColours['V'] = CRGB::Purple;
  letterColours['W'] = CRGB::Blue;
  letterColours['X'] = CRGB::Yellow;
  letterColours['Y'] = CRGB::Purple;
  letterColours['Z'] = CRGB::Red;

  letterPositions[' '] = 2; //should not collide with any other we care about
  // TOP ROW
  letterPositions['A'] = 114;
  letterPositions['B'] = 119;
  letterPositions['C'] = 124;
  letterPositions['D'] = 129;
  letterPositions['E'] = 134;
  letterPositions['F'] = 139;
  letterPositions['G'] = 143;
  letterPositions['H'] = 149;

  // MID ROW
  letterPositions['I'] = 94;
  letterPositions['J'] = 88;
  letterPositions['K'] = 84;
  letterPositions['L'] = 80;
  letterPositions['M'] = 75;
  letterPositions['N'] = 71;
  letterPositions['O'] = 67;
  letterPositions['P'] = 63;
  letterPositions['Q'] = 57;

  // BOTTOM ROW 
  letterPositions['R'] = 5;
  letterPositions['S'] = 9;
  letterPositions['T'] = 13;
  letterPositions['U'] = 17;
  letterPositions['V'] = 21;
  letterPositions['W'] = 25;
  letterPositions['X'] = 29;
  letterPositions['Y'] = 33;
  letterPositions['Z'] = 39;
  delay(500);
  FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() { 
  /* fract8 amount = toFract((1.0 + sin(TIME_MULT * millis())) / 2.0); */
  /* CRGB colour = dim(CRGB::Red, amount); */
  /* leds[1] = colour; */

  /* setLetterBrightness('a', 0.5); */
  /* setLetterBrightness('B', 1.0); */
  /* setLetterBrightness('C', 1.0); */
  /* setLetterBrightness('D', 1.0); */
  /* setLetterBrightness('E', 1.0); */
  /* setLetterBrightness('F', 1.0); */
  /* setLetterBrightness('G', 1.0); */
  /* setLetterBrightness('H', 1.0); */
  /* setLetterBrightness('I', 1.0); */

  /* FastLED.show(); */
  /* delay(10); */

  char* message = getRandomMessage();
  showMessage(message);
  delay(100);
  blink(BLINK_DURATION);
  delay(100);
}

fract8 toFract(float amount) {
  return byte(round(amount * 255));
}

fract8 toFract(double amount) {
  return byte(round(amount * 255));
}

CRGB dim(CRGB colour, float amount) {
  return blend(CRGB::Black, colour, toFract(amount));
}

CRGB dim(CRGB colour, fract8 amount) {
  return blend(CRGB::Black, colour, amount);
}

void setLetterBrightness(char letter, float brightness) {
  letter = normalizeLetter(letter);
  byte position = letterPositions[letter];
  CRGB maxColour = letterColours[letter];

  leds[position] = dim(maxColour, brightness);
}

char normalizeLetter(char letter) {
  if(letter >= 'A' && letter <= 'Z') {
    return letter;
  }

  if (letter >= 'a' && letter <= 'z') {
    return char(letter - 'a' + 'A');
  }

  return ' ';
}

char* getRandomMessage() {
  int idx = random(MESSAGE_COUNT);
  strcpy_P(messageBuffer, (char *)pgm_read_word(&(messages[idx])));
  return messageBuffer;
}

void clearLetters() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void showMessage(char* message) {
  // clear the board
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  unsigned long startTime = millis();
  long messageLength = strlen(message);
  unsigned long endTime = startTime + LETTER_DURATION * messageLength;

  unsigned long now;
  while((now = millis()) < endTime) {
    unsigned long elapsed = now - startTime;
    unsigned long curIdx = elapsed / LETTER_DURATION;
    unsigned long letterTime = elapsed % LETTER_DURATION;

    float brightness = brightnessCurve(letterTime);
    // previous letter needs to be set first in case it's the
    // same letter two letters in a row
    if(curIdx - 1 >= 0) {
      setLetterBrightness(message[curIdx - 1], 1.0 - sqrt(brightness));
    }

    setLetterBrightness(message[curIdx], brightness);

    FastLED.show();
  }
}

float brightnessCurve(unsigned long timeOffset) {
  float time = TIME_MULT * timeOffset;
  if(timeOffset <= 0.0) {
    return 0.0;
  }
  if(time >= PI / 2.0) {
    return 1.0;
  }
  return 1.0 - cos(time);
}

void blink(unsigned long blink_duration) {
  seedBlinking();
  unsigned long start = millis();
  unsigned long time;

  while((time = (millis() - start)) <= BLINK_DURATION) {
    for(char letter = 'A'; letter <= 'Z'; letter++) {
      float letterAmount = blinkCurve(time, blinkLag[letter], blinkPeriod[letter]);
      setLetterBrightness(letter, letterAmount);
    }
    FastLED.show();
    delay(1);
  }
  clearLetters();
}

float blinkCurve(unsigned long time, unsigned long lag, unsigned long period) {
  if(time < lag) {
    return 0.0;
  }
  time = time - lag;

  float amount = sin(2.0 * PI * time / (1.0 * period));
  return max(0.0, amount) * BLINK_STRENGTH_MULTIPLIER;
}

void seedBlinking() {
  for(char letter = 'A'; letter <= 'Z'; letter++) {
    blinkLag[letter] = random(MIN_BLINK_LAG, MAX_BLINK_LAG);
    blinkPeriod[letter] = random(MIN_BLINK_PERIOD, MAX_BLINK_PERIOD);
  }
}
