#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_3_2 = CapacitiveSensor(3,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_5_4 = CapacitiveSensor(5,4);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_7_6 = CapacitiveSensor(7,6);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

int led1 = 11; 
int led2 = 12; 
int led3 = 13;          
int brightness = 0;

void setup()                    
{
   cs_3_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_3_2.capacitiveSensor(10);
    long total2 =  cs_5_4.capacitiveSensor(10);
    long total3 =  cs_7_6.capacitiveSensor(10);
if(total1 > 10){
  digitalWrite(led1, HIGH);
  }else{
      digitalWrite(led1, LOW);
    }
    
   if(total2 > 40){
  digitalWrite(led2, HIGH);
  }else{
      digitalWrite(led2, LOW);
    }

    if(total3 > 40){
  digitalWrite(led3, HIGH);
  }else{
      digitalWrite(led3, LOW);
    }
    
//    digitalWrite(led2, total2);
//    digitalWrite(led3, total3);

    
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port 
}
