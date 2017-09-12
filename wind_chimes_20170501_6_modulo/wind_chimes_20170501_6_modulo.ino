//NeoPixel 49 >=
//

#include <Scheduler.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 2
#define PIN2 3
#define PIN3 4

#define BRIGHTNESS 200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(35, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(42, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(49, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  strip.setBrightness(BRIGHTNESS);

  Scheduler.startLoop(loop2);
  Scheduler.startLoop(loop3);

  strip.begin();
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'

  strip2.begin();
  strip2.clear();
  strip2.show(); // Initialize all pixels to 'off'

  strip3.begin();
  strip3.clear();
  strip3.show(); // Initialize all pixels to 'off'
}

void loop() {
  whiteOverRainbow1(1, 3, 40); // whiteSpeed * whiteLength(wind speed *10) = 120
}


void whiteOverRainbow1(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength) {

  if (whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while (true) {
    for (int j = 0; j < 256; j++) {
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if ((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ) {
          strip.setPixelColor(i, 0, 0, 0);
        }
        else {
          strip.setPixelColor(i, ny(((i * 256 / strip.numPixels()) + j) & 255));
        }

      }

      if (millis() - lastTime > whiteSpeed) {
        head ++;
        tail ++ ;
        if (head == strip.numPixels()) {
          loopNum++;
        }
        lastTime = millis();
      }

      if (loopNum == loops) return;

      head %= strip.numPixels();
      tail %= strip.numPixels();
      strip.show();
      delay(wait);
    }
  }
}

void loop2() {
  whiteOverRainbow2(1, 3, 40);
  yield();
}

void whiteOverRainbow2(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength) {

  if (whiteLength >= strip2.numPixels()) whiteLength = strip2.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while (true) {
    for (int j = 0; j < 256; j++) {
      for (uint16_t i = 0; i < strip2.numPixels(); i++) {
        if ((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ) {
          strip2.setPixelColor(i, 0, 0, 0);
        }
        else {
          strip2.setPixelColor(i, seoul(((i * 256 / strip2.numPixels()) + j) & 255));
        }

      }

      if (millis() - lastTime > whiteSpeed) {
        head ++;
        tail ++ ;
        if (head == strip2.numPixels()) {
          loopNum++;
        }
        lastTime = millis();
      }

      if (loopNum == loops) return;

      head %= strip2.numPixels();
      tail %= strip2.numPixels();
      strip2.show();
      delay(wait);
    }
  }
}

void loop3() {
  whiteOverRainbow3(1, 3, 40);
  yield();
}


void whiteOverRainbow3(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength) {

  if (whiteLength >= strip3.numPixels()) whiteLength = strip3.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while (true) {
    for (int j = 0; j < 256; j++) {
      for (uint16_t i = 0; i < strip3.numPixels(); i++) {
        if ((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ) {
          strip3.setPixelColor(i, 0, 0, 0);
        }
        else {
          strip3.setPixelColor(i, somewhere(((i * 256 / strip3.numPixels()) + j) & 255));
        }

      }

      if (millis() - lastTime > whiteSpeed) {
        head ++;
        tail ++ ;
        if (head == strip3.numPixels()) {
          loopNum++;
        }
        lastTime = millis();
      }

      if (loopNum == loops) return;

      head %= strip3.numPixels();
      tail %= strip3.numPixels();
      strip.show();
      delay(wait);
    }
  }
}


uint32_t ny(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(0, 150 - WheelPos % 60, 150 - WheelPos % 30);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(0, 150 - WheelPos % 30, 150 - WheelPos % 60);
  }
}

uint32_t seoul(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(160 - WheelPos % 62, 0, 140 - WheelPos % 31);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(160 - WheelPos % 31, 0, 140 - WheelPos % 62);
  }
}

uint32_t somewhere(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(140 - WheelPos % 31, 130 - WheelPos % 31, 200 - WheelPos % 31);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(140 - WheelPos % 31, 130 - WheelPos % 31, 200 - WheelPos % 31);
  }
}

