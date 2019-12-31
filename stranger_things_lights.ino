#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 150

#define DATA_PIN 3

#define PI 3.14159
#define TIME_MULT 0.001 * 2 * PI * 0.6
#define ASCII_RANGE 128

#define LETTER_DURATION 650
#define AFTER_MESSAGE_PAUSE_DURATION 800

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
const char m10[] PROGMEM = "Consume. Obey. Stay asleep. Work. Reproduce. Watch Television. Conform. Buy. Obey.";
const char m11[] PROGMEM = "Oto herezja tych czasow rozumu albo cos podobnego. Widze i zgadzam sie co sluszne ale robie to co niesluszne.";
const char m12[] PROGMEM = "Whatever you do, dont fall asleep.";
const char m13[] PROGMEM = "I can smell your fear. Tasty, tasty, beautiful fear.";
const char m14[] PROGMEM = "WeRe going to get you. WeRe going to get you. Not another peep. Time to go to sleep.";
const char m15[] PROGMEM = "We all go a little mad sometimes.";
const char m16[] PROGMEM = "Monsters are real, ghosts are real too. They live inside us and sometimes they win.";
const char m17[] PROGMEM = "Walls have ears. Doors have eyes. Trees have voices. Beasts tell lies. Beware the rain. Beware the snow. Beware the man You think you know.";
const char m18[] PROGMEM = "The world outside has its own rules and those rules are not human.";
const char m19[] PROGMEM = "That cold aint the weather. Thats death approaching.";
const char m20[] PROGMEM = "I don't live in darkness. Darkness lives in me.";
const char m21[] PROGMEM = "People die. Beauty fades. Love changes. And you will always be alone.";
const char m22[] PROGMEM = "If you are reading this, then you are blissfully unaware what is creeping up behind you.";
const char m23[] PROGMEM = "I'm every nightmare you've ever had. I am your worst dream come true. I am everything you ever were afraid of!";
/* const char m20[] PROGMEM = "It is a mistake to fancy that horror is associated inextricably with darkness, silence, and solitude."; */
/* const char m20[] PROGMEM = ""; */
/* const char m20[] PROGMEM = ""; */
/* const char m20[] PROGMEM = ""; */
/* const char m20[] PROGMEM = ""; */

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
  m9,
  m10,
  m11,
  m12,
  m13,
  m14,
  m15,
  m16,
  m17,
  m18,
  m19,
  m20,
  m21,
  m22,
  m23
};

#define MESSAGE_COUNT 24

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
  char* message = getRandomMessage();
  showMessage(message);
  delay(AFTER_MESSAGE_PAUSE_DURATION);
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
