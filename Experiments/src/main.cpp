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

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "myfunctions.h"
#include "vex.h"
using namespace std;
using namespace vex;

controller Controller1(controllerType::primary);
int LeftY;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (1) {/*
    if (Controller1.Axis3.position(percent) > 0) {
      Brain.Screen.print(
          nathanRampUp(Controller1.Axis3.position(percent), 10, 10));
      task::sleep(50);
      Brain.Screen.newLine();
    } */
    if (Controller1.Axis3.position(percent) > 0) {
      Brain.Screen.print(
          rampUp(Controller1.Axis3.position(percent), 10));
      task::sleep(50);
      Brain.Screen.newLine();
    }
  }
}
