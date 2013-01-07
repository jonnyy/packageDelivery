//Jonathan Lutz
//Rotary Encoder

int state, prevstate = 0, count = 0;
int nextEncoderState[4] = { 2, 0, 3, 1 };
int prevEncoderState[4] = { 1, 3, 0, 2 };

void setup()
{
  pinMode(7, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  Serial.begin(9600);  
}

void loop()
{
  state = (digitalRead(7) << 1) | digitalRead(5);
  if (state != prevstate) {
    if (state == nextEncoderState[prevstate]) {
       count++;
    } else if (state == prevEncoderState[prevstate]) {
       count--; 
    }
    Serial.println(count, DEC); 
    prevstate = state;
  }
}
