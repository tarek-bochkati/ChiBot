#include "hal.h"
#include "ch.h"
#include "tools.h"
#include "speedmeter.h"

/******************************************************************************
 * speed calculation is EXTI based
 * it use EXTD1
 * so you should set "HAL_USE_EXT" -> TRUE at halconf.h-line 65
 *****************************************************************************/

#define DEVIDER          13.68   // :  (36÷10)x(38÷10)
#define WHEEL_PERIMETER  12      // cm

static const float cte_speed = WHEEL_PERIMETER * 1000000 / DEVIDER;


static systime_t tl1, tl2, tr1, tr2, t;
static SpeedMeter_callback_t left_cb, right_cb;
     
static void leftCallBack(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;  

  tl1 = tl2;
  tl2 = chTimeNow();
  
  left_cb();
}

static void rightCallBack(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  
  tr1 = tr2;
  tr2 = chTimeNow();
  
  right_cb();
}

static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    // left SpeedMeter connected to PC4
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, leftCallBack},
    // right SpeedMeter connected to PC5
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, rightCallBack},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

void SpeedMetersConfig(SpeedMeter_callback_t _left_cb, SpeedMeter_callback_t _right_cb){
  left_cb = _left_cb;
  right_cb = _right_cb;
     
  extStart(&EXTD1, &extcfg);
  
  tl1 = tl2 = chTimeNow();
  tr1 = tr2 = chTimeNow();
}

static float ___SpeedMeterGetSpeed(systime_t timeLap){
  return cte_speed / SystemTick2us(timeLap);
}

bool isLeftLate(){
  t = chTimeNow();
  return (t-tl2>tl2-tl1);  
}

bool isRightLate(){
  t = chTimeNow();
  return (t-tr2>tr2-tr1);  
}

float SpeedMeterGetSpeedLeft(){
  if(isLeftLate())
    return ___SpeedMeterGetSpeed(t-tl2);
  else
    return ___SpeedMeterGetSpeed(tl2-tl1); 
}

float SpeedMeterGetSpeedRight(){
  if(isRightLate())
    return ___SpeedMeterGetSpeed(t-tr2);
  else
    return ___SpeedMeterGetSpeed(tr2-tr1); 
}