#include "HX711.h"
#include <math.h>

#define LOADCELL_DOUT_PIN  11
#define LOADCELL_SCK_PIN  10
#define LED 3
#define Switch 2

  HX711 scale;

  int gasrelaypin = 8;
  int lightrelaypin = 9;
  const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
  const int echoPin = 13; // Echo Pin of Ultrasonic Sensor
  
  //CHANGE THESE
  int candyNumber = 4;
  int allowedTake = 1;

  //DON'T CHANGE THESE
  //unsigned long curTime;
  //unsigned long waitTime = 5000;
  int startWeight;
  float currentWeight;
  int calcWeight;
  int lastCandyNum;
  float curCandy;
  float singularWeight;
  int weigh = 0;
  int buttonState2 = 0;
  float calibration_factor = -10000; 
  bool cooldown = true;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(gasrelaypin, OUTPUT);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(lightrelaypin, OUTPUT);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  scale.set_scale(calibration_factor);
  //one reading without any weight to check zero
  scale.get_units();

}


void loop() 
{
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  //curTime = millis();
    
  if(buttonState2 != digitalRead(2))
  {
     buttonState2 = digitalRead(2);
     //Serial.println(buttonState2);

     if(buttonState2  = 2)
    {
       
       
      digitalWrite(LED, HIGH);
      getWeight();
      curCandy = (currentWeight / singularWeight) + 0.5;
      if(cm != 21 && int(curCandy + 0.5) < (int(candyNumber) - 1))
      {
       //handleCandy();
       fireball();
       //Serial.println(currentWeight);
       //Serial.println(curCandy);
       //Serial.println(candyNumber - 1);
      }
      //Serial.println(int(curCandy));
      //delay(1000);
     }

   }

}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

   
void handleCandy()
  {
    curCandy = (currentWeight / singularWeight) + 0.5;

      
  }  

void getWeight() 
  {
    currentWeight = scale.get_units();
    Serial.println(int(curCandy));
    if(weigh < 1)
      {
      Serial.println("wrk");
      lastCandyNum = curCandy;
      startWeight = scale.get_units();
      calcWeight = startWeight;
      singularWeight = scale.get_units() / candyNumber;
      //Serial.println(singularWeight);
      //Serial.println(startWeight);
      Serial.println(currentWeight);
      weigh++;
      }

  }

void fireball()
{
   digitalWrite(gasrelaypin, HIGH); // sets the digital pin 13 on
  delay(1000);
  digitalWrite(lightrelaypin, HIGH); // sets the digital pin 13 on
  delay(900);            // waits for a second
   digitalWrite(gasrelaypin, LOW); // sets the digital pin 13 on
  digitalWrite(lightrelaypin, LOW); // sets the digital pin 13 on  
  delay(1000);
  candyNumber = curCandy;
  }
