
#ifndef LINE_SENSOR_H_
#define LINE_SENSOR_H_

#include "hal.h"
#include "ch.h"
#include "tools.h"


#define BLACK 0
#define WHITE 1
#define LINE_COLOR BLACK

#define LS_LEFT      1
#define LS_RIGHT     2
//#define LS_MIDDLE    3
// idea about add front/back LS


typedef struct{
  // The GPIO pin on which the LineSensor is connected
  GPIO_PIN IN;
  // Line Color
  char LineColor;
}LineSensor;

void LineSensorsConfig();
bool_t LineSensorIsInLine(char ls);

#endif /* LINE_SENSOR_H_ */
