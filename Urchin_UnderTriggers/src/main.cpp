/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\SMASH Scholar                                    */
/*    Created:      Wed Dec 18 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

vex::competition Competition;
vex::motor LeftDrive(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor RightDrive(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor TrayRotate(vex::PORT14, vex::gearSetting::ratio18_1, false);
vex::motor LeftArm(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::motor RightArm(vex::PORT17, vex::gearSetting::ratio18_1, true);
vex::motor LeftScissor(vex::PORT15, vex::gearSetting::ratio36_1, false);
vex::motor RightScissor(vex::PORT13, vex::gearSetting::ratio36_1, true);
vex::motor Clamp(vex::PORT12, vex::gearSetting::ratio18_1, false);
vex::controller Controller1(vex::controllerType::primary);
vex::drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 319.19, 367.5063, 254, mm, 1);


void drivetrainBrake(){
  LeftDrive.stop(vex::brakeType::brake);
  RightDrive.stop(vex::brakeType::brake);
}


int liftSpeedPCT = 90;
int dpadSpeedPCT = 100;
int rotateSpeedPCT = 50;
int clampPCT = 50;
int rampSpeedPCT = 90;
int armSpeedPCT = 50;
float joyspeedMod = 0.9;

void pre_auton( void ) {

}

void autonomous( void ) {
  LeftDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  RightDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(3000);
  LeftDrive.spin(vex::directionType::rev, 100 , vex::velocityUnits::pct); 
  RightDrive.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(2000);
}

//Driver Code
void usercontrol( void ) {
  while (1) {
    LeftDrive.spin(vex::directionType::fwd, ((Controller1.Axis3.value() + Controller1.Axis1.value())  * joyspeedMod), vex::velocityUnits::pct); //(Axis3+Axis1)/2
    RightDrive.spin(vex::directionType::fwd, ((Controller1.Axis3.value() - Controller1.Axis1.value()) * joyspeedMod), vex::velocityUnits::pct);//(Axis3-Axis1)/2

       //DRIVETRAIN DPAD
       if (Controller1.ButtonUp.pressing()) { //nudge fwd/rev
          LeftDrive.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
          RightDrive.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        //ARM CONTROL
        if(Controller1.ButtonRight.pressing()) {
          LeftArm.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          RightArm.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonY.pressing()) { 
          LeftArm.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          RightArm.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          LeftArm.stop(vex::brakeType::hold);
          RightArm.stop(vex::brakeType::hold);
        }
        //CLAMP
        if(Controller1.ButtonB.pressing()) {
          Clamp.spin(vex::directionType::fwd, clampPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) { 
          Clamp.spin(vex::directionType::rev, clampPCT, vex::velocityUnits::pct);
        }
        else {
          Clamp.stop(vex::brakeType::hold);
        }

        //SCISSOR CONTROL
        if(Controller1.ButtonR1.pressing()) {
          LeftScissor.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          RightScissor.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);

        }
        else if(Controller1.ButtonR2.pressing()) { 
          LeftScissor.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          RightScissor.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          LeftScissor.stop(vex::brakeType::hold);
          RightScissor.stop(vex::brakeType::hold);
        }

        //TRAY CONTROL
        if(Controller1.ButtonL1.pressing()) { 
          TrayRotate.spin(vex::directionType::fwd, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
          TrayRotate.spin(vex::directionType::rev, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
          TrayRotate.stop(vex::brakeType::hold);        
        }
    task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();

    //Prevent main from exiting with an infinite loop.                         
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
