#include "ch.h"
#include "hal.h"
#include "dc_motor.h"
#include "dc_vehicle.h"
#include "speedmeter.h"

#define BETWEEN(v,MAX,MIN) (v>MAX?MAX:(v<MIN?MIN:v))
#define DELIMIT_SPEED() speed = BETWEEN(speed,40,0)

static int LeftSpeedPercent, RightSpeedPercent;
static float rightSpeed, leftSpeed;

static const DCMotor rightMotor = {
    {GPIOA, 6},   // motor IN1 : PA6
    {GPIOA, 7},   // motor IN2 : PA7
    {GPIOA, 3},   // motor EN  : PA3
    &PWMD2,       // motor EN PWM Driver : TIM2
    3             // motor EN PWM Channel : CH4
};

static const DCMotor leftMotor = {
    {GPIOA, 4},   // motor IN1 : PA4
    {GPIOA, 5},   // motor IN2 : PA5
    {GPIOA, 2},   // motor EN  : PA2
    &PWMD2,       // motor EN PWM Driver : TIM2
    2             // motor EN PWM Channel : CH3
};

static DCVehicle dcvehicle;

#define SPEED_REGULATION(SPEED_PERCENT, SPEED_CMD, SPEED, MOTOR)   \
          if(SPEED_CMD == 0)           SPEED_PERCENT = 100;        \
          else if(SPEED < SPEED_CMD)   SPEED_PERCENT ++;           \
          else                         SPEED_PERCENT --;           \
          DCMotorSetSpeed(&MOTOR,&SPEED_PERCENT);


void left_speed_regulation_cb(){
    SPEED_REGULATION(LeftSpeedPercent, leftSpeed, SpeedMeterGetSpeedLeft(), dcvehicle.leftMotor)
}

void right_speed_regulation_cb(){
    SPEED_REGULATION(RightSpeedPercent, rightSpeed, SpeedMeterGetSpeedRight(), dcvehicle.rightMotor)
}

static WORKING_AREA(speed_reg_wake_up_wa, 128);
static msg_t speed_reg_wake_up_thd(void *arg) {
  while(TRUE){
    if(isLeftLate())    left_speed_regulation_cb();
    if(isRightLate())   right_speed_regulation_cb();
    chThdSleepMilliseconds(100);
  }
}

void DCVehicleConfig() {
  dcvehicle.rightMotor = rightMotor;
  dcvehicle.leftMotor = leftMotor;
    
  LeftSpeedPercent = RightSpeedPercent = 0;

  DCMotorConfig(&dcvehicle.rightMotor);
  DCMotorConfig(&dcvehicle.leftMotor);
  
  SpeedMetersConfig(left_speed_regulation_cb, right_speed_regulation_cb);
  (void)chThdCreateStatic(speed_reg_wake_up_wa,
                          sizeof(speed_reg_wake_up_wa),
                          NORMALPRIO ,
                          speed_reg_wake_up_thd, NULL);
}

void DCVehicleStop() {
  rightSpeed = leftSpeed = 0;
  DCMotorStop(&dcvehicle.rightMotor);
  DCMotorStop(&dcvehicle.leftMotor);
}

void DCVehicleForward(float speed) {
  DELIMIT_SPEED();
  rightSpeed = leftSpeed = speed;
  DCMotorForward(&dcvehicle.rightMotor);
  DCMotorForward(&dcvehicle.leftMotor);
}

void DCVehicleBackward(float speed) {
  DELIMIT_SPEED();
  rightSpeed = leftSpeed = speed;
  DCMotorBackward(&dcvehicle.rightMotor);
  DCMotorBackward(&dcvehicle.leftMotor);
}

void DCVehicleTurnRight(float speed){
  DELIMIT_SPEED();
  rightSpeed = 0;  
  DCMotorStop(&dcvehicle.rightMotor);
  
  leftSpeed = speed;
  DCMotorForward(&dcvehicle.leftMotor);
}
void DCVehicleTurnLeft(float speed){
  DELIMIT_SPEED();
  rightSpeed = speed;  
  DCMotorForward(&dcvehicle.rightMotor);
  
  leftSpeed = 0;
  DCMotorStop(&dcvehicle.leftMotor);
}
void DCVehicleSpinRight(float speed){
  DELIMIT_SPEED();
  rightSpeed = leftSpeed = speed;
  DCMotorBackward(&dcvehicle.rightMotor);
  DCMotorForward(&dcvehicle.leftMotor);
}
void DCVehicleSpinLeft(float speed){
  DELIMIT_SPEED();
  rightSpeed = leftSpeed = speed;
  DCMotorForward(&dcvehicle.rightMotor);
  DCMotorBackward(&dcvehicle.leftMotor);
}
