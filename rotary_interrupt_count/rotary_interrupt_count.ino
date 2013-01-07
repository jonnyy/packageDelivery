#define encoder1PinA 2 //Pin 2 is the first interrupt pin and must be used for handling this interrupt
#define encoder1PinB 4

#define encoder2PinA 3 //Pin 3 is the second interrupt pin and must be used for handling this second interrupt
#define encoder2PinB 5

//#define encoder3PinA 6
//#define encoder3PinB 7
//
//#define encoder4PinA 8
//#define encoder4PinB 9
volatile unsigned int encoder1Pos = 0;
volatile unsigned int encoder2Pos = 0;
//volatile unsigned int encoder3Pos = 0;
//volatile unsigned int encoder4Pos = 0;


void checkChannelA(volatile unsigned int &encoderPos, int encoderPinA, int encoderPinB);
void checkChannelB(volatile unsigned int &encoderPos, int encoderPinA, int encoderPinB);


void setup() {
  pinMode(encoder1PinA, INPUT); 
  pinMode(encoder1PinB, INPUT); 
// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoder1A, CHANGE);
  attachInterrupt(1, doEncoder2, CHANGE);
// encoder pin on interrupt 1 (pin 3)
//  attachInterrupt(1, doEncoder0B, CHANGE); 
// attachInterrupt( 
  Serial.begin (9600);
}
void loop(){ //Do stuff here 
  delay(1000);
  Serial.print("Encoder 1: ");
  Serial.println(encoder1Pos, DEC);
    Serial.print("Encoder 2: ");
  Serial.println(encoder2Pos, DEC);
}
void doEncoder1A(){
  checkChannelA(encoder1Pos, encoder1PinA, encoder1PinB);
}
void doEncoder1B(){
  checkChannelB(encoder1Pos, encoder1PinA, encoder1PinB);
}

void doEncoder2(){
  checkChannelA(encoder2Pos, encoder2PinA, encoder2PinB);
}

void checkChannelA(volatile unsigned int &encoderPos, int encoderPinA, int encoderPinB){
    // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {  
      encoderPos = encoderPos + 1;         // CW
    } 
    else {
      encoderPos = encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoderPinB) == HIGH) {   
      encoderPos = encoderPos + 1;          // CW
    } 
    else {
      encoderPos = encoderPos - 1;          // CCW
    }
  }
}

void checkChannelB(volatile unsigned int &encoderPos, int encoderPinA, int encoderPinB){
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {  
      encoderPos = encoderPos + 1;         // CW
    } 
    else {
      encoderPos = encoderPos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoderPinA) == LOW) {   
      encoderPos = encoderPos + 1;          // CW
    } 
    else {
      encoderPos = encoderPos - 1;          // CCW
    }
  }  
}
