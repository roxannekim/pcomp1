int Pin1 = 12;       
int Pin2 = 11;       
int Pin3 = 10;       
int Pin4 = 9;        
int Pin5 = 6;       
int Pin6 = 5;       
int Pin7 = 3;       // the 'wave' goes Led: 1-2-3-4-5-6-7

int Value1 = 0;    //Value Led
int Value2 = 0;    
int Value3 = 0;    
int Value4 = 0;    
int Value5 = 0;    
int Value6 = 0;    
int Value7 = 0;    
        
int analog0Pin = A0;      // button to start wave
int val0 = 0;             // variable to store the value read
int threshold = 30;     // threshold for button
int timer = 100;

int sensorValue = 0;        // value read from the pot
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
int outputValue = 0;        // value output to the PWM (analog out)


void setup()  {

  pinMode(analog0Pin, INPUT);
  pinMode(Pin1, OUTPUT);   // sets the digital pin as output
  pinMode(Pin2, OUTPUT);   // sets the digital pin as output
  pinMode(Pin3, OUTPUT);   // sets the digital pin as output
  pinMode(Pin4, OUTPUT);   // sets the digital pin as output
  pinMode(Pin5, OUTPUT);   // sets the digital pin as output
  pinMode(Pin6, OUTPUT);   // sets the digital pin as output
  pinMode(Pin7, OUTPUT);   // sets the digital pin as output      
 
  Serial.begin(9600);          //  setup serial

   while (millis() < 5000) {
    sensorValue = analogRead(analog0Pin);

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

void loop(){ 
 // read the analog in value:
  sensorValue = analogRead(analog0Pin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  outputValue = abs(outputValue);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);

   // print the results to the serial monitor:
  Serial.print("sensor = ");            
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);


  if (outputValue >= threshold){ 
    for(Value1 = 0 ; Value1 <= 255; Value1+=5) {    // fade in (from min to max) Led 1
      analogWrite(Pin1, Value1);                    // sets the value (range from 0 to 255) 
      delay(512/outputValue);                            // waits for 30 milli seconds to see the dimming effect 
      } 
    for(Value1 = 255; Value1 >=0; Value1-=5){ 
      analogWrite(Pin1, Value1); 
      }
  } 

  if (Value1 = 255){ 
    for(Value2 = 0 ; Value2 <= 255; Value2+=5){ 
      analogWrite(Pin2, Value2);          
      delay(512/outputValue);                        
      } 
    for(Value2 = 255; Value2 >=0; Value2-=5){ 
      analogWrite(Pin2, Value2); 
      //delay(5); 
      } 
  }
   if (Value2 = 255){ 
    for(Value3 = 0 ; Value3 <= 255; Value3+=5){ 
      analogWrite(Pin3, Value3);         
      delay(512/outputValue);                          
      } 
     for(Value3 = 255; Value3 >=0; Value3-=5){ 
      analogWrite(Pin3, Value3); 
      //delay(5); 
      } 
   }
    if (Value3 = 255){ 
      for(Value4 = 0 ; Value4 <= 255; Value4+=5){ 
        analogWrite(Pin4, Value4);           
        delay(512/outputValue);                          
        } 
        for(Value4 = 255; Value4 >=0; Value4-=5){ 
        analogWrite(Pin4, Value4); 
       //delay(5); 
        }
   }
    if (Value4 = 255){ 
      for(Value5 = 0 ; Value5 <= 255; Value5+=5){ 
        analogWrite(Pin5, Value5);          
        delay(512/outputValue);                         
        } 
        for(Value5 = 255; Value5 >=0; Value5-=5){ 
        analogWrite(Pin5, Value5); 
        //delay(5); 
       } 
    }

     if (Value5 = 255){ 
      for(Value6 = 0 ; Value6 <= 255; Value6+=5){ 
        analogWrite(Pin6, Value6);          
        delay(512/outputValue);                         
        } 
        for(Value6 = 255; Value6 >=0; Value6-=5){ 
        analogWrite(Pin6, Value6); 
        //delay(5); 
       } 
    }
     if (Value6 = 255){ 
      for(Value7 = 0 ; Value7 <= 255; Value7+=5){ 
        analogWrite(Pin7, Value7);          
        delay(512/outputValue);                         
        } 
        for(Value7 = 255; Value7 >=0; Value7-=5){ 
        analogWrite(Pin7, Value7); 
        //delay(5); 
       } 
    }
  }
    

 
