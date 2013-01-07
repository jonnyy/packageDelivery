#include <Servo.h>
Servo myservo;
void setup(){
  myservo.attach(9);
  
  Serial.begin(9600);
}
void loop(){
  myservo.write(0);
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
