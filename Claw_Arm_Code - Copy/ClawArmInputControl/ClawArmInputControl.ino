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
  
  if (val == 1)
  {
    Serial.println("Lower Claw");
    armServo.write(160);
  }
  else if (val == 2)
  {
    Serial.println("Raise Claw");
    armServo.write(50);
  }
  
  else if (val == 3)
  {
    Serial.println("Open Claw");
    clawServo.write(10);
  }
  else if (val == 4)
  {
    Serial.println("Close Claw");
    clawServo.write(60);
  }
  else if (val == 5)
  {
    clawServo.write(10);
    delay(500);
    clawServo.write(60);
    delay(500);
    clawServo.write(10);
    delay(500);
    clawServo.write(60);
    delay(500);
    clawServo.write(10);
    delay(500);
    clawServo.write(60);
    delay(500);
    clawServo.write(10);
    delay(500);
    
  }
  else if (val == 6)
  {
    Serial.println("Raise Slow Claw");
    for (int i =160; i >= 50; i=i-2)
    {
      armServo.write(i);
      delay(50);
    }
  }
  else if (val == 7)
  {
    Serial.println("Lower Slow Claw");
    for (int i =50; i <= 160; i=i+2)
    {
      armServo.write(i);
      delay(50);
    }
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
  
  
