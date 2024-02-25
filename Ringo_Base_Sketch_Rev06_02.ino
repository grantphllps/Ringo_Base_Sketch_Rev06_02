
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

int songState = 0; //0 for dancing queen, 1 for imp march
int sensorRight;
int sensorLeft;
int sensorRear;
TaskHandle_t VaderHandle;
TaskHandle_t DQHandle;
TaskHandle_t DancingHandle;



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
      , 2
      , &VaderHandle);

  xTaskCreate(
    DQ
      , (const portCHAR *)"Vader"
      , 128
      , NULL
      , 2
      , &DQHandle);

   xTaskCreate(
    Checker
      , (const portCHAR *)"Checker"
      , 128
      , NULL
      , 3
      , NULL);

         
   xTaskCreate(
    Dancing
      , (const portCHAR *)"BR"
      , 128
      , NULL
      , 0
      , &DancingHandle);


      vTaskSuspend(VaderHandle);
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

void DQ(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    DancingQueen();
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



//Periodic sensor Checker, 
void Checker(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    
    digitalWrite(Source_Select, HIGH);
    sensorRear = analogRead(LightSense_Rear);
    sensorLeft = analogRead(LightSense_Left);
    int newSong;

    if (sensorRear < 500) {
      newSong = 1;
      OnEyes(50,0,0);
      
    } else {
      newSong = 0;
      OnEyes(0,0,50);
    }

    if (newSong != songState) {//If we are not playing the correct song
       if (newSong == 1) {//If supposed to be playing "vader"
        songState = 1;
        vTaskSuspend(DQHandle);
        vTaskSuspend(DancingHandle);
        vTaskResume(VaderHandle);
       } else if(newSong == 0) {
        songState = 0;
        vTaskSuspend(VaderHandle);
        vTaskResume(DQHandle);
        vTaskResume(DancingHandle);
       }
    }
    
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
