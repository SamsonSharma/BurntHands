#include "HX711.h"
#include <math.h>

#define LOADCELL_DOUT_PIN  11
#define LOADCELL_SCK_PIN  10
#define LED 3
#define Switch 2

  HX711 scale;

  int gasrelaypin = 8;
  int lightrelaypin = 9;
  
  //CHANGE THESE
  int candyNumber = 3;
  int allowedTake = 1;

  //DON'T CHANGE THESE
  int startWeight;
  float currentWeight;
  int calcWeight;
  float curCandy;
  float singularWeight;
  int weigh = 0;
  int buttonState2 = 0;
  float calibration_factor = -466; 

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
  scale.get_units() + 0.5;

}


void loop() 
{

    
  if(buttonState2 != digitalRead(2))
  {
     buttonState2 = digitalRead(2);
     //Serial.println(buttonState2);

     if(buttonState2  = 2)
    {
      digitalWrite(LED, HIGH);
      getWeight();
      curCandy = (currentWeight / singularWeight) + 0.5;
      Serial.println(int(curCandy));
      //delay(1000);
      
      if(candyNumber - curCandy > allowedTake)
      {
       Serial.println("GAS");
       delay(1000);
       //calcWeight = currentWeight;
//       Serial.println(singularWeight);
//       Serial.println(startWeight);
//       Serial.println(currentWeight);

      }
  
     }

   }

}

   
  

void getWeight() 
  {
    currentWeight = scale.get_units();
    if(weigh < 1)
      {
      Serial.println("wrk");
      startWeight = scale.get_units();
      calcWeight = startWeight;
      singularWeight = scale.get_units() / candyNumber;
      Serial.println(singularWeight);
      Serial.println(startWeight);
      Serial.println(currentWeight);
      weigh++;
      }
//
//      if(currentWeight / candyNumber > singularWeight)
//      {
//        //Serial.println("putback");
//        //calcWeight = startWeight;
//        //rWeight = scale.get_units() / candyNumber;
//        }
  }
