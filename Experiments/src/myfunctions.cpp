// to allow access to SDK classes and class member functions
#include "vex.h"
using namespace vex;

// ramp up script
int rampUp(int controlInput, int maxChange) {
  int motorPercent;
  int lastPercent = 0;
  int deltaPercent;
  while (true) {
    motorPercent = controlInput;
    deltaPercent = (lastPercent - motorPercent);
    if (deltaPercent > maxChange) {
      deltaPercent = maxChange;
    }
    motorPercent = lastPercent + deltaPercent;
    lastPercent = motorPercent;
    return motorPercent;
    task::sleep(20);
  }
}

// ramp down script
int rampDown(int controlInput,
             int maxChange) { // replace controlInput with a controller axis,
                              // replace maxChange with how fast motor ramps
  int motorPercent;           // -20
  int lastPercent = 0;        // -20
  int deltaPercent;           // -10
  while (true) {
    motorPercent = controlInput;                 // -100 = -100
    deltaPercent = (lastPercent - motorPercent); // -10 - -100 = 90
    if (deltaPercent > maxChange) {              // 90 > -10
      deltaPercent = maxChange;                  // 90 = -10
    }
    motorPercent = lastPercent + deltaPercent; // -10 + -10 = -20
    lastPercent = motorPercent;
    return motorPercent;
    task::sleep(20);
  }
}

int nathanRampUp(int controllerPwr, int maxChange, int delayTime) {
  int motorPwr = 0;
  while (1) {
    if (controllerPwr > maxChange && motorPwr != controllerPwr) {
      for(;motorPwr <= controllerPwr;motorPwr +=maxChange)
      task::sleep(delayTime);
    }
    else{
      motorPwr = controllerPwr;
    }
    return motorPwr;
  }
}

int nathanRampDown(int controllerPwr, int maxChange, int delayTime) {
  int motorPwr = 0;
  while (1) {
    if (controllerPwr < maxChange && motorPwr != controllerPwr) {
      motorPwr -= maxChange;
      task::sleep(delayTime);
    }
    return motorPwr;
  }
}

int deadzoneX(int x, int threshold) {
  while (1 == 1) {
    int deadX = 0;
    // Create "deadzone" for x axis
    if (x > threshold) {
      x = deadX;
    } else {
      x = 0;
    }
    return deadX;
  }
}

int deadzoneY(int y, int threshold) {
  while (1 == 1) {
    int deadY = 0;
    // Create "deadzone" for y axis
    if (y > threshold) {
      y = deadY;
    } else {
      y = 0;
    }
    return deadY;
  }
}
