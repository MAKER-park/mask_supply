/*Example sketch to control a stepper motor with DRV8825 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
// Include the timer
#include <SimpleTimer.h>


SimpleTimer timer;
SimpleTimer timer1;

//--------------------------step---------------------------
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:

//enable pin dvr8825
#define upper_en 13//no 7 is somting wrong...
#define roller_en 8

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin1 4
#define stepPin1 3
#define motorInterfaceType1 1
// Create a new instance of the AccelStepper class:



AccelStepper upper = AccelStepper(motorInterfaceType1, stepPin1, dirPin1); // upper and down
AccelStepper roller = AccelStepper(motorInterfaceType, stepPin, dirPin); // roller

//--------------------------------------------------------------------------------------------


// set limit switch
int maskButton = A0;
int endButton = A1;
int startButton = A2;
int restartButton = A3;

//--------set pushbutton---------
boolean ledOn = false;
int roundButton = 9;
int roundLed = 11;


int triangle = 10;
int triangleLed = 12;
//--------button led---------

int count = 0;
int count_home = 0;
int count_left = 0;
int count_reset = 0;

int round_button_count = 0;

int test = 0;

void setup() {
//timer_set 500 = 0.5 sec 
  timer.setInterval(500, toggle);
  timer1.setInterval(1000, toggle1);
///test
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);


  //set mode
  /*
   * int maskButton = A0;
   * int endButton = A1;
   * int startButton = A2;
   * int restartButton = A3;
   */
  pinMode(maskButton, INPUT_PULLUP); //mask 
  pinMode(endButton, INPUT_PULLUP); // mask_rest
  pinMode(startButton, INPUT_PULLUP);// upper home
  pinMode(restartButton, INPUT_PULLUP);// reset switch
  
  
  pinMode(roundButton, INPUT_PULLUP);
  pinMode(roundLed, OUTPUT);

  pinMode(triangle, INPUT_PULLUP);
  pinMode(triangleLed, OUTPUT);
  
  // Set the maximum speed in steps per second:
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

//-----------------------------------timer-------------------------
void toggle(){
if(ledOn == true){
digitalWrite(roundLed, LOW);
}else{
digitalWrite(roundLed, HIGH);
}
ledOn = !ledOn;
}
//------------------------------------------------------


//---------------------------timer1-------------------------
void toggle1(){
if(ledOn == true){
digitalWrite(triangleLed, LOW);
}else{
digitalWrite(triangleLed, HIGH);
}
ledOn = !ledOn;
}

//--------------------------timer------------------------------


void loop() {
  //limit
  int mask = digitalRead(maskButton);
  int left = digitalRead(endButton);
  int up_home = digitalRead(startButton);
  int reset = digitalRead(restartButton);

  //button
  int buttonState = digitalRead(roundButton); //round
  int buttonState1 = digitalRead(triangle);//triangle
  //Serial.println(up_home);

//check -- input serial---------
  if (Serial.available() > 0) { //
    char ch = Serial.read(); //1byte
    //Serial.print("test_get : "); //1byte
    //Serial.println(ch);
    if(ch == 'a'){//mask supply action
      Serial.println("plz push the round button");
      round_button_count++;
    }
    else if(ch == 'r'){//run test steep motor
      Serial.println("start run test motor");
      back_step();
    }

    else if(ch == '1'){//test the button
      Serial.println("plz push the round button");
      test = 1;
    }

    else if(ch == '2'){
      Serial.println("plz push the triangle button");
      test = 2;
    }
  }

  if(test == 1){
    timer.run();
    if(buttonState == 1){
      Serial.println("push the round button");
      digitalWrite(roundLed, LOW);
      test = 0;
      }
  }
  else if(test ==2){
    timer1.run();
      if(buttonState1 == 1){
      Serial.println("push the triangle button");
      digitalWrite(triangleLed, LOW);
      test = 0;
      }
  }
  
  if(round_button_count == 1){
    timer.run();
    if(buttonState == 1){
      Serial.println("push the round button");
      round_button_count = 0;
      digitalWrite(roundLed, LOW);
      count++;
    }
  }
  if(count == 1){
  //Step the motor with a constant speed as set by setSpeed():
  Serial.println("runstep");
  digitalWrite(upper_en,LOW);
  digitalWrite(roller_en,HIGH);
  digitalWrite(dirPin1, HIGH);//set dir
  run_step();
  count++;  
  }
  if(count == 2){
    run_step();
    if(mask == 0){
      back_step();
      count_home++;
      Serial.println(count_home);
      digitalWrite(upper_en,LOW);
      digitalWrite(roller_en,HIGH);
      digitalWrite(dirPin1, LOW);//set dir
      }
     else if(left == 0){
      //Serial.println("no left mask");
      digitalWrite(upper_en,LOW);
      digitalWrite(roller_en,HIGH);
      digitalWrite(dirPin1, LOW);//set dir
      run_step();
      count_home=1;
      count_left=1;
     }
     
     if(count_home == 1){
      if(count_left == 1){
        run_step();
        if(up_home == 0){
        stop_step();
        Serial.println("home");
        //Serial.println("plz refill mask and push the reset button");
        count_reset = 1;
        }
      }
      }
  }
  if(count == 0){
   if(count_home == 1){
    run_step();
    if(up_home == 0){
      stop_step();
      Serial.println("home");
    }
   }
   if(count_reset == 1){
    Serial.println("plz refill mask and push the reset button");
    count_reset = 2;
    }
    else if(count_reset == 2){
      if(reset == 0){
        Serial.println("reset_check_supply_the_mask");
        count_reset = 0;
        count = 1;
      }
    }
  }

  
  
//------------------------------------
  
}
