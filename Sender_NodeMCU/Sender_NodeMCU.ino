#include <SoftwareSerial.h>
SoftwareSerial s(D5,D6);

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "3fh5iD6Rxx9l7WY5qO6QSG9YI6b5ghhd";
char ssid[] = "yenbai";
char pass[] = "25319999";

int Arduino;

WidgetLED led1(V1);
WidgetLED led4(V4);
WidgetLED led5(V5);
WidgetLCD lcd(V0);
int pinValue6;
int pinValue7;
int i;

void setup() 
{
  Blynk.begin(auth, ssid, pass);
  s.begin(115200);
  Serial.begin(9600);
}

BLYNK_WRITE(V6)
{
  pinValue6 = param.asInt(); 
  if(pinValue6==1)
  {
    i = 5;
    lcd.clear();
    lcd.print(0, 0, "xin cho 10s");
    Serial.println("nut tat");
  }
  if(pinValue6==0)
  {
    i = 6;
    lcd.clear();
    lcd.print(0, 0, "xin cho 10s");
    Serial.println("nut bat");
  }
}

BLYNK_WRITE(V7)
{
  pinValue7 = param.asInt();
  if(pinValue7==1)
  {
    i = 7;
    lcd.clear();
    lcd.print(0, 0, "xin cho 10s");
    Serial.println("nut tat 30s");
  }
}
 
void loop() 
{
  Blynk.run();
  if(i==5||i==6||i==7)
  {
    s.write(i);
    delay(10000);
    lcd.clear();
    s.write(0);
    i=0;
  }
  if (s.available()>0)
  {
    Arduino=s.read();
    Serial.println(Arduino);
  }
  if (Arduino == 1) //alarm on
  {
    lcd.clear();
    lcd.print(0, 0, "bao dong chi co");
    lcd.print(0, 1, "the tat sau 10s");
    led1.on();
    s.write(0);
  }
  else if (Arduino == 2) //alarm off
  {
    s.write(0);
    led1.off();
  }
  else if (Arduino == 3) //online
  {
    s.write(0);
    led4.on();
    led5.off();
  }
  else if (Arduino == 4) //offline
  {
    s.write(0);
    led5.on();
    led4.off();
  }
  else if (Arduino == 4)
  {
    lcd.clear();
  }
  delay(1000);
  Arduino = 0;
}
