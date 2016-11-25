// constants won't change. They're used here to
// set pin numbers:
const int buttonPin1 = 4;    // the number of the pushbutton pin
const int buttonPin2 = 3;
const int buttonPin3 = 2;
const int ledPin1 = 13;      // the number of the LED pin
const int ledPin2 = 12;
const int ledPin3 = 11;  

// Variables will change:
int ledState1 = LOW;         // the current state of the output pin
int ledState2 = LOW;        
int ledState3 = LOW;        
int buttonState1;             // the current reading from the input pin
int buttonState2;
int buttonState3;
int lastButtonState1 = HIGH;   // the previous reading from the input pin
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can't be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading1 = digitalRead(buttonPin1);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == LOW) {
        ledState1 = !ledState1;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin1, ledState1);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState1 = reading1;

  
  //GREEN

  int reading2 = digitalRead(buttonPin2);
  
  if (reading2 != lastButtonState2) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == LOW) {
        ledState2 = !ledState2;
      }
    }
  }

  digitalWrite(ledPin2, ledState2);
  lastButtonState2 = reading2;


  //BLUE

  int reading3 = digitalRead(buttonPin3);
  
  if (reading3 != lastButtonState3) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;
      if (buttonState3 == LOW) {
        ledState3 = !ledState3;
      }
    }
  }

  digitalWrite(ledPin3, ledState3);
  lastButtonState3 = reading3;
  
}

