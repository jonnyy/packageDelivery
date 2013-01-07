//LORA: Movement and Correction
//Jonathan Lutz
//1/7/12
//HOW TO HOOK UP: (USE ARDUINO MEGA 2560)
//Connect encoder A to have a control at pin 2, and the other at pin 22
//Connect motor A control wire to pin 4
//Connect encoder B to have a control at pin 3, and the other at pin 24
//Connect motor B control wire to pin 5
//TODO: check this for pins 18 and 19 for the encoders
//Connect encoder C to have a control at pin 21??? and the other at pin 26
//Connect motor C control wire to pin 6
//Connect encoder D to have a control pin at 20??? and the other at pin 28
//Connect motor D control wire to pin 7
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

//Motor Constants
#define maxCWSpeed 2000
#define maxCCWSpeed 1000
//TODO: Shouold probably only need one of these since we will be adjusting on the fly
#define mtr_c_full_CCW 980
#define mtr_d_full_CCW 983
#define mtr_a_full_CCW 978
#define mtr_b_full_CCW 970

//b stop = 1570 for all
#define mtr_b_full_CW 1996
#define mtr_c_full_CW 2001
#define mtr_d_full_CW 2011
#define mtr_a_full_CW 2005
#define mtr_off 1570        // Motor off position

//Encoder Constants
#define fullRotation 160
#define encoderAPin1 2 //Pin 2 is the first interrupt pin and must be used for handling this interrupt
#define encoderAPin2 22
#define encoderBPin1 3 //Pin 3 is the second interrupt pin and must be used for handling this second interrupt
#define encoderBPin2 24
#define encoderCPin1 21
#define encoderCPin2 26
#define encoderDPin1 20
#define encoderDPin2 28
#define balancePin   19

volatile int encoderAPos = 0;
volatile int encoderBPos = 0;
volatile int encoderCPos = 0;
volatile int encoderDPos = 0;
 
void setup() 
{ 
  motor_A.attach(4);  // attaches the A motor on pin 3 to the motor
  motor_B.attach(5);  // attaches the B motor on pin 5 to the motor
  motor_C.attach(6);  // attaches the C motor on pin 6 to the motor
  motor_D.attach(7);  // attaches the D motor on pin 9 to the motor
  
  motor_A.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value 
  motor_B.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
  motor_C.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
  motor_D.writeMicroseconds(mtr_off);                  // sets the servo position according to the scaled value
 
  pinMode(encoderAPin1, INPUT); 
  pinMode(encoderAPin2, INPUT);
  pinMode(encoderBPin1, INPUT); 
  pinMode(encoderBPin2, INPUT);
  pinMode(encoderCPin1, INPUT); 
  pinMode(encoderCPin2, INPUT);
  pinMode(encoderDPin1, INPUT); 
  pinMode(encoderDPin2, INPUT); 
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);
  attachInterrupt(2, doEncoderC, CHANGE);
  attachInterrupt(3, doEncoderD, CHANGE);
  attachInterrupt(4, balance, CHANGE);
  Serial.begin (9600); 
} 
//Motor prototypes
void test_run();
void strafe_left();   //Keep driving to the left, do not stop
void strafe_right();  //Keep dirving to the right, do not stop
void forward();       //Keep driving forward, do not stop
void backward();      //Keep driving backward, do not stop
void move_CW();       //Keep driving clockwise, do not stop
void move_CCW();      //Keep dirving counter clockwise, do not stop
void stop_motor(char motor_label); //Stop a specific motor, or all motors
void slowMotor(Servo motor);
void speedUpMotor(Servo motor);

//Encoder Prototypes
void checkPin1(volatile int &encoderPos, int encoderPinA, int encoderPinB);
void checkPin2(volatile int &encoderPos, int encoderPinA, int encoderPinB);
 
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

