/**
  ******************************************************************************
  * @file    vr3.ino
  * @author  Veenus Yadav
  * @brief   Using VR3 module, four commands are used to control LEDs & sensor
  ******************************************************************************
  * @note:
        As a submission to Yun Technologies. 19/5/2017
  ******************************************************************************
  **/
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
  Connection
  Arduino    
   2   ------->     VoiceRecognitionModule TX
   3   ------->     VoiceRecognitionModule RX
   8   ------->     Red LED
   9   ------->     Green LED
   10  ------->     IR sensor Ouput
   A0  ------->     Temprature sensor Output
*/
VR myVR(2,3);

uint8_t records[7]; // save commands that were previously recorded during VR3 training
uint8_t buf[64];

int led1 = 8;
int led2 = 9;
int temp = A0;
int ir = 10;
int irval=0;
int tempval=0;


#define LED1    (0)
#define IRsense  (1) 
#define tempsense (2)
#define LED2 (3)


void setup()
{
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Voice recognition using V3 module");
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(ir, INPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }
  else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)LED1) >= 0){
    Serial.println("LED1 Record loaded");
  }
  
  if(myVR.load((uint8_t)IRsense) >= 0){
    Serial.println("IRsense Record loaded");
  }

  if(myVR.load((uint8_t)tempsense) >= 0){
    Serial.println("tempsense Record loaded");
  }

  if(myVR.load((uint8_t)LED2) >= 0){
    Serial.println("LED2 Record loaded");
  }
}

void loop()
{
  int ret,c=0;
  ret = myVR.recognize(buf, 50);
  if (buf[1]==LED1)
  c=1;
  else if (buf[1]==IRsense)
  c=2;
  else if (buf[1]==tempsense)
  c=3;
  else if (buf[1]==LED2)
  c=4;
    switch(c){
      case 1:
        Serial.println("Command <one>. Blinking RED LED..");
        digitalWrite(led1, HIGH);
        delay(500);
        digitalWrite(led1, LOW);
        delay(500);
        break;
      case 2:
        Serial.println("Command <two>. Printing value of IR sensor..");
        irval=digitalRead(ir);
        Serial.println(irval);
        delay(500);
        break;
      case 3:
        Serial.println("Command <three>. Printing value of Temprature sensor..");
        tempval=analogRead(temp);
        Serial.println(tempval);
        delay(500);
        break;
      case 4:
        Serial.println("Command <four>. Blinking GREEN LED..");
        digitalWrite(led2, HIGH);
        delay(500);
        digitalWrite(led2, LOW);
        delay(500);
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
  }



