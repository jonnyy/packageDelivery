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
Servo motor_B;  // create servo object to control a motor
Servo motor_C;  // create servo object to control a motor
Servo motor_D;  // create servo object to control a motor

 
int mtr_c_full_CCW = 980;
int mtr_d_full_CCW = 983;
int mtr_a_full_CCW = 978;
int mtr_b_full_CCW = 970;

//b stop = 1570 for all
int mtr_b_full_CW = 1996;
int mtr_c_full_CW = 2001;
int mtr_d_full_CW = 2011;
int mtr_a_full_CW = 2005;
int mtr_off = 1570;        // Motor off position
 
void setup() 
{ 
  motor_A.attach(3);  // attaches the A motor on pin 3 to the motor
  motor_B.attach(5);  // attaches the B motor on pin 5 to the motor
  motor_C.attach(6);  // attaches the C motor on pin 6 to the motor
  motor_D.attach(9);  // attaches the D motor on pin 9 to the motor
  
  motor_A.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value 
  motor_B.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
  motor_C.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
  motor_D.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
  
} 

void test_run();
void strafe_left();   //Keep driving to the left, do not stop
void strafe_right();  //Keep dirving to the right, do not stop
void forward();       //Keep driving forward, do not stop
void backward();      //Keep driving backward, do not stop
void move_CW();       //Keep driving clockwise, do not stop
void move_CCW();      //Keep dirving counter clockwise, do not stop
void stop_motor(char motor_label); //Stop a specific motor, or all motors


void test_run()
{
  //Motor Test Run
  motor_A.writeMicroseconds(mtr_a_full_CW);
  delay(2500);
  motor_A.writeMicroseconds(mtr_off);
  
  //Motor Test Run
  motor_B.writeMicroseconds(mtr_b_full_CW);
  delay(2500);
  motor_B.writeMicroseconds(mtr_off);
  
  //Motor Test Run
  motor_C.writeMicroseconds(mtr_c_full_CW);
  delay(2500);
  motor_C.writeMicroseconds(mtr_off);
  
  //Motor Test Run
  motor_D.writeMicroseconds(mtr_d_full_CW);
  delay(2500);
  motor_D.writeMicroseconds(mtr_off);
  
  
  
  motor_A.writeMicroseconds(mtr_a_full_CW); 
  motor_B.writeMicroseconds(mtr_b_full_CW);
  motor_C.writeMicroseconds(mtr_c_full_CW);
  motor_D.writeMicroseconds(mtr_d_full_CW);
  delay(2500);                           // waits for the motors to move
  
  motor_A.writeMicroseconds(mtr_off); 
  motor_B.writeMicroseconds(mtr_off);
  motor_C.writeMicroseconds(mtr_off);
  motor_D.writeMicroseconds(mtr_off);
  delay(2500);
}

void strafe_left()
{
  //Strafe Left Rear Wheels Drive
  motor_C.writeMicroseconds(mtr_c_full_CW);
  motor_B.writeMicroseconds(mtr_b_full_CCW);
  delay(150);  //Let the motors get started.
}

void strafe_right()
{
  //Strafe Right Rear Wheels Drive
  motor_A.writeMicroseconds(mtr_a_full_CW);
  motor_D.writeMicroseconds(mtr_d_full_CCW);
  delay(150);  //Let the motors get started.
}

void forward()
{
  //Move Forward Rear Wheels Drive
  motor_D.writeMicroseconds(mtr_d_full_CW);
  motor_C.writeMicroseconds(mtr_c_full_CCW);
  delay(150);  //Let the motors get started.
}


void backward()
{
  //Move Backward Rear Wheels Drive
  motor_B.writeMicroseconds(mtr_b_full_CW);
  motor_A.writeMicroseconds(mtr_a_full_CCW);
  delay(150);  //Let the motors get started.
}

void move_CW()
{
  //Move Count Clockwise With Opposing Wheel Drive
  motor_B.writeMicroseconds(mtr_b_full_CW);
  motor_D.writeMicroseconds(mtr_d_full_CW);
  delay(150);  //Let the motors get started.
}

void move_CCW()
{
  //Move Count Clockwise With Opposing Wheel Drive
  motor_B.writeMicroseconds(mtr_b_full_CCW);
  motor_D.writeMicroseconds(mtr_d_full_CCW);
  delay(150);  //Let the motors get started.
}



void stop_motor(char motor_label)
{
  if (motor_label == 'A')
    motor_A.writeMicroseconds(mtr_off);
  else if (motor_label == 'B')
    motor_B.writeMicroseconds(mtr_off);
  else if (motor_label == 'C')
    motor_C.writeMicroseconds(mtr_off);
  else if (motor_label == 'D')
    motor_D.writeMicroseconds(mtr_off);
  
  if (motor_label == '4')
  {
    motor_A.writeMicroseconds(mtr_off);
    motor_B.writeMicroseconds(mtr_off);
    motor_C.writeMicroseconds(mtr_off);
    motor_D.writeMicroseconds(mtr_off);
  }
  
  delay(150);  //Let the motors turn off
}


 
void loop() 
{ 
  
  test_run();
  
  strafe_left();
  delay(5000);
  stop_motor('B');
  stop_motor('C');
  delay(1000);
  
  strafe_right();
  delay(5000);
  stop_motor('A');
  stop_motor('D');
  delay(1000);
  
  forward();
  delay(5000);
  stop_motor('D');
  stop_motor('C');
  delay(1000);
  
  backward();
  delay(5000);
  stop_motor('B');
  stop_motor('A');
  delay(1000);
  
  move_CW();
  delay(750);
  stop_motor('B');
  stop_motor('D');
  delay(1000);
  
  move_CCW();
  delay(750);
  stop_motor('B');
  stop_motor('D');
  delay(1000);
  
  stop_motor('4'); //Stop all 4 just in case a mistake was made.
  

} 


