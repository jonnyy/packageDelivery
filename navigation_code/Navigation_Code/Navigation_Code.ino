/*
Armin Hadzic
Team 08: LORA
12/28/12
This code is open source.
*/

#include <DistanceGP2Y0A21YK.h>
#include <Servo.h>

////////////////////////////////////////////////////////////////////////////////////////
//PINOUT:
//A0: IR sensor output
//D10: Servo Control
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
//ASSUMPTIONS:
//1. The robots rear face (opposite of the claw) is facing the pick up wall
//2. The IR Sensor is pointed towards the claw direction when the servo is at 0 degrees
//3. The color sensor facing the ground can detect beyond the edge of the 10in robot
//   boundary.
//4. !!!!! The IR sensor's servo needs to be mounted below the base, and the base should
//         should have a hole for the IR sensor shaft to go through the base.  (why?)
//         The walls are 3.5inches tall and the robot is roughly 2in off the ground
//         so for the IR sensor to measure properly, it must only be mounted one inch
//         above the base.  As a result, the system CANNOT MEASURE IN FRONT OF THE ROBOT
//         due to the claw and measurement system obstructing the sensor.
////////////////////////////////////////////////////////////////////////////////////////

 
////////////////////////////////////////////////////////////////////////////////////////
//Globals
Servo myservo;              //Create servo object to control a servo 
DistanceGP2Y0A21YK Dist;
DistanceGP2Y0A21YK ShortRngDist;  //One of the short range IR sensors
int DISTANCE = 99999;
int SERVO_ANGLE = 0;        //Half of the output servo angle
bool start_up = true;
char current_box = 'n';     //Holds the current box type
                  //n = none
                  //a = air
                  //s = sea
                  //r = rail
