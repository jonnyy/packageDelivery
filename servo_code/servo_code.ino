//LORA: Servo Code
//HOW TO HOOK UP:
//Connect the servo control to pin 9
//WIRE THE SERVO GROUND WIRE TO THE ARDUINO GROUND.
//The servo can turn from 0 to 179 degrees.

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo
} 
 
void loop() 
{ 
  val = rand()%179; //0 to 179 is allowed
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(150);                           // waits for the servo to get there 
} 
