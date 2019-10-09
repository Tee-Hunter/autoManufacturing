// Rotary encoder basic program and circuit
#include <Arduino.h>

volatile int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
unsigned int angle = 0;
int resolution = 1000;

//Calling Function  
void outA();
void outB();
// void angular(unsigned int PPR);

void setup() {
  Serial.begin (9600);

    pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
    pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
    

    //Setting up interrupt
    //A rising pulse from encoders activated outA(). DigitalPin 2
    attachInterrupt(digitalPinToInterrupt(2), outA, RISING);
    
    //B rising pulse from encoders activated outB(). DigitalPin 3
    attachInterrupt(digitalPinToInterrupt(3), outB, RISING);
  }
   
void loop() {
  // Send the value of counter
  if ( counter != temp ){
      Serial.print("counter \t: ");
      Serial.println(counter);
      
      // angular(counter);
      angle = (counter*360)/1000;
      Serial.print("Angle \t\t: ");
      Serial.println(angle);
  }
  // check status
  temp = counter;
}
   
void outA() {
  // outA is activated if DigitalPin 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(3) == LOW) {
      counter++;
      if (counter > 1000)
        counter = 1000;
  }
  else {
      counter--;
      if (counter < 0)
        counter = 1000;
  }
}
   
void outB() {
  // outA is activated if DigitalPin 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(2) == LOW) {
    counter--;
    if (counter < 0)
        counter = 0;
  }
  else {
    counter++;
    if (counter > 1000)
        counter = 1000;
  }
}

// void angular(unsigned int PPR) {
//   angle = (counter*360)/1000;
//   Serial.print("Angle : ");
//   Serial.println(angle);
// }


