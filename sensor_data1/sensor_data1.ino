

int sensorPin = A0;
int avg;
float sensorValue = 0;

void setup() 
  {
  Serial.begin(9600);
  }

void loop() 
  {
    avg = 0;
  for (int i=0; i <= 9; i++){
      avg = avg + analogRead(sensorPin);
   } 
  sensorValue = avg / 10;

    
    sensorValue = (2914 / (sensorValue + 5)) - 1;
    sensorValue = map(sensorValue, 3, 40, 0, 255);
    Serial.println(sensorValue);
    
    
    delay (200);
  }
