
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

volatile int currentHeading = 0;
volatile int headingError = 0;
volatile int headingTarget = 0;
volatile int headingOutput = 0;
volatile int errorSum = 0;
volatile int left;
volatile int right;
volatile int velocityBias = 30; //constant velocity speed
float updateTime = 0.08;


int kp = 2; //Ku = 5
int ki = 5; //Tu = 0.5
int kd = 0;

int controlSaturation = 100;


//TaskHandle_t VaderHandle;
//TaskHandle_t DQHandle;
//TaskHandle_t DancingHandle;

int sign(int value) { //funtion that just returns a number's sign
  if (value >= 0) {
    return 1;
  } else {
    return -1;
  }
}


void setup() {
  /// Setup Ringo ///
  HardwareBegin();              //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();             //Play startup chirp and blink eyes
  SwitchMotorsToSerial();
  delay(1000);
  NavigationBegin();            //Turns on and intializes the gyroscope and accelerometer
  delay(1000);
  CalibrateNavigationSensors(); //Needed?

  delay(1000);
  ZeroNavigation();             //Needed?
//  Serial.begin(19200);
//  Serial.println("send it");

 
   xTaskCreate(
    Checker
      , (const portCHAR *)"Checker"
      , 128
      , NULL
      , 3
      , NULL);

   xTaskCreate(
    Controller
      , (const portCHAR *)"Controller"
      , 128
      , NULL
      , 2
      , NULL);

}

void loop() {};

//Periodic sensor Checker, 
void Checker(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {
    SimpleGyroNavigation();
    currentHeading = PresentHeading();

    
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

//PID controller for heading
void Controller(void *pvParameters) 
{
  (void) pvParameters;
  for(;;) {


    headingError = headingTarget - currentHeading;
    errorSum = errorSum + updateTime * headingError;
    
    headingOutput = kp*headingError + ki*errorSum;

    if (headingOutput > 0) {
      OnEyes(0,50,0); //Green
    } else if (headingOutput < 0) {
      OnEyes(50,0,0); //Red
    } else if (headingError == 0) {
      OnEyes(0,0,50); //Blue
    }

    if (abs(headingOutput) > controlSaturation) {
      headingOutput = controlSaturation * sign(headingOutput);
      left = 0.5*headingOutput + headingOutput;
      right = 0,5*headingOutput - headingOutput;
    } else {
      left =velocityBias + headingOutput;
      right=velocityBias - headingOutput;
      
    }


    //Serial.println(headingOutput);

    
    Motors(left,right);

    
    vTaskDelay(80 / portTICK_PERIOD_MS);
  }
}
