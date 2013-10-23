/*===========================================================================*/
/**
 * Filename : main.c
 * Author   : Tarek Bouchkati
 * license  : BSD
 */
/*===========================================================================*/

#include "ch.h"
#include "hal.h"
#include "middleware/dc_vehicle.h"
#include "middleware/line_sensor.h"
#include "algorithmes/line_following.h"
#include "algorithmes/test_moving.h"


/*===========================================================================*/
/**
 * Main function
 */
/*===========================================================================*/


void setup(){
  halInit();
  chSysInit();  
    
  DCVehicleConfig();
  
  LineSensorsConfig();
}

int main() {
  setup();

  while(!palReadPad(GPIOA,GPIOA_BUTTON));
  
  //StartLineFollowing();
  StartTestMoving();
  
  // infinite loop
  while (TRUE) {
      chThdSleepMilliseconds(1000);
  }
}
