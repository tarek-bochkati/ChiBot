#ifndef DC_VEHICLE_H_
#define DC_VEHICLE_H_

#include "dc_motor.h"

typedef struct {
  DCMotor rightMotor;
  DCMotor leftMotor;
} DCVehicle;

/*===========================================================================*/
/**
 *  DCVehicle Functions
 */
/*===========================================================================*/

//init
void DCVehicleConfig();
//commands
void DCVehicleStop();
void DCVehicleFree();
void DCVehicleForward(float speed);
void DCVehicleBackward(float speed);
void DCVehicleTurnRight(float speed);
void DCVehicleTurnLeft(float speed);
void DCVehicleSpinRight(float speed);
void DCVehicleSpinLeft(float speed);


#endif /* DC_VEHICLE_H_ */
