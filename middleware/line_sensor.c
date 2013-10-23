#include "hal.h"
#include "ch.h"
#include "tools.h"
#include "line_sensor.h"


static LineSensor leftLineSensor = { // Left LineSensor configuration
    {GPIOB, 0},    // INPUT
    LINE_COLOR};

static LineSensor rightLineSensor = { // Right LineSensor configuration
    {GPIOB, 1},    // INPUT
    LINE_COLOR};

#ifdef LS_MIDDLE
static LineSensor middleLineSensor = { // middle LineSensor configuration
    {GPIOB, 2},    // INPUT
    LINE_COLOR};
#endif


static void ___LineSensorConfig(LineSensor *linesensor) {
  palSetPadMode(linesensor->IN.port, linesensor->IN.pin, PAL_MODE_INPUT);
}

static bool_t ___LineSensorIsInLine(LineSensor *linesensor) {
  char color =
      (palReadPad(linesensor->IN.port, linesensor->IN.pin) == PAL_LOW) ? BLACK :
                                                                         WHITE;
  return color == linesensor->LineColor ? TRUE : FALSE;
}

void LineSensorsConfig(){
  ___LineSensorConfig(&leftLineSensor);
  ___LineSensorConfig(&rightLineSensor);
  #ifdef LS_MIDDLE
  ___LineSensorConfig(&middleLineSensor);
  #endif
}

bool_t LineSensorIsInLine(char ls){
    switch(ls){
      case LS_LEFT:
        return ___LineSensorIsInLine(&leftLineSensor);
        break;
      case LS_RIGHT:
        return ___LineSensorIsInLine(&rightLineSensor);
        break;
      #ifdef LS_MIDDLE
      case LS_MIDDLE:
        return ___LineSensorIsInLine(&middleLineSensor);
        break;
      #endif 
    }
  return FALSE;   
}
