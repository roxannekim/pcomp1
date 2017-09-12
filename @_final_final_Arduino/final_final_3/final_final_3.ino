#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(298, PIN, NEO_GRB + NEO_KHZ800);

//const int  buttonPin = 2;    // the pin that the pushbutton is attached to

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int delayval = 10;
float speedval;
unsigned long now;

unsigned long lastDisplay = 0;
unsigned long p_millis = 0;
unsigned long change;
unsigned long changeMax = 100;
unsigned long changeMin = 0;
float changeVal = 0;

boolean playLights = false;

int slowestSpeed = 1500;
int fastestSpeed = 100;
unsigned int lastMillis;

int inactivityPeriod = 2000;


void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println("HELLO");
  attachInterrupt(0, change_speed, RISING);
}

void change_speed() {
  //Serial.println("WE ARE HERE");
  playLights = true;
  now = millis();

  speedval = now - lastDisplay;

  if (speedval >= slowestSpeed) {
    speedval = slowestSpeed;
  }

  //Serial.println(speedval);

  changeVal = map(speedval, fastestSpeed, slowestSpeed, 800, 100);
  changeVal = changeVal / 100;
  //Serial.write(changeVal);
  if (changeVal <= 0) {
    changeVal = 0;
  }

  Serial.println(changeVal);


  lastDisplay = now;

}

void loop() {

  if (playLights) {
  if (changeVal < 5){
    for (uint16_t i = 0; i < pixels.numPixels(); i = i + pow(2, changeVal - 1)) {
      pixels.setPixelColor(i, 1 + i * 0.17, 30, 1 + i * 0.46);
      pixels.show();

      delay(10);
      //Change last number in for loop
      for (uint16_t i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i , 0);
      }
    }
  }
  else if (changeVal >= 5){
    for (uint16_t i = 0; i < pixels.numPixels(); i = i+pow(2, changeVal-1)) {
      pixels.setPixelColor(i, 1 + i * 0.46, 30, 1 + i * 0.17);
      pixels.show();

      delay(20);
      //Change last number in for loop
      for (uint16_t i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i , 0);
      }
    }
  }

  }


  //Change the last number in for loop

  //  if(lastMillis - millis() >= inactivityPeriod){
  if (millis() - now >= inactivityPeriod) {
    //Serial.println("inactivity");
    playLights = false;
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i , 0);
      //      pixels.show();
    }
    lastMillis = millis();
  }

}


