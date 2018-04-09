
#include <TinkerKit.h>
#include <Servo.h> 


#include "DHT.h"
#include<string.h>
byte buff[2];
int pin = 8;//DSM501A input D8
unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

DHT dht;
TKLightSensor ldr(I0);
Servo myservo;
int p = 0;
int brightnessVal = ldr.read();
int N=5;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  myservo.attach(9);
  dht.setup(I1); // data pin 2
  pinMode(8,INPUT);
  starttime = millis();
}

void loop()
{
  
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy += duration;
  endtime = millis();
  if ((endtime-starttime) > sampletime_ms)
  {
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    brightnessVal = ldr.read();

    //Serial.print(dht.getStatusString());
    //Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t");
    Serial.print(temperature, 1);
    Serial.print("\t");
    Serial.print(brightnessVal);
    Serial.print("\t");
    ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);  
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    float ppmv=(((concentration*0.0283168/100) *  (0.08205*temperature)/0.01));
    Serial.println(ppmv);
    //Serial.print("\n");
 
    lowpulseoccupancy = 0;
    starttime = millis();
  }
  //else Serial.print("\n");
}
  

void rozwin(){
    p=0;
    myservo.attach(9);
    for(int pos = 0; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15*N);                      // waits 15ms for the servo to reach the position 
      p++;
    } 
    myservo.detach();
}

void zwin(){
    myservo.attach(9);
    for(int pos = p; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15*N);                       // waits 15ms for the servo to reach the position 
    } 
    myservo.detach();
    p=0;
}

