// Rotary encoder basic program and circuit
#include <Arduino.h>

int encoderPin1 = 2; // Black
int encoderPin2 = 3; // White

// motor
int AIN1 = 8;      //PIN 21
int AIN2 = 7;      //PIN 22
int PWMA = 6;    //PIN 23
int STBY = 9;   // standby

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

int angularSpeed = 0;
long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

int clockwiseSpeed = 0;
int counterClockwiseSpeed = 0;

void updateEncoder();
void angular();
void clockWise();
void counterClockWise();

void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT_PULLUP); 
  pinMode(encoderPin2, INPUT_PULLUP);

  //motor output define
  pinMode(AIN1, OUTPUT); 
  pinMode(AIN2, OUTPUT); 
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){ 
  //Do stuff here
  if (lastencoderValue != encoderValue) {
    //pulse
    Serial.print("counter: ");
    Serial.print(encoderValue);
    Serial.print("\t\t | \t\t");

    angular();

    if ( encoderValue >= 0 && encoderValue <= 40600) clockWise();
    else if ( encoderValue <= 0 && encoderValue >= -40600) counterClockWise();
    
  }
  lastencoderValue = encoderValue;
}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  if (encoderValue > 40600) encoderValue = 40600;
  if (encoderValue < -40600) encoderValue = -40600;

  lastEncoded = encoded; //store this value for next time
}

void angular() {
  // angular speed (rad/s)
    angularSpeed = 2*PI*encoderValue / 1000;

    if (angularSpeed > 255 ) angularSpeed = 255;
    if (angularSpeed <= -255) angularSpeed = -255;
}

// clockwise 
void clockWise() {
  clockwiseSpeed = angularSpeed;
  Serial.print("clockwise speed: \t");
  Serial.println(clockwiseSpeed);

  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, clockwiseSpeed);
}

//counterClockwise
void counterClockWise() {
  counterClockwiseSpeed = angularSpeed * -1;
  Serial.print("counter clockwise speed: \t");
  Serial.println(counterClockwiseSpeed);

  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, counterClockwiseSpeed);
}