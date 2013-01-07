//LORA: Motor Control Code
//Armin Hadzic
//12/17/12
//
//HOW TO HOOK UP:
//Connect motor A control wire to pin 3
//Connect motor B control wire to pin 5
//Connect motor C control wire to pin 6
//Connect motor D control wire to pin 9
//WIRE THE MOTOR GROUND WIRES TO THE ARDUINO GROUND.
//The turning directions are based on clockwise orientation with 12 o'clock being at the claw.
//The claw is between motors A and B.

//The code is open source.

#include <Servo.h> 

//Motor Labels Correspond to the labeling on the base.
Servo motor_A;  // create servo object to control a motor
Servo motor_B;
Servo motor_C;
Servo motor_D;

 
int mtr_full_CW = 0;     // Motor full speed clockwise
int mtr_full_CCW = 179;  // Motor full speed counter clockwise
int mtr_half_CW = 45;    // Motor half speed clockwise
int mtr_half_CCW = 135;  // Motor half speed counter clockwise
int mtr_80_CW = 80;
int mtr_170_CCW = 170;
int mtr_160_CCW = 160;
int mtr_off = 90;        // Motor off position

int mtr_c_full_CCW = 980;
int mtr_d_full_CCW = 983;
int mtr_a_full_CCW = 978;
int mtr_b_full_CCW = 970;

//b stop = 1570 for all
int mtr_b_full_CW = 1996;
int mtr_c_full_CW = 2001;
int mtr_d_full_CW = 2011;
int mtr_a_full_CW = 2005;




void setup() 
{ 
  motor_A.attach(3);  // attaches the A motor on pin 3 to the motor
 
  motor_A.write(mtr_off);                  // sets the servo position according to the scaled value 
  
  motor_B.attach(5);  // attaches the A motor on pin 3 to the motor
 
  motor_B.write(mtr_off);                  // sets the servo position according to the scaled value 
  
  motor_C.attach(6);  // attaches the A motor on pin 3 to the motor
 
  motor_C.write(mtr_off);                  // sets the servo position according to the scaled value 
  
  motor_D.attach(9);  // attaches the A motor on pin 3 to the motor
 
  motor_D.write(mtr_off);                  // sets the servo position according to the scaled value 

} 

void test_run();

void test_run()
{
  //Motor C = 
  
  //Motor Test Run
  motor_A.writeMicroseconds(mtr_a_full_CW);
  delay(10000);
  motor_A.write(mtr_off);
  
  delay(15000);
  
  motor_B.writeMicroseconds(mtr_b_full_CW);
  delay(10000);
  motor_B.write(mtr_off);
  
  delay(15000);
  
  motor_C.writeMicroseconds(mtr_c_full_CW);
  delay(10000);
  motor_C.write(mtr_off);
  
  delay(15000);
  
  motor_D.writeMicroseconds(mtr_d_full_CW);
  delay(10000);
  motor_D.write(mtr_off);
}

bool stop_now = false;
 
void loop() 
{ 
  if (stop_now == false)
  {
    test_run();
    stop_now = true;
  }

} 


