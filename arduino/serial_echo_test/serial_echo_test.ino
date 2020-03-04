void setup() {
  Serial.begin(9600);    
}
void loop() {
  
  if (Serial.available() > 0) { //
    char ch = Serial.read(); //1byte
    Serial.print("test_get : "); //1byte
    Serial.println(ch);
  }
}
