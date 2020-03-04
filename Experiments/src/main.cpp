// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor11              motor         11
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Clawbot Template (Drivetrain, No Gyro)                    */
/*                                                                            */
/*    Name:                                                                   */
/*    Date:                                                                   */
/*    Class:                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "myfunctions.h"
#include "vex.h"
using namespace std;
using namespace vex;

controller Controller1(controllerType::primary);
int LeftY;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (1) {
    Rampv2(Controller1.Axis3.position(percent),
           Motor11.velocity(velocityUnits::pct), 10, 10);
    task::sleep(50);
    Brain.Screen.newLine();
  }
}
