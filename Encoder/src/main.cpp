// Rotary encoder basic program and circuit
#include <Arduino.h>

volatile signed int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
float Angle = 0.0; // define the angle variable
int Speed = 0;  // declare the speed variable
int resolution = 1000;

//Calling Function  
void ai0();
void ai1();
void rotationAngle (int PPR);
void rotatoinSpeed (int NoP);
    
void setup() {
  Serial.begin (9600);

    pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
    
    pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
    //Setting up interrupt
    //A rising pulse from encoders activated ai0(). DigitalPin 2
    attachInterrupt(digitalPinToInterrupt(2), ai0, RISING);
    
    //B rising pulse from encoders activated ai1(). DigitalPin 3
    attachInterrupt(digitalPinToInterrupt(3), ai1, RISING);
  }
   
void loop() {
  // Send the value of counter
  if( counter != temp ){
      Serial.print("Pulse : ");
      Serial.println(counter);
      temp = counter;
      rotationAngle (counter);
      rotatoinSpeed (counter);
  }
  // delay(1000);
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

void rotationAngle (int NoP) {
  // decare the angle variable as global
  // calculate DPP form Encoder value
  Angle = (NoP * 360.0) / resolution;
  // print out angle (DPP)
  Serial.print("Angle : ");
  Serial.print(Angle);
  Serial.println("°");
}

void rotatoinSpeed (int NoP) {
  // declare the speed variable as global
  // calculate Speed form Encoder value
  Speed = (NoP * 60) / resolution;
  // Print out the Speed
  Serial.print("Speed : ");
  Serial.print(Speed);
  Serial.println(" RPM");
}
