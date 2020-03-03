/*Example sketch to control a stepper motor with DRV8825 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:

//enable pin dvr8825
#define step0 7
#define step1 8

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin1 4
#define stepPin1 3
#define motorInterfaceType1 1
// Create a new instance of the AccelStepper class:


// digital pin 3 has a pushbutton attached to it. Give it a name:
int endButton = 12;
int pushButton = 9;
int count = 0;
int count_1 = 0;


AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

AccelStepper stepper1 = AccelStepper(motorInterfaceType1, stepPin1, dirPin1);

void run_step(){
  /*if(count_1==0){
    stepper.runSpeed();
    // Set the speed in steps per second:
  // Step the motor with a constant speed as set by setSpeed():
  Serial.println("run");
  count_1++;
  }*/
  digitalWrite(step0,LOW);
  digitalWrite(step1,HIGH);
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);

}

void back_step(){
  digitalWrite(step0,LOW);
  digitalWrite(step1,LOW);
  stepper.setCurrentPosition(0);
  stepper1.setCurrentPosition(0);
  Serial.println("back");
  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
  while(stepper.currentPosition() != -800)
  {
    stepper.setSpeed(-600);
    stepper.runSpeed();
  }

  while(stepper1.currentPosition() != 800)
  {
    stepper1.setSpeed(600);
    stepper1.runSpeed();
  }
  count=0;
  count_1=0;
}

void stop_step(){
  /*stepper.setSpeed(0); 
  stepper1.setSpeed(0); */

  digitalWrite(step0,HIGH);
  digitalWrite(step1,HIGH);
}


void setup() {
///test
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);


  
  pinMode(endButton, INPUT_PULLUP);
  pinMode(pushButton, INPUT_PULLUP);
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(1000);
  Serial.begin(9600);

  pinMode(step0, OUTPUT);
  pinMode(step1, OUTPUT);
  
  stepper.setMaxSpeed(1000);
  stepper1.setMaxSpeed(1000);
  /*stepper.setSpeed(0);
  stepper1.setSpeed(0);
  stepper.runSpeed();
  stepper1.runSpeed();*/
  digitalWrite(step0,HIGH);
  digitalWrite(step1,HIGH);
}
void loop() {
  int state = digitalRead(endButton);
  int buttonState = digitalRead(pushButton);
  Serial.println(count);
    

  if(count == 0){
   if(buttonState == 0){
   count++;
  } 
  }
  

  if(count == 1){
  //Step the motor with a constant speed as set by setSpeed():
    run_step();
    if(state == 0){
      back_step();
    }
  }else{
    stop_step();
  }

  
}