//Encoder interrupt counters
//the encoderPos if statements may need to be more sophisticated in the future if we want to do 2 wheel balance
void doEncoderA(){
  checkPin1(encoderAPos, encoderAPin1, encoderAPin2);
  if(encoderAPos % fullRotation){
   if(((encoderAPos/fullRotation)%2) == 1){
    digitalWrite(balancePin, HIGH);
   }
   else{
     digitalWrite(balancePin, LOW);
   }
  }
}
void doEncoderB(){
  checkPin1(encoderBPos, encoderBPin1, encoderBPin2);
  if(encoderAPos % fullRotation){
   if(((encoderAPos/fullRotation)%2) == 1){
    digitalWrite(balancePin, HIGH);
   }
   else{
     digitalWrite(balancePin, LOW);
   }
  }
}
void doEncoderC(){
  checkPin1(encoderCPos, encoderCPin1, encoderCPin2);
  if(encoderAPos % fullRotation){
   if(((encoderAPos/fullRotation)%2) == 1){
    digitalWrite(balancePin, HIGH);
   }
   else{
     digitalWrite(balancePin, LOW);
   }
  }
}
void doEncoderD(){
  checkPin1(encoderDPos, encoderDPin1, encoderDPin2);
  if(encoderAPos % fullRotation){
   if(((encoderAPos/fullRotation)%2) == 1){
    digitalWrite(balancePin, HIGH);
   }
   else{
     digitalWrite(balancePin, LOW);
   }
  }
}

void balance(){
  int average = (abs(encoderAPos) + abs(encoderBPos) + abs(encoderCPos) + abs(encoderDPos))/4;
  if(encoderAPos > average){
    slowMotor(motor_A);
  }
  else if(encoderAPos < average){
    speedUpMotor(motor_A);
  }
  
  if(encoderBPos > average){
    slowMotor(motor_B);
  }
  else if(encoderBPos < average){
    speedUpMotor(motor_B);
  }
  
  if(encoderCPos > average){
    slowMotor(motor_C);
  }
  else if(encoderCPos < average){
    speedUpMotor(motor_C);
  }
  
  if(encoderDPos > average){
    slowMotor(motor_D);
  }
  else if(encoderDPos < average){
    speedUpMotor(motor_D);
  }
}

//FUNCTIONS

//Motor Functions
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

void slowMotor(Servo motor){
  int currentVal = motor.readMicroseconds();
  if(currentVal > 1500){
    motor.writeMicroseconds(currentVal - 10);
  }  
  else if(currentVal < 1500){
    motor.writeMicroseconds(currentVal + 10);
  }
}
void speedUpMotor(Servo motor){
  int currentVal = motor.readMicroseconds();
  if(currentVal > 1500 && currentVal < maxCWSpeed){
    motor.writeMicroseconds(currentVal + 10);
  }  
  else if(currentVal < 1500 && currentVal > maxCCWSpeed){
    motor.writeMicroseconds(currentVal - 10);
  }
}


//Encoder functions
void checkPin1(volatile int &encoderPos, int encoderPin1, int encoderPin2)
{
  // look for a low-to-high on channel A
  if (digitalRead(encoderPin1) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPin2) == LOW) {  
      encoderPos = encoderPos + 1;         // CW
    } 
    else {
      encoderPos = encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoderPin2) == HIGH) {   
      encoderPos = encoderPos + 1;          // CW
    } 
    else {
      encoderPos = encoderPos - 1;          // CCW
    }
  }
}

//TODO: may not be needed
void checkPin2(volatile int &encoderPos, int encoderPin1, int encoderPin2)
{
  // look for a low-to-high on channel B
  if (digitalRead(encoderPin2) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoderPin1) == HIGH) {  
      encoderPos = encoderPos + 1;         // CW
    } 
    else {
      encoderPos = encoderPos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoderPin1) == LOW) {   
      encoderPos = encoderPos + 1;          // CW
    } 
    else {
      encoderPos = encoderPos - 1;          // CCW
    }
  }  
}
