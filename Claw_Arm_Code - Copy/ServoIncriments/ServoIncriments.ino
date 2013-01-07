//Include the Servo Library
//Create a Servo Object
#include <Servo.h>
Servo dakotasServo;

//Define the Pins
int servoPin = 9;

void setup ()
{
  //"Attach" The Servo Object
  // We don't need to set it as an output manually
  dakotasServo.attach(servoPin);
  
}

void loop()
{
  //Let's Turn the Servo from 0 to 180
  //in increments of 20 degrees
  for (int i =0; i <=80; i=i+20)
  {
    dakotasServo.write(i);
    delay(1000);
  }
  
}
