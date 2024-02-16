
/* 

Ringo Robot
Ringo_Base_Sketch_Rev06
Version 6.2 03/2018

This is a basic sketch that can be used as a starting point
for various functionality of the Ringo robot.

Significant portions of this code written by
Dustin Soodak for Plum Geek LLC. Some portions
contributed by Kevin King.
Portions from other open source projects where noted.
This code is licensed under:
Creative Commons Attribution-ShareAlike 2.0 Generic (CC BY-SA 2.0)
https://creativecommons.org/licenses/by-sa/2.0/
Visit http://www.plumgeek.com for Ringo information.
Visit http://www.arduino.cc to learn about the Arduino.

*/
#include <Arduino_FreeRTOS.h>
#include "RingoHardware.h"

volatile int LightsOn = 1;
bool BackLightsState = false;
int sensorRight;
int sensorLeft;
int sensorRear;
TaskHandle_t hand;



void setup() {
  /// Setup Ringo ///
  HardwareBegin();        //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();       //Play startup chirp and blink eyes
  RxIRRestart(4);         //wait for 4 byte IR remote command
  IsIRDone();
  GetIRButton();
  RestartTimer();
  IRFlag = false;
  
  Serial.begin(19200);
  Serial.println("Setup");
 

  xTaskCreate(
    Vader
      , (const portCHAR *)"Vader"
      , 128
      , NULL
      , 0
      , NULL);

   xTaskCreate(
    Checker
      , (const portCHAR *)"Checker"
      , 128
      , NULL
      , 2
      , NULL);

   xTaskCreate(
    Blink
      , (const portCHAR *)"BR"
      , 128
      , NULL
      , 1
      , NULL);

   xTaskCreate(
    ToggleLights
      , (const portCHAR *)"BR"
      , 128
      , NULL
      , 3
      , &hand);
         
   xTaskCreate(
    Dancing
      , (const portCHAR *)"BR"
      , 128
      , NULL
      , 0
      , NULL);
      
}

void loop() {};

//Periodic "Imperial March"
void Vader(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    HesComing();
  }
}

//Periodic "Dancing"
void Dancing(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    Dancing();
  }
}

//Sporatic Blinking, this task is event triggered but has an upper
//Limit to the number of time it can be called
void Blink(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
      if (LightsOn) {
        OnEyes(30,30,30);
      } else {
        OnEyes(0,0,0);
      }
      vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

//Aperiodic Light toggling, this task blocks after it has completed
//A single loop. 
void ToggleLights(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    sensorRear = analogRead(LightSense_Rear);
    if (sensorRear < 400) {
      SetPixelRGB(3,30,30,30);
      SetPixelRGB(2,30,30,30);
      SetPixelRGB(1,30,30,30);
    } else {
      SetPixelRGB(3,0,0,0);
      SetPixelRGB(2,0,0,0);
      SetPixelRGB(1,0,0,0);
    }
    vTaskSuspend(NULL);
  }
}

//Periodic sensor Checker, 
void Checker(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    
    digitalWrite(Source_Select, HIGH);
    sensorRear = analogRead(LightSense_Rear);
    sensorLeft = analogRead(LightSense_Left);

    //Check the light intensity for the sporatic task
    if(sensorRear < 550) {
      LightsOn = 1;
    } else {
      LightsOn = 0;
    }

    //Check the light intensity for the aperiodic task
    if (sensorRear < 450 || sensorRear > 600) {
      vTaskResume(hand);
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
