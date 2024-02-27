
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

volatile int heading = 0;

//TaskHandle_t VaderHandle;
//TaskHandle_t DQHandle;
//TaskHandle_t DancingHandle;



void setup() {
  /// Setup Ringo ///
  HardwareBegin();              //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();             //Play startup chirp and blink eyes
  delay(1000);
  NavigationBegin();            //Turns on and intializes the gyroscope and accelerometer
  delay(1000);
  CalibrateNavigationSensors(); //Needed?
  delay(1000);
//  ZeroNavigation();             //Needed?

  Serial.begin(19200);
  Serial.println("Setup");
 
   xTaskCreate(
    Checker
      , (const portCHAR *)"Checker"
      , 128
      , NULL
      , 3
      , NULL);

}

void loop() {}

//Periodic sensor Checker, 
void Checker(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    SimpleGyroNavigation();
    heading = PresentHeading();

    if (abs(heading) > 90) {
      OnEyes(50,0,0);
    } else {
      OnEyes(0,0,0);
    }
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
