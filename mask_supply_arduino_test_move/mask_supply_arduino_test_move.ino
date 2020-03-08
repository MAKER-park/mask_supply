/*Example sketch to control a stepper motor with DRV8825 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:

//enable pin dvr8825
#define upper_en 7
#define roller_en 8

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin1 4
#define stepPin1 3
#define motorInterfaceType1 1
// Create a new instance of the AccelStepper class:


// set limit switch
int maskButton = 13;
int endButton = 12;
int startButton = 11;

//set pushbutton
int roundButton = 9;
int triangle = 10;

int count = 0;
int count_1 = 0;

AccelStepper upper = AccelStepper(motorInterfaceType1, stepPin1, dirPin1); // upper and down
AccelStepper roller = AccelStepper(motorInterfaceType, stepPin, dirPin); // roller


void run_step(){
  /*if(count_1==0){
    stepper.runSpeed();
    // Set the speed in steps per second:
  // Step the motor with a constant speed as set by setSpeed():
  Serial.println("run");
  count_1++;
  }*/
  //upper up infi
  digitalWrite(upper_en,LOW);
  digitalWrite(roller_en,HIGH);
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);

}

void back_step(){
  digitalWrite(upper_en,LOW);
  digitalWrite(roller_en,HIGH);
  upper.setCurrentPosition(0);
  roller.setCurrentPosition(0);
  Serial.println("back");
  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
  while(upper.currentPosition() != -800)
  {
    upper.setSpeed(-600);
    upper.runSpeed();
  }

  digitalWrite(upper_en,HIGH);
  digitalWrite(roller_en,LOW);

  while(roller.currentPosition() != 800)
  {
    roller.setSpeed(600);
    roller.runSpeed();
  }

  digitalWrite(upper_en,HIGH);
  digitalWrite(roller_en,HIGH);
  count=0;
  count_1=0;
}

void stop_step(){
  /*stepper.setSpeed(0); 
  stepper1.setSpeed(0); */

  digitalWrite(upper_en,HIGH);
  digitalWrite(roller_en,HIGH);
}


void setup() {
///test
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);


  //set mode
  pinMode(maskButton, INPUT_PULLUP);
  
  pinMode(roundButton, INPUT_PULLUP);
  
  // Set the maximum speed in steps per second:
  upper.setMaxSpeed(1000);
  Serial.begin(9600);

  pinMode(upper_en, OUTPUT);
  pinMode(roller_en, OUTPUT);
  
  upper.setMaxSpeed(1000);
  roller.setMaxSpeed(1000);
  /*stepper.setSpeed(0);
  stepper1.setSpeed(0);
  stepper.runSpeed();
  stepper1.runSpeed();*/
  digitalWrite(upper_en,HIGH);
  digitalWrite(roller_en,HIGH);
}
void loop() {
  int state = digitalRead(maskButton);
  int buttonState = digitalRead(roundButton);
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
