/*
 * ChibiOS/DCMotor is a small library to easily interface L293D
 * in order control DC Motors with ChibiOS/RT.
 *
 * This library is compatible STM32
 *
 * BSD licensed
 *
 * Author: Tarek Bouchkati   <tarekbouchkati@gmail.com>
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "hal.h"
#include "ch.h"
#include "tools.h"

typedef struct {
  // The GPIO pin on which the DCMotor IN1 is connected
  GPIO_PIN IN1;
  // The GPIO pin on which the DCMotor IN2 is connected
  GPIO_PIN IN2;
  // The GPIO pin on which the DCMotor EN is connected
  GPIO_PIN EN;
  // The PWM driver to use with EN
  PWMDriver *pwm_driver;
  // The PWM channel to use with EN
  pwmchannel_t pwm_channel;
} DCMotor;

/*
static const PWMConfig _pwmcfg_model_ = { //model to copy on each initialization
    // 1MHz PWM clock frequency
    1000000,
    // PWM period 10 milliseconds
    10000,
    // no callback
    NULL,
    // PWM channels array
    {    // All disabled
    {PWM_OUTPUT_DISABLED, NULL},    // Channel 0
    {PWM_OUTPUT_DISABLED, NULL},    // Channel 1
    {PWM_OUTPUT_DISABLED, NULL},    // Channel 2
    {PWM_OUTPUT_DISABLED, NULL}     // Channel 3
    }, // channel configuration set dynamically in DCMotorInit()
    0};
*/

/*===========================================================================*/
/**
 *  DCMotor Functions
 */
/*===========================================================================*/

//init
void DCMotorConfig(DCMotor *dcmotor);
//commands
void DCMotorSetSpeed(DCMotor *dcmotor, int *speedPercent);
void DCMotorStop(DCMotor *dcmotor);
void DCMotorForward(DCMotor *dcmotor);
void DCMotorBackward(DCMotor *dcmotor);

#endif // DC_MOTOR_H
