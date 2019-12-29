#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 120

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

#define PI 3.14159
#define TIME_MULT 0.001 * 2 * PI
#define ASCII_RANGE 128

// Define the array of leds
CRGB leds[NUM_LEDS];

CRGB letterColours[ASCII_RANGE];
byte letterPositions[ASCII_RANGE];

void setup() { 
    letterColours[' '] = CRGB::Brown; // debugging, remove this
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
    delay(500);
    FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() { 
  fract8 amount = toFract((1.0 + sin(TIME_MULT * millis())) / 2.0);
  CRGB colour = dim(CRGB::Red, amount);
  leds[1] = colour;

  setLetterBrightness('a', 0.5);
  setLetterBrightness('B', 1.0);
  setLetterBrightness('C', 1.0);
  setLetterBrightness('D', 1.0);
  setLetterBrightness('E', 1.0);
  setLetterBrightness('F', 1.0);
  setLetterBrightness('G', 1.0);
  setLetterBrightness('H', 1.0);
  setLetterBrightness('I', 1.0);

  FastLED.show();
  delay(10);
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
