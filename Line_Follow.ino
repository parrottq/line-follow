#include <GroveColorSensor.h>
#include <Registers.h>
#include <Utilities.h>

/*  PRIZM Controller example program
 *  This program implements line following with the TaskBot. Using the line finder sensor   
 *  on sensor port D3, the robot will follow the edge of a black stripe on a white surface. 
 *  The DC drive motors will power one motor at a time resulting in back and forth forward motion to
 *  keep the robot traversing the line edge.
 *  author PWU 08/05/2016
 */

#include <stdint.h>
#include <PRIZM.h>     // include PRIZM library
PRIZM prizm;           // instantiate a PRIZM object “prizm” so we can use its functions

#define BLACKLINE_SENSOR 3

//boolean is_done;
//unsigned long lost_contact_time;
uint16_t clock_black_line;
uint64_t clock_time;

enum Mode {
  STOP,
  DRIVE,
  RECOVER
} current_state;

void setup() { 
  //is_done = false; 
  //lost_contact_time = 7000;
  clock_black_line = 0;
  clock_time = 0;

  current_state = DRIVE;
  
  prizm.PrizmBegin();   // initialize PRIZM

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors

  
}

void loop() {

  switch(current_state) {
    case(STOP): {
      prizm.setMotorPowers(125, 125);
      break;
    }
    case(DRIVE) : {
      if(prizm.readLineSensor(BLACKLINE_SENSOR) == 1 || clock_black_line > 0){
        prizm.setMotorPowers(-15,15); 
        prizm.setRedLED(HIGH);

        if(!(clock_black_line > 0)){
          clock_black_line = 10;
        }
      } else {
        prizm.setMotorPowers(15,0); 
        prizm.setRedLED(LOW);
      }
      
      if(clock_black_line > 0) {
        clock_black_line = clock_black_line - 1;
        prizm.setGreenLED(HIGH);
      }else{
        prizm.setGreenLED(LOW);
      }

      /*if(clock_time > (15000)){
        current_state = STOP;
      }*/
      
    }
  }

  clock_time += 10;
  delay(10);
/*
  if(!is_done){
    // beam reflected, no line detected
    if(prizm.readLineSensor(BLACKLINE_SENSOR) == 0){
      prizm.setMotorPowers(15,0); 
      prizm.setRedLED(LOW);
    }  
    
    // no relected beam, line detected
    if(prizm.readLineSensor(BLACKLINE_SENSOR) == 1){
      prizm.setMotorPowers(-15,15); 
      prizm.setRedLED(HIGH);
      lost_contact_time = millis() + 3000;
      delay(100);
    }

    if(millis() > lost_contact_time){
      prizm.setGreenLED(HIGH);  
      prizm.setMotorPowers(-10, -10);
      delay(4000);
      prizm.setMotorPowers(15, 0);
    }
    
  } else {
    delay(250);
  }

  if(millis() > 35000) {
    is_done = true;
    prizm.setMotorPowers(125, 125);
  }
*/
  
   
}







