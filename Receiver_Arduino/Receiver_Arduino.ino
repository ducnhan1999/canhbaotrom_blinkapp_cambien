#include <SoftwareSerial.h>
SoftwareSerial s(2,3);

const int infrared = 5; //pin digital cam bien nhiet
const int InfraredPin = 4; //pin digital chuyen dong
const int Buzzer = 6; //pin coi bao dong

bool state = true;
int mcu;
int i;

void setup() 
{
  pinMode(InfraredPin, INPUT);
  pinMode(infrared, INPUT_PULLUP);
  //pinMode(Buzzer, OUT);
  s.begin(115200);
  Serial.begin(9600);
}
 
void loop() 
{
  //chuyen dong
  if(digitalRead(InfraredPin)==HIGH && state == true)
  {
    //digitalWrite(Buzzer, HIGH);
    s.write(1);
    Serial.println("chuyendong");
    mcu = 0;
  }
  
  //hong ngoai
  if(digitalRead(infrared) == 0 && state == true)
  {
    //digitalWrite(Buzzer, HIGH);
    Serial.println("hongngoai");
    s.write(1); 
    mcu = 0;
  }
  mcu=s.read();
  Serial.println(mcu);
  if(mcu == 5)
  {
    digitalWrite(Buzzer, LOW);
    Serial.println("nut tat");
    state = false;
    s.write(2);
    s.write(4);
    mcu = 0;
  }
  if(mcu == 6)
  {
    state = true;
    Serial.println("bat");
    s.write(3);
    delay(1000);
    mcu = 0;
  }
  if(mcu == 7)
  {
    digitalWrite(Buzzer, LOW);
    Serial.println("nut tat 30s");
    state = false;
    s.write(2);
    s.write(4);
    delay(30000);
    state == true;
    Serial.println("bat");
    s.write(3);
    mcu = 0;
  }
  delay(5000);
  s.write(9);
}