char current_servo_pos = 'B';    //For testing purposes and crisis control
                  //F = foward   (0 degrees)  OBSOLETE
                  //R = right    (90 degrees)
                  //B = backward (180 degrees)
                  //L = left     (270 degrees)
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
//Prototypes:
void railDropoff();
void seaDropoff();
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
//Function: Rail Drop Off
void railDropoff()
{
  //First, set the IR sensor to the rear position, to measure the distance between the robot and the sea zone wall (left wall).
  SERVO_ANGLE = 90;                            // 180 *.5 = 90 (since the servo can only go from 0 to 180          
  myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
  delay(150);                                  // Waits for the servo to get there 
  current_servo_pos = 'B'; 
  
  //Move to the front edge of the rail drop-off zone (5in rail drop cell size + 5in half the robot size + one inch rotation buffer space)
  DISTANCE = Dist.getDistanceCentimeter();
  while(DISTANCE >= 11)
  {
    move_backward();
    DISTANCE = Dist.getDistanceCentimeter();
  }
  stop_moving(); 
  
  //Move the IR sensor to the right (135 degrees) to measure the distance to far right wall as a reference to the rail zone
  SERVO_ANGLE = 45;                           // The gear mechanism doubls the servo angle, so 1/2*90 = 45 or 45 for this setup
  myservo.write(SERVO_ANGLE);                 // Sets the servo position according to the scaled value 
  delay(150);                                 // Waits for the servo to get there  
  current_servo_pos = 'R';
  
  
  //Move to the right edge of the rail zone.
  DISTANCE = Dist.getDistanceCentimeter();
  while(DISTANCE >= 32)
  {
    move_right();
    DISTANCE = Dist.getDistanceCentimeter();
  }
  stop_moving(); 
  
  
  //Next, rotate such that the claw face is facing the rail zone wall
  rotate_clkwise_180();
  stop_moving();
  
  //Move slightly closer to the rail zone, so the ground color sensor can measure the floor colors
  //5in for the rail cell length + 5in for half the robot's length = 10in
  DISTANCE = ShortRngDist.getDistanceCentimeter();
  while(DISTANCE >= 10)
  {
    slow_move_forward();
    DISTANCE = ShortRngDist.getDistanceCentimeter();
  }
  stop_moving();
  
  //Move the IR sensor to the left (270 degrees) to measure the distance to the far right wall, in case the robot has to retry the rail drop-off
  SERVO_ANGLE = 135;                           // The gear mechanism doubls the servo angle, so 1/2*270 = 135 or 135 for this setup
  myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
  delay(150);                                  // Waits for the servo to get there 
  current_servo_pos = 'L' 
  
  
  //A different approach is used to creep down the line of cells for the rail zone, than was used
  //for the sea or pick-up zones.  The reasoning is because the rail zone is so far from the left and right walls,
  //that it is only possible to move the robot to 3 of the 6 cells since the sensor used has an accuracy of
  //up to 40in (and going to the limit is not wise either).
  //Instead, the white lines will be counted to track the robot's progression from cell to cell.  The method
  //is more prone to error due to the unpredicatable nature of the robot's movement, but it is the best approach
  //given the situation.
  
  bool new_start = true;
  int cell_found = 0;
  while(current_box != 'n')
  {
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
    measure_floor_color();
    
    if(new_start == true)
    {
      //First ensure that the robot's floor color sensor is measuring a white line
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
      if(floor_color == black_color_range)
      {
          //Drive to the right until a white line is found.
        
          //Move to the right edge of the rail zone.
          /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
          measure_floor_color();
          while(floor_color != white_color_range)
          {
            move_right();
            /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
            measure_floor_color();
          }
          stop_moving(); 
          new_start = false;
      }
    }
    
    //Next, move to the right until the floor sensor does not recognize the white line
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
    measure_floor_color();
    while(floor_color == white_color_range)
    {
      slow_move_right();
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
      measure_floor_color();
    }
    stop_moving(); 
    ++cell_found;
    
    //Check if the current cell matches the coloring of the block.  If it does not,
    //keep driving until the next white line is reached.
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
    measure_floor_color();
    if(blk_color_range == floor_color_range)
    {
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!DAKOTA's LIFTING CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
      drop_box();
      current_box = 'n';
    }
    else
    {
      //Should the robot have reached the 6th cell and still not found the correct color,
      //move the robot back to the right edge of the rail zone and try again.
      
      if(cell_found != 6)
      {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
        measure_floor_color();
        while(floor_color != white_color_range)
        {
          slow_move_right();
          measure_floor_color();
        }
        stop_moving(); 
      }
      else
      { 
        //Since 6 cells have been found, and none of them have been a match:
        //Move to the right edge of the rail zone.
        DISTANCE = Dist.getDistanceCentimeter();
        while(DISTANCE >= 32)
        {
          slow_move_right();
          DISTANCE = Dist.getDistanceCentimeter();
        }
        stop_moving(); 
        cell_found = 0; 
        new_start = true;
      }
    }
    
  }
  
  //The box has been dropped off, now the robot needs to prepare itself to go back to the pick-up zone.
  
  //First, back up a little to avoid nudging any already placed boxes
  //5in for the rail cell length + 5in for half the robot's length + 2in buffer space = 12in
  DISTANCE = ShortRngDist.getDistanceCentimeter();
  while(DISTANCE <= 12)
  {
    slow_move_backward();
    DISTANCE = ShortRngDist.getDistanceCentimeter();
  }
   stop_moving();
  
  //Next, the robot needs to move back to the bottom left area of the course in order to be allowed to move back to the
  //pick-up zone properly.
  
  //Move to IR sensor to the right such that it can measure the distance from the robot to the left course wall.
  SERVO_ANGLE = 45;                           // The gear mechanism doubls the servo angle, so 1/2*90 = 45 or 45 for this setup
  myservo.write(SERVO_ANGLE);                 // Sets the servo position according to the scaled value 
  delay(150);                                 // Waits for the servo to get there  
  current_servo_pos = 'R';
  
  //Move to 12in from the left wall.
  DISTANCE = Dist.getDistanceCentimeter();
  while(DISTANCE >= 12)
  {
    move_right();
    DISTANCE = Dist.getDistanceCentimeter();
  }
  stop_moving(); 
  
  //The robot is now ready to start the pick-up process again. 
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
//Function: Sea Drop Off
void seaDropoff()
{
    //First, rotate the robot such that its rear face (the face opposite the claw) is facing the left wall (sea zone wall)
    rotate_clkwise_90();
    stop_moving();
    
    //The rear end of the robot should now be facing the left wall (sea zone wall)
    
    //Set the IR sensor to the rear position, to measure the distance between the robot and the sea zone wall (left wall).
    SERVO_ANGLE = 90;                            // 180 *.5 = 90 (since the servo can only go from 0 to 180          
    myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
    delay(150);                                  // Waits for the servo to get there 
    current_servo_pos = 'B'; 
    
    //Move to the edge of the sea drop-off zone (4in sea drop cell size + 5in half the robot size + one inch rotation buffer space)
    DISTANCE = Dist.getDistanceCentimeter();
    while(DISTANCE >= 10)
    {
      move_backward();
      DISTANCE = Dist.getDistanceCentimeter();
    }
    stop_moving(); 
    
    //Next, rotate 180 degrees such that the claw face is facing the sea drop zone
    rotate_clkwise_180();
    stop_moving();
    
    //Move slightly closer to the sea zone, so the ground color sensor can measure the floor colors
    DISTANCE = ShortRngDist.getDistanceCentimeter();
    while(DISTANCE >= 9)
    {
      slow_move_forward();
      DISTANCE = ShortRngDist.getDistanceCentimeter();
    }
    stop_moving(); 
    
    
    //Move the IR sensor to the right (135 degrees) to measure the distance from the pick-up wall and the robot's current position.
    //It is used to scoot down the sea drop-off zone one cell at a time(and rotating it to the left would exceed the sensor's range).
    SERVO_ANGLE = 45;                           // The gear mechanism doubls the servo angle, so 1/2*90 = 45 or 45 for this setup
    myservo.write(SERVO_ANGLE);                 // Sets the servo position according to the scaled value 
    delay(150);                                 // Waits for the servo to get there  
    current_servo_pos = 'R';
    
    //Next, search for the correct color match by going down the row one cell at a time
    int distance_from_wall = 10;  //starting distance from the left wall
    while(current_box != 'n')
    {
      //read floor color
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
      measure_floor_color();
      if(blk_color_range == floor_color_range)
      {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!DAKOTA's LIFTING CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
        drop_box();
        current_box = 'n';
      }
      else
      {
        //The correct color was not found in the current cell, move down one cell
        distance_from_wall += 3;
        
        //If the distance from the wall is less than 25 then the robot has not gone through all of the sea cells,
        //as such just move down to the next cell, since the correct color match was not yet found.
        //Otherwise, a measuring error probably occured, so move the robot back to the top of the sea zone and try
        //again.
        if(distance_from_wall < 25)
        {
          DISTANCE = Dist.getDistanceCentimeter();
          while(DISTANCE <= distance_from_wall)
          {
            slow_move_left();
            DISTANCE = Dist.getDistanceCentimeter();
          }
          stop_moving(); 
        }
        else
        {
          distance_from_wall = 10;
          DISTANCE = Dist.getDistanceCentimeter();
          while(DISTANCE >= distance_from_wall)
          {
            slow_move_right();
            DISTANCE = Dist.getDistanceCentimeter();
          }
          stop_moving(); 
        }
        
      }
      
    }
    
    //Move far enough away from the blocks so that the robot can rotate back to having its rear face the pick-up zone, so that  it is ready to restart the process.
    //Move slightly closer to the sea zone, so the ground color sensor can measure the floor colors
    DISTANCE = ShortRngDist.getDistanceCentimeter();
    while(DISTANCE <= 5)
    {
      slow_move_backward();
      DISTANCE = ShortRngDist.getDistanceCentimeter();
    }
    stop_moving(); 
    
    //Now rotate so the rear faces the pick-up zone
    rotate_cntrClkwise_90();
    stop_moving();
    
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Dist.begin(A0);      // Set the IR sensor to pin A0
  myservo.attach(10);  // Set the servo to pin 10
  myservo.write(90);
  current_servo_pos = 'B';
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  
  ////////////////////////////////////////////////////////////
  //NAVIGATION
  ////////////////////////////////////////////////////////////
  
  
  //Initialize servo to 180 degrees rear position
  SERVO_ANGLE = 90;                            // 180 *.5 = 90 (since the servo can only go from 0 to 180          
  myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
  delay(150);                                  // Waits for the servo to get there 
  current_servo_pos = 'B'; 
  
  //First: align the robot with the left wall
  if(start_up == true)
  {
    while (left_bumper == false)
    {
      slow_move_left();
    }
    stop_moving();
    start_up = false;
  }
  
  
  //Second: move to the pick-up zone area
  
  //Move towards the pick up wall until 6in (+5in from the robot frame) or roughly 11in from the sensor is reached
  DISTANCE = Dist.getDistanceCentimeter();
  while(DISTANCE >= 11)
  {
    move_backward();
    DISTANCE = Dist.getDistanceCentimeter();
  }
  stop_moving();
  
  //Now rotate the robot 180 degrees so the claw is facing the pick-up wall
  rotate_clkwise_180();
  stop_moving();
  
  
  //Third: move to the right to be in front of the pick-up zone
  
  //Move the IR sensor to the left (270 degrees) to measure the distance to the pick up zone to the right of the robot
  SERVO_ANGLE = 135;                           // The gear mechanism doubls the servo angle, so 1/2*270 = 135 or 135 for this setup
  myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
  delay(150);                                  // Waits for the servo to get there 
  current_servo_pos = 'L' 
 
  //Move 12in to the right (+5in from the robot frame) or roughly 17in from the sensor (centers the robot with the first box)
  DISTANCE = Dist.getDistanceCentimeter();
  while(DISTANCE <= 17)
  {
    move_right();
    DISTANCE = Dist.getDistanceCentimeter();
  }
  stop_moving();
  
  int desired_distance = 17;  //starting distance from the left wall
  while (current_box == 'n')
  {
    //Fourth: align the robot with the box
  
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PHILIP's ALIGNMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
  
  
    //Fifth: pick up the box, measure its size and color
  
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!DAKOTA's LIFTING CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's SIZE MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JONATHAN's COLOR MEASUREMENT CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/ 
  
    //ASSUMPTION: assuming that Dakota and Jonathan's functions will drop the box and lift the claw if it is an air box, and assign current_box = 'a'
    //            and if the boxes are sea or rail they set current_box to the appropriate value('s' and 'r' respectively).
    if(current_box == 'a')
    {
      //Move right by 3in + current distance and measure again
      desired_distance += 3;
      
      DISTANCE = Dist.getDistanceCentimeter();
      while(DISTANCE <= desired_distance)
      {
        if (current_servo_pos == 'L')
        {
          slow_move_right();
        }
        else
        {
          slow_move_left();
        }
          
        DISTANCE = Dist.getDistanceCentimeter();
      }
      stop_moving();
      current_box = 'n';
      continue;
    }
    
    //Every 7 zones the distance sensor must switch to measuring distance from the left instead of the right, due to range constraints of the sensor.
    //initial diatance (14in) + (7 zones * 3in) = 35in  (40in is max range)
    //In case of an error, where the robot has passed through all 14 blocks, the robot can go back to creeping from the left edge
    if((desired_distance >= 35) && (current_box == 'n')) 
    {
      desired_distance = 17;                      //reset starting distance from the right wall
      if (current_servo_pos == 'L')
      {
        //Move the IR sensor to the right (135 degrees) to measure the distance to the pick up zone to the right of the robot
        SERVO_ANGLE = 45;                           // The gear mechanism doubls the servo angle, so 1/2*90 = 45 or 45 for this setup
        myservo.write(SERVO_ANGLE);                 // Sets the servo position according to the scaled value 
        delay(150);                                 // Waits for the servo to get there  
        current_servo_pos = 'R';
        
        //Move to the right edge of the pick-up zone
        DISTANCE = Dist.getDistanceCentimeter();
        while(DISTANCE >= desired_distance)
        {
          slow_move_right();
          DISTANCE = Dist.getDistanceCentimeter();
        }
        stop_moving();  
      }
      else
      {
        //Move the IR sensor to the left (270 degrees) to measure the distance to the pick up zone to the right of the robot
        SERVO_ANGLE = 135;                           // The gear mechanism doubls the servo angle, so 1/2*270 = 135 or 135 for this setup
        myservo.write(SERVO_ANGLE);                  // Sets the servo position according to the scaled value 
        delay(150);                                  // Waits for the servo to get there 
        current_servo_pos = 'L';
        
        //Move to the left edge of the pick-up zone
        DISTANCE = Dist.getDistanceCentimeter();
        while(DISTANCE >= desired_distance)
        {
          slow_move_left();
          DISTANCE = Dist.getDistanceCentimeter();
        }
        stop_moving(); 
      }
    
    }
  }
    
    
  //Sixth: the rail or sea boxes
  
  //first, move the robot away from the boxes using a calibrated nudge
  //6in for pick up zone + one inch for rotation room + 5in for half the robot base size = 12in
  DISTANCE = ShortRngDist.getDistanceCentimeter();
  while(DISTANCE <= 12)
  {
    slow_move_backward();
    DISTANCE = ShortRngDist.getDistanceCentimeter();
  }
  stop_moving(); 
  
  if(current_box == 'r')
  {
    railDropoff();
  }
  
  else if (current_box == 's')
  {
    seaDropoff();
  }
  
  //LAST: the robot has returned to the left most edge of the pick up zone, and it repeats the process again.
}
////////////////////////////////////////////////////////////////////////////////////////
