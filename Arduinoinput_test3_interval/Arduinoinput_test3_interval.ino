const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
int outputValue = 0;        // value output to the PWM (analog out)


unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000; 

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
 
   // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(analogInPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(abs(outputValue));

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (outputValue == LOW) {
     outputValue = HIGH;
    } else {
      outputValue = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(analogOutPin, outputValue);
  }
}
