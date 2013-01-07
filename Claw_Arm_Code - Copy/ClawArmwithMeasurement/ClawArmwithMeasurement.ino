//Include the Servo Library
#include <Servo.h>

//Create Servo Objects
Servo clawServo;
Servo armServo;

//Define Pins
int servoPin1 = 9;
int servoPin2 = 10;

void setup ()
{
  //"Attach" The Servo Object 
  clawServo.attach(servoPin1);
  armServo.attach(servoPin2);
  
  //Initial the Serial Window
  Serial.begin(9600);
}

void loop ()
{
  //Wait to receive input
  while (Serial.available() == 0);
  
  //Read the Input
  int val = Serial.read() - '0';
  
  //Output Command List
  Serial.println("Command List");
  Serial.println("1 - Pick Up Block");
  Serial.println("2 - Test Measurement");
  Serial.println("3 - React to Measurement Data");
  Serial.println("4 - Deliver Block");
  
  //Pick up a Block
  if (val == 1)
  {
    Serial.println("Pick Up Block");
    clawServo.write(10);
    delay(500);
    armServo.write(160);
    delay(500);
    clawServo.write(60);
    delay(500);
    armServo.write(50);
  }
  
  //Measure the Block
  else if (val == 2)
  {
    Serial.println("Block Measurement");
    int value = analogRead(A1);
  if(value >= 1000){
    Serial.println("NO BOX");
  }
  else if(value <= 550 && value >= 470){
    Serial.println("Air Box");
  }
  else if(value >= 190 && value <= 230){
    Serial.println("Sea Box");
  }
  else if(value >= 50 && value <= 90){
    Serial.println("Rail Box");
  }
  else{
    Serial.println("WTF");
  }
  Serial.println(value);
  delay(1000);
  }
  
  //Intepret Measurement and React
  else if (val == 3)
  {
    Serial.println("React to Measurement Data");
    int mval = analogRead(A1);
    if(mval <= 1000 && mval >= 250)
    {
      Serial.println("Air or Error: Return Box");
      armServo.write(160);
      delay(500);
      clawServo.write(10);
      delay(500);
      armServo.write(50);
      delay(500);
    }
    else
    {
      while (Serial.available() == 0);
    }
    
  }
  
  //Deliver Block
  else if (val == 4)
  {
    Serial.println("Delivering Block");
    armServo.write(160);
      delay(500);
      clawServo.write(10);
      delay(500);
      armServo.write(50);
      delay(500);
  }
  else
  {
    Serial.println("Invalid!");
  }
  
  Serial.flush();
  
  /*
  //Echo the input
  Serial.println(val);
  */
  
}
  
  
