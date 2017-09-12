#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#define USE_SERIAL Serial
#define BRIGHTNESS 255
const int numPixels  = 50;
//const int numPixels2  = 54;
const int ledPin = 14; // the pin that the LED is attached to
const int ledPin2 = 12; // the pin that the LED is attached to
float speed;
int c;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numPixels, ledPin2, NEO_GRB + NEO_KHZ800);

ESP8266WiFiMulti WiFiMulti;

const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
DynamicJsonBuffer jsonBuffer(bufferSize);

void setup() {


  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("RHK", "11223344");
  WiFiMulti.addAP("itpsandbox", "NYU+s0a!+P?");

  strip.begin();
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'

  strip2.begin();
  strip2.clear();
  strip2.show(); // Initialize all pixels to 'off'



}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    //callWeatherAPI("New York");
    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://api.wunderground.com/api/3e5efec846df6775/conditions/q/NY/10003.json");

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);

        JsonObject& root = jsonBuffer.parseObject(payload);
        long speed = root["current_observation"]["wind_kph"]; // 1351824120
        Serial.println(speed);
        Serial.println(c);


      } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }

    whiteOverRainbow1(1, 30, 4);
    whiteOverRainbow2(1, 10, 12);
  
    //whiteOverRainbow1(1, 120 / 1 + speed * 10, 1 + speed * 10); // whiteSpeed * whiteLength(wind speed *10) = 120
    //whiteOverRainbow2(1, 120 / 1 + speed * 10, 1 + speed * 10); // whiteSpeed * whiteLength(wind speed *10) = 120
  }

}



void dayWhite(uint8_t wait, uint8_t mapSpeed) {
  for (int j = 0; j < 256 ; j++) {
    for (uint16_t i = 0; i < strip.numPixels() +  mapSpeed ; i++) {
      strip.setBrightness(mapSpeed - abs(mapSpeed - j % mapSpeed * 2));
      strip.setPixelColor(j, 100, 250, 150);
      Serial.println(mapSpeed - abs(mapSpeed - j % mapSpeed * 2));
    }
    delay(wait);
    strip.show();
  }
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

void whiteOverRainbow2(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength) {

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
    return strip.Color(0, 150 - WheelPos % 20, 150 - WheelPos % 10);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(0, 150 - WheelPos % 10, 150 - WheelPos % 20);
  }
}

uint32_t seoul(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 62) {
    return strip.Color(160 - WheelPos % 20, 0, 140 - WheelPos % 10);
  }
  if (WheelPos < 124) {
    WheelPos -= 62;
    return strip.Color(160 - WheelPos % 10, 0, 140 - WheelPos % 20);
  }
}
