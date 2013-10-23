#ifndef SPEEDMETER_H_
#define SPEEDMETER_H_

#include "hal.h"
#include "ch.h"
#include "tools.h"


/**
 * @brief   System ticks to microseconds.
 * @details Converts from system ticks number to microseconds.
 * @note    The result is rounded upward to the next microseconds boundary.
 *
 * @param[in] st        system tick
 * @return              time in microseconds.
 *
 * @api
 */

#define SystemTick2us(st) ((int) ((st - 1L) * 1000000L / CH_FREQUENCY) + 1L)
     
typedef void (*SpeedMeter_callback_t)();


bool isLeftLate();
bool isRightLate();
void  SpeedMetersConfig(SpeedMeter_callback_t _left_cb, SpeedMeter_callback_t _right_cb);
float SpeedMeterGetSpeedLeft();
float SpeedMeterGetSpeedRight();


#endif /* SPEEDMETER_H_ */
