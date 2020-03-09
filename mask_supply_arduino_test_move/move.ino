
void run_step(){
  /*if(count_1==0){
    stepper.runSpeed();
    // Set the speed in steps per second:
  // Step the motor with a constant speed as set by setSpeed():
  Serial.println("run");
  count_1++;
  }*/
  //upper up infi
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(800);

}

void back_step(){//supply the mask action
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
  Serial.println("mask supply done");
}

void stop_step(){
  /*stepper.setSpeed(0); 
  stepper1.setSpeed(0); */

  digitalWrite(upper_en,HIGH);
  digitalWrite(roller_en,HIGH);
  count_home=0;
  count=0;
  count_left=0;
}
