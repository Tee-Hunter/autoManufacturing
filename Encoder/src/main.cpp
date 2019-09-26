// Rotary encoder basic program and circuit

#include <Arduino.h>

volatile signed int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder

//Calling Function  
void ai0();
void ai1();
    
void setup() {
  Serial.begin (9600);

    pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
    
    pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
    //Setting up interrupt
    //A rising pulse from encodenren activated ai0(). DigitalPin 2
    attachInterrupt(digitalPinToInterrupt(2), ai0, RISING);
    
    //B rising pulse from encodenren activated ai1(). DigitalPin 3
    attachInterrupt(digitalPinToInterrupt(3), ai1, RISING);
  }
   
  void loop() {
      // Send the value of counter
      if( counter != temp ){
      Serial.println (counter);
      temp = counter;
    }
  }
   
  void ai0() {
    // ai0 is activated if DigitalPin 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if(digitalRead(3) == LOW) {
      counter++;
    }
      else{
        counter--;
    }
  }
   
  void ai1() {
    // ai0 is activated if DigitalPin 3 is going from LOW to HIGH
    // Check with pin 2 to determine the direction
    if(digitalRead(2) == LOW) {
      counter--;
    }
    else{
      counter++;
    }
  }


