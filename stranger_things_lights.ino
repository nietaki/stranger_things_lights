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

#define MIN_BLINK_PERIOD 400
#define MAX_BLINK_PERIOD 1500

#define BLINK_DURATION 3000

unsigned int blinkLag[ASCII_RANGE];
unsigned int blinkPeriod[ASCII_RANGE];

void setup() { 
  randomSeed(analogRead(A0));
  seedBlinking();
  letterColours[' '] = CRGB::Brown; // debugging, TODO change to Black
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
  letterPositions['A'] = 13;
  letterPositions['B'] = 14;
  letterPositions['C'] = 15;
  letterPositions['D'] = 16;
  letterPositions['E'] = 17;
  letterPositions['F'] = 18;
  letterPositions['G'] = 19;
  letterPositions['H'] = 20;
  letterPositions['I'] = 21;
  letterPositions['J'] = 22;
  letterPositions['K'] = 23;
  letterPositions['L'] = 24;
  letterPositions['M'] = 25;
  letterPositions['N'] = 26;
  letterPositions['O'] = 27;
  letterPositions['P'] = 28;
  letterPositions['Q'] = 29;
  letterPositions['R'] = 30;
  letterPositions['S'] = 31;
  letterPositions['T'] = 32;
  letterPositions['U'] = 33;
  letterPositions['V'] = 34;
  letterPositions['W'] = 35;
  letterPositions['X'] = 36;
  letterPositions['Y'] = 37;
  letterPositions['Z'] = 38;
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

  showMessage("abcde");
  blink(BLINK_DURATION);
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
}

float blinkCurve(unsigned long time, unsigned long lag, unsigned long period) {
  if(time < lag) {
    return 0.0;
  }
  time = time - lag;

  float amount = sin(2.0 * PI * time / (1.0 * period));
  return max(0.0, amount);
}

void seedBlinking() {
  for(char letter = 'A'; letter <= 'Z'; letter++) {
    blinkLag[letter] = random(MIN_BLINK_LAG, MAX_BLINK_LAG);
    blinkPeriod[letter] = random(MIN_BLINK_PERIOD, MAX_BLINK_PERIOD);
  }
}
