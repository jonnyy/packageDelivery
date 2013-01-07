// Color Match
// by Jonathan Lutz

int pwmrgb[] = {11, 9, 10}; //sets the r,g,b cathode pins for the pwm led (must be pwm pins)
int rgbbias[] = {50, -20, -20};//110, 15, 0 //sets the bias for the illuminated RGB LED: higher number = less intense (max 255)

int rgbds[] = {255, 255, 255};
int maxwhite[] = {863, 753, 442};//{500, 493, 480};//{773, 624, 542};
int minblack[] = {606, 419, 431};//{337, 308, 305};//{309, 134, 104};

int sensorValue = 0;

int speed = 50;

void setup(){
  pinMode(2, OUTPUT); //sensor red cathode
  pinMode(3, OUTPUT); //sensor green cathode
  pinMode(4, OUTPUT); //sensor blue cathode
  Serial.begin(9600);
  for(int i = 2; i < 5; i++){ 
    digitalWrite(i, HIGH); analogWrite(pwmrgb[i-2], rgbds[i-2]); 
  } 
} 

void loop(){ 
  int switchstate = analogRead(A5); 
  if(switchstate > 1000){
    for(int i = 2; i < 5; i++){
      digitalWrite(i, HIGH);
      analogWrite(pwmrgb[i-2], 255);
    }
    delay(1000);
    switchstate = analogRead(A5);
    while(switchstate < 1000){
      switchstate = analogRead(A5);
    }
    delay(500);
  }

  for(int i = 0; i < 3; i++){
    delay(100);
    digitalWrite(i + 2, LOW);
    delay(100);
    sensorValue = analogRead(A0);
    rgbds[i] = constrain(sensorValue, minblack[i], maxwhite[i]);
    rgbds[i] = map(rgbds[i], minblack[i], maxwhite[i], 0, 255);
    if(i==0){
      Serial.print("RED: ");
      Serial.println(sensorValue);
    }
    else if(i==1){
      Serial.print("GREEN: ");
      Serial.println(sensorValue);
    }
    else{
      Serial.print("BLUE: ");
      Serial.println(sensorValue);
    }
    rgbds[i] = (255 + rgbbias[i]) - rgbds[i];
    rgbds[i] = constrain(rgbds[i], 0, 255);
    digitalWrite(i + 2, HIGH);
  }

  for(int i = 0; i < 3; i++){
    analogWrite(pwmrgb[i], rgbds[i]);
  }
  delay(speed);
}
