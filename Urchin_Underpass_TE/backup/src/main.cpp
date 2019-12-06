/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nathan Brown                                              */
/*    Created:      Tue Oct 22 2019                                           */
/*    Description:  Jordan's Jank Jo-Bot                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

vex::brain       Brain;
vex::competition Competition;
vex::motor LeftDrive(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor RightDrive(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor CenterDrive(vex::PORT6, vex::gearSetting::ratio18_1, true);
vex::motor IntakeClamp(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::motor IntakeRotate(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LeftIntake(vex::PORT7, vex::gearSetting::ratio18_1, false);
vex::motor RightIntake(vex::PORT8, vex::gearSetting::ratio18_1, true);
vex::motor LeftScissor(vex::PORT15, vex::gearSetting::ratio18_1, false);
vex::controller Controller1(vex::controllerType::primary);

void drivetrainBrake(){
  LeftDrive.stop(vex::brakeType::brake);
  RightDrive.stop(vex::brakeType::brake);
}
void centerBrake(){
  CenterDrive.stop(vex::brakeType::brake);
}

int liftSpeedPCT = 100;
int clawSpeedPCT = 50;
int dpadSpeedPCT = 100;
int intakeSpeedPCT = 100;
int rotateSpeedPCT = 75;
int clampPCT = 50;
float joyspeedMod = 0.9;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {

}

void autonomous( void ) {
  LeftDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  RightDrive.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(3000);
  LeftDrive.spin(vex::directionType::rev, 75 , vex::velocityUnits::pct); 
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
        else if(Controller1.ButtonDown.pressing()) {
          LeftDrive.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);
          RightDrive.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);            
        }
        if (Controller1.ButtonLeft.pressing()) { //nudge fwd/rev
          CenterDrive.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonRight.pressing()) {
          CenterDrive.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        
        Controller1.ButtonLeft.released(centerBrake);
        Controller1.ButtonRight.released(centerBrake);
        Controller1.ButtonUp.released(drivetrainBrake);
        Controller1.ButtonDown.released(drivetrainBrake);
                
        //INTAKE CONTROL
        if(Controller1.ButtonR1.pressing()) {
          LeftIntake.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          RightIntake.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing()) { 
          LeftIntake.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          RightIntake.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          LeftIntake.stop(vex::brakeType::hold);
          RightIntake.stop(vex::brakeType::hold);
        }

        //SCISSOR CONTROL
        if(Controller1.ButtonL1.pressing()) {
          LeftScissor.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
          LeftScissor.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          LeftScissor.stop(vex::brakeType::hold);
        }
        
        //Intake Rotato
        if(Controller1.ButtonX.pressing()) { 
          IntakeRotate.spin(vex::directionType::fwd, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonB .pressing()) { 
          IntakeRotate.spin(vex::directionType::rev, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
          IntakeRotate.stop(vex::brakeType::hold);        
        }

        //IntakeClamp
        if(Controller1.ButtonA.pressing()) { 
          IntakeClamp.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonY.pressing()) { 
          IntakeClamp.spin(vex::directionType::rev, intakeSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
          IntakeClamp.stop(vex::brakeType::hold);        
        }
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}