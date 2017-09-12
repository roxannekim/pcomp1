//Time Tunnel Machine by Roxanne Kim
//NYU ITP 2016 Winter Show
//Arduino Sketch

#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(289, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
int slowestSpeed = 1500;
int fastestSpeed = 100;
int inactivityPeriod = 2000;
unsigned int lastMillis;
unsigned long now;
unsigned long lastDisplay = 0;
unsigned long p_millis = 0;
float changeVal = 0;
float speedval;
boolean playLights = false;


void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println("HELLO");
  attachInterrupt(0, change_speed, RISING);
}


void change_speed() {
  playLights = true;
  now = millis();
  speedval = now - lastDisplay;

  if (speedval >= slowestSpeed) {
    speedval = slowestSpeed;
  }

  changeVal = map(speedval, fastestSpeed, slowestSpeed, 800, 100);
  changeVal = changeVal / 100;

  if (changeVal <= 0) {
    changeVal = 0;
  }

  Serial.println(changeVal);

  lastDisplay = now;

}


void loop() {
  if (playLights) {
    if (changeVal < 5) {
      for (uint16_t i = 0; i < pixels.numPixels(); i = i + pow(2, changeVal - 1)) {
        pixels.setPixelColor(i, 1 + i * 0.17, 30, 1 + i * 0.46);
        pixels.show();

        delay(10);

        for (uint16_t i = 0; i < pixels.numPixels(); i++) {
          pixels.setPixelColor(i , 0);
        }
      }
    }

    else if (changeVal >= 5) {
      for (uint16_t i = 0; i < pixels.numPixels(); i = i + pow(2, changeVal - 1)) {
        pixels.setPixelColor(i, 1 + i * 0.46, 30, 1 + i * 0.17);
        pixels.show();

        delay(20);

        for (uint16_t i = 0; i < pixels.numPixels(); i++) {
          pixels.setPixelColor(i , 0);
        }
      }
    }
  }

  if (millis() - now >= inactivityPeriod) {
    playLights = false;
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i , 0);
    }
    
    lastMillis = millis();
  }
}


