//NeoPixel 144
//

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define BRIGHTNESS 200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(124, PIN, NEO_GRB + NEO_KHZ800);

void setup() {


  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  whiteOverRainbow(1, 3, 40); // whiteSpeed * whiteLength(wind speed *10) = 120
}


void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {

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
          strip.setPixelColor(i, seoul(((i * 256 / strip.numPixels()) + j) & 255));
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

uint32_t ny(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(0, 150 - WheelPos%60,150 - WheelPos%30);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(0, 150 - WheelPos%30, 150 - WheelPos%60);
  }
}

uint32_t seoul(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(160 - WheelPos%62,0, 140 - WheelPos%31);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(160 - WheelPos%31, 0, 140 - WheelPos%62);
  }
}

uint32_t somewhere(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(140 - WheelPos%31, 130 - WheelPos%31,200 - WheelPos%31);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(140 - WheelPos%31, 130 - WheelPos%31, 200 - WheelPos%31);
  }
}

