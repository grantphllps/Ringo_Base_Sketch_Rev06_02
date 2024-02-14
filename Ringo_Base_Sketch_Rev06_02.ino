
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

void setup() {
  /// Setup Ringo ///
  HardwareBegin();        //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();       //Play startup chirp and blink eyes
  RxIRRestart(4);         //wait for 4 byte IR remote command
  IsIRDone();
  GetIRButton();
  RestartTimer();

  xTaskCreate(
     TaskBlink
      ,  (const portCHAR *)"Remote"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );

  xTaskCreate(
     SongDancingQueen
      ,  (const portCHAR *)"Song"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );

  xTaskCreate(
     LeftRightDance
      ,  (const portCHAR *)"Dance"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );
  
}

void loop() {}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {restart:              //label to cause program to come back to here if "MENU" on remote is pressed in any example
   byte button;
   //Example user code:  

    if(IsIRDone()){                   //wait for an IR remote control command to be received
      button = GetIRButton();       // read which button was pressed, store in "button" variable

     
      if(button){                   // if "button" is not zero...
        switch (button){            // activate a behavior based on which button was pressed

         case 1:                    // Button 1
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         OnEyes(220, 30, 160);   // turn eyes to plum
         //vTaskDelay(1000 / portTICK_PERIOD_MS);               // brief delay
         //OffPixels();
         break;

         case 2:                    // Button 2
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         OnEyes(120, 0, 0);   // turn eyes red
         //vTaskDelay(1000 / portTICK_PERIOD_MS);               // brief delay
         //OffPixels();
         break;

         case 3:                    // Button 3
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         OnEyes(0, 0, 160);   // turn eyes blue
         vTaskDelay(1000 / portTICK_PERIOD_MS);               // brief delay
         OffPixels();
         break;
         
         default:                   // if no match, break out and wait for a new code
         PlayNonAck();              // quick "NonAck" chirp to know a known button was received, but not understood as a valid command
         RxIRRestart(4);            //wait for 4 byte IR remote command
         SwitchMotorsToSerial();
         Serial.print("button: ");Serial.println(button);  // send button number pressed to serial window
      
         break;
        }
      }
    }//end if(IsIRDone())

  }
}

void LeftRightDance(void *pvParameters)
{
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
    {
      Motors(-50, 50);
      vTaskDelay(125 / portTICK_PERIOD_MS);
      Motors(0, 0);
      vTaskDelay(125 / portTICK_PERIOD_MS);
      Motors(50, -50);
      vTaskDelay(125 / portTICK_PERIOD_MS);
      Motors(0, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void SongDancingQueen(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  { //You are the dancing queen
    PlayChirp(NOTE_E5, 50);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);
    
    PlayChirp(NOTE_FS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    
    //Young and sweet
    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(700 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    //Only seventeen
    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(400 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(1500 / portTICK_PERIOD_MS);

    //Dancing Queen
    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    //Feel the beat from the tambourine
    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);



    //oh yeah

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_CS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(800 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(1200 / portTICK_PERIOD_MS);

    //you can dance
    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(900 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    //you can jive

    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(600 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    //having the time of your life, oh
    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(150 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(150 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_FS5, 50);
    vTaskDelay(900 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    //ooh
    PlayChirp(NOTE_CS6, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    //see that girl
    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    //watch that scene
    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(600 / portTICK_PERIOD_MS);

    //digin the dancing queen
    PlayChirp(NOTE_B5, 50);
    vTaskDelay(150 / portTICK_PERIOD_MS);
    //OffChirp();
    //vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(150 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(450 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(900 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);


    
    OffChirp();
    vTaskDelay(10000 / portTICK_PERIOD_MS);


  }
} 






