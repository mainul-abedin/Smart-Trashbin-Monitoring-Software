#define BLYNK_TEMPLATE_ID "TMPL6miaqbXqi"
#define BLYNK_TEMPLATE_NAME "Blynk Smart Dustbin"
#define BLYNK_AUTH_TOKEN "gUhPbepTS18OFD1IJXlkJnQ58Y7PLUgk"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Pixel_2612";//WiFi Name//
char pass[] = "87654321";//WiFi Password//

BlynkTimer timer;

#define echoPin 32
#define trigPin 33
#include<Servo.h>
Servo servo;
long duration;
int distance; 
int binLevel=0;

void SMESensor()
{
  int ir=digitalRead(34);
  if(ir==HIGH)
  {    
    servo.write(90);
    for(int i=0; i<50; i++)
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  if(ir==LOW)
  {
    
    ultrasonic();
    delay(100);
  }
}
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
  Serial.begin(9600);
  servo.attach(13);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
   Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run();
}
