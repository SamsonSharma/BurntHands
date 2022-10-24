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


  //DON'T CHANGE THESE
  float currentWeight;
  float curCandy;
  float singularWeight;
  int weigh = 0;
  int buttonState2 = 0;
  float calibration_factor = -10000; 


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
  Serial.println(cm);
    
  if(buttonState2 != digitalRead(2))
  {
     buttonState2 = digitalRead(2);

     if(buttonState2  = 2)
    {
      digitalWrite(LED, HIGH);
      getWeight();
      curCandy = (currentWeight / singularWeight) + 0.5;
      if(cm < 21 || cm > 22)
      {
       if(int(curCandy + 0.5) < (int(candyNumber) - 1))
       {
        fireball();
       }
       
      }

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
      singularWeight = scale.get_units() / candyNumber;
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
