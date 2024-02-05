
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

  /*xTaskCreate(
     TaskBlink
      ,  (const portCHAR *)"Blink"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );*/

  xTaskCreate(
     SongDancingQueen
      ,  (const portCHAR *)"Song"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );
}

void loop() {}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    OnEyes(50,0,0);
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    OffEyes();
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}


void SongDancingQueen(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    SetAllPixelsRGB(0,0,0);

    PlayChirp(NOTE_E5, 50);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);
    
    PlayChirp(NOTE_FS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(700 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(700 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(700 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_B5, 50);
    vTaskDelay(400 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_GS5, 50);
    vTaskDelay(400 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    PlayChirp(NOTE_A5, 50);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    OffChirp();
    vTaskDelay(25 / portTICK_PERIOD_MS);

    
    OffChirp();
    vTaskDelay(18000 / portTICK_PERIOD_MS);


  }
}






