#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(299, PIN, NEO_GRB + NEO_KHZ800);

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
unsigned int changeVal = 0;

boolean playLights = false;

int slowestSpeed = 800;
int fastestSpeed = 10;

int inactivityPeriod = 500;


void setup() {
  Serial.begin(115200);
  pixels.begin();
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

  Serial.println(speedval);

  changeVal = map(speedval, fastestSpeed, slowestSpeed, 800, 100);
  changeVal = changeVal/100;
  Serial.write(changeVal);
  if (changeVal <= 0) {
    changeVal = 0;
  }

  Serial.println(changeVal);


  lastDisplay = now;

}
void loop() {
  //Serial.print("change: ");
  //Serial.println(changeVal);


  if (playLights) {
    for (uint16_t i = 0; i < pixels.numPixels(); i = i + changeVal ) {
      pixels.setPixelColor(i, 1 + i * 0.17, 30, 1 + i * 0.46);
      pixels.show();

      delay(10);
      //Change last number in for loop
      for (uint16_t i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i , 0);
      }
    }

  }

  //Change the last number in for loop


  if (millis() - now >= inactivityPeriod) {
   // Serial.println("inactivity");
    playLights = false;
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i , 255 - i, 10, 255 -i);
      pixels.show();
    }
  }

}


