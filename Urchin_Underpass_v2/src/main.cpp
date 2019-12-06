/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nathan Brown                                              */
/*    Created:      Tue Oct 22 2019                                           */
/*    Description:  Jordan's Jank Jo-Bot                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "myfunctions.h"
#include "vex.h"
using namespace vex;
typedef std::string string;

brain Brain;
competition Competition;
motor LeftDrive(PORT11, gearSetting::ratio18_1, false);
motor RightDrive(PORT20, gearSetting::ratio18_1, true);
motor IntakeRotate(PORT14, gearSetting::ratio18_1, false);
motor LeftIntake(PORT16, gearSetting::ratio18_1, false);
motor RightIntake(PORT17, gearSetting::ratio18_1, true);
motor LeftScissor(PORT15, gearSetting::ratio36_1, false);
motor RightScissor(PORT13, gearSetting::ratio36_1, true);
controller Controller1(controllerType::primary);

int liftSpeedPCT = 75;
int clawSpeedPCT = 50;
int dpadSpeedPCT = 100;
int intakeSpeedPCT = 100;
int rotateSpeedPCT = 35;
int clampPCT = 35;
int rampDelayTime = 5;
float joyspeedMod = 0.9;
float slowmodeMod = 0.4;
bool slowmode = false;
string slowmodeState = "OFF";

void drivetrainBrake() {
  LeftDrive.stop(vex::brakeType::brake);
  RightDrive.stop(vex::brakeType::brake);
}

void slowmodeSwitch() { slowmode = !slowmode; }

void slowmodeToggle() {
  if (slowmode == true) {
    slowmodeState = "ON";
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Slowmode  %s", slowmodeState.c_str()); //
    Controller1.rumble(".");
    Controller1.Screen.clearLine(5);
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("Slowmode  %s", slowmodeState.c_str());
  }
  if (slowmode == false) {
    slowmodeState = "off";
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Slowmode  %s", slowmodeState.c_str()); // "Slowmode  %s", "Slowmode  %s", slowmodeState.c_str()
    Controller1.rumble(".");
    Controller1.Screen.clearLine(5);
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("Slowmode  %s", slowmodeState.c_str());
  }
}

void autonomous(void) {
  LeftDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(3000);
  LeftDrive.spin(vex::directionType::rev, 75, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(2000);
}

// Driver Code
void usercontrol(void) {
  while (1) {
    Controller1.ButtonA.pressed(slowmodeSwitch);
    Controller1.ButtonA.pressed(slowmodeToggle);
  }
  while (slowmode == false) {
    LeftDrive.spin(
        fwd,
        rampUp(Controller1.Axis3.value(), 5),
        vex::velocityUnits::pct); //(Axis3+Axis1)/2
    RightDrive.spin(
        vex::directionType::fwd,
        ((Controller1.Axis3.value() - Controller1.Axis1.value()) * joyspeedMod),
        vex::velocityUnits::pct); //(Axis3-Axis1)/2

    // DRIVETRAIN DPAD
    if (Controller1.ButtonUp.pressing()) { // nudge fwd/rev
      LeftDrive.spin(vex::directionType::fwd, dpadSpeedPCT,
                     vex::velocityUnits::pct);
      RightDrive.spin(vex::directionType::fwd, dpadSpeedPCT,
                      vex::velocityUnits::pct);
    } else if (Controller1.ButtonDown.pressing()) {
      LeftDrive.spin(vex::directionType::rev, dpadSpeedPCT,
                     vex::velocityUnits::pct);
      RightDrive.spin(vex::directionType::rev, dpadSpeedPCT,
                      vex::velocityUnits::pct);
    }

    Controller1.ButtonUp.released(drivetrainBrake);
    Controller1.ButtonDown.released(drivetrainBrake);

    // INTAKE CONTROL
    if (Controller1.ButtonR1.pressing()) {
      LeftIntake.spin(vex::directionType::fwd, liftSpeedPCT,
                      vex::velocityUnits::pct);
      RightIntake.spin(vex::directionType::fwd, liftSpeedPCT,
                       vex::velocityUnits::pct);
    } else if (Controller1.ButtonR2.pressing()) {
      LeftIntake.spin(vex::directionType::rev, liftSpeedPCT,
                      vex::velocityUnits::pct);
      RightIntake.spin(vex::directionType::rev, liftSpeedPCT,
                       vex::velocityUnits::pct);
    } else {
      LeftIntake.stop(vex::brakeType::hold);
      RightIntake.stop(vex::brakeType::hold);
    }

    // SCISSOR CONTROL
    if (Controller1.ButtonL1.pressing()) {
      LeftScissor.spin(vex::directionType::fwd, liftSpeedPCT,
                       vex::velocityUnits::pct);
      RightScissor.spin(vex::directionType::fwd, liftSpeedPCT,
                        vex::velocityUnits::pct);

    } else if (Controller1.ButtonL2.pressing()) {
      LeftScissor.spin(vex::directionType::rev, liftSpeedPCT,
                       vex::velocityUnits::pct);
      RightScissor.spin(vex::directionType::rev, liftSpeedPCT,
                        vex::velocityUnits::pct);

    } else {
      LeftScissor.stop(vex::brakeType::brake);
      RightScissor.stop(vex::brakeType::brake);
      wait(.001, seconds);
      LeftScissor.stop(vex::brakeType::hold);
      RightScissor.stop(vex::brakeType::hold);
    }

    // Intake Rotato
    if (Controller1.ButtonX.pressing()) {
      IntakeRotate.spin(vex::directionType::fwd, rotateSpeedPCT,
                        vex::velocityUnits::pct);
    } else if (Controller1.ButtonB.pressing()) {
      IntakeRotate.spin(vex::directionType::rev, rotateSpeedPCT,
                        vex::velocityUnits::pct);
    } else {
      IntakeRotate.stop(vex::brakeType::hold);
    }

    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
  while (slowmode == true) {
    LeftDrive.spin(
        vex::directionType::fwd,
        ((Controller1.Axis3.value() + Controller1.Axis1.value()) * joyspeedMod),
        vex::velocityUnits::pct); //(Axis3+Axis1)/2
    RightDrive.spin(
        vex::directionType::fwd,
        ((Controller1.Axis3.value() - Controller1.Axis1.value()) * joyspeedMod),
        vex::velocityUnits::pct); //(Axis3-Axis1)/2

    // DRIVETRAIN DPAD
    if (Controller1.ButtonUp.pressing()) { // nudge fwd/rev
      LeftDrive.spin(vex::directionType::fwd, dpadSpeedPCT,
                     vex::velocityUnits::pct);
      RightDrive.spin(vex::directionType::fwd, dpadSpeedPCT,
                      vex::velocityUnits::pct);
    } else if (Controller1.ButtonDown.pressing()) {
      LeftDrive.spin(vex::directionType::rev, dpadSpeedPCT,
                     vex::velocityUnits::pct);
      RightDrive.spin(vex::directionType::rev, dpadSpeedPCT,
                      vex::velocityUnits::pct);
    }

    Controller1.ButtonUp.released(drivetrainBrake);
    Controller1.ButtonDown.released(drivetrainBrake);

    // INTAKE CONTROL
    if (Controller1.ButtonR1.pressing()) {
      LeftIntake.spin(vex::directionType::fwd, liftSpeedPCT,
                      vex::velocityUnits::pct);
      RightIntake.spin(vex::directionType::fwd, liftSpeedPCT,
                       vex::velocityUnits::pct);
    } else if (Controller1.ButtonR2.pressing()) {
      LeftIntake.spin(vex::directionType::rev, liftSpeedPCT,
                      vex::velocityUnits::pct);
      RightIntake.spin(vex::directionType::rev, liftSpeedPCT,
                       vex::velocityUnits::pct);
    } else {
      LeftIntake.stop(vex::brakeType::hold);
      RightIntake.stop(vex::brakeType::hold);
    }

    // SCISSOR CONTROL
    if (Controller1.ButtonL1.pressing()) {
      LeftScissor.spin(vex::directionType::fwd, liftSpeedPCT,
                       vex::velocityUnits::pct);
      RightScissor.spin(vex::directionType::fwd, liftSpeedPCT,
                        vex::velocityUnits::pct);

    } else if (Controller1.ButtonL2.pressing()) {
      LeftScissor.spin(vex::directionType::rev, liftSpeedPCT,
                       vex::velocityUnits::pct);
      RightScissor.spin(vex::directionType::rev, liftSpeedPCT,
                        vex::velocityUnits::pct);

    } else {
      LeftScissor.stop(vex::brakeType::brake);
      RightScissor.stop(vex::brakeType::brake);
      wait(.001, seconds);
      LeftScissor.stop(vex::brakeType::hold);
      RightScissor.stop(vex::brakeType::hold);
    }

    // Intake Rotato
    if (Controller1.ButtonX.pressing()) {
      IntakeRotate.spin(vex::directionType::fwd, rotateSpeedPCT,
                        vex::velocityUnits::pct);
    } else if (Controller1.ButtonB.pressing()) {
      IntakeRotate.spin(vex::directionType::rev, rotateSpeedPCT,
                        vex::velocityUnits::pct);
    } else {
      IntakeRotate.stop(vex::brakeType::hold);
    }

    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(100); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}
