/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nathan Brown                                              */
/*    Created:      10/21/19                                                    */
/*    Description:  Code for Midlife Crisis a.k.a Fat Man a.k.a. 3rd Chinese Child */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      LeftWheel(vex::PORT17, vex::gearSetting::ratio18_1, false);
vex::motor      RightWheel(vex::PORT18, vex::gearSetting::ratio18_1, true);
vex::motor      ltlift(vex::PORT7, vex::gearSetting::ratio36_1, false);
vex::motor      rtlift(vex::PORT8, vex::gearSetting::ratio36_1, true);
vex::motor      lblift(vex::PORT9, vex::gearSetting::ratio36_1, true);
vex::motor      rblift(vex::PORT10, vex::gearSetting::ratio36_1, false);
vex::motor      ClawMotor(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor      expand(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::controller Controller1(vex::controllerType::primary);
vex::competition Competition;
//#endregion config_globals

void drivetrainBrake(){
    LeftWheel.stop(vex::brakeType::brake);
    RightWheel.stop(vex::brakeType::brake);
}


int liftSpeedPCT = 75;
int clawSpeedPCT = 50;
int dpadSpeedPCT = 35;
int expandPCT = 50;
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
  LeftWheel.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  RightWheel.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(3000);
  LeftWheel.spin(vex::directionType::rev, 100, vex::velocityUnits::pct); 
  RightWheel.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(2000);
}

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    LeftWheel.spin(vex::directionType::fwd, ((Controller1.Axis3.value() + Controller1.Axis1.value())  * joyspeedMod), vex::velocityUnits::pct); //(Axis3+Axis1)/2
    RightWheel.spin(vex::directionType::fwd, ((Controller1.Axis3.value() - Controller1.Axis1.value()) * joyspeedMod), vex::velocityUnits::pct);//(Axis3-Axis1)/2

        
        
        
        
        //DRIVETRAIN DPAD
        if (Controller1.ButtonUp.pressing()) { //nudge fwd/rev
            LeftWheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
            RightWheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) {
            LeftWheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);
            RightWheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);            
        }
        
        
        Controller1.ButtonUp.released(drivetrainBrake);
        Controller1.ButtonDown.released(drivetrainBrake);
                
        //LIFT CONTROL
        if(Controller1.ButtonR1.pressing()) {
          ltlift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          rtlift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          lblift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          rblift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);

        }
        else if(Controller1.ButtonR2.pressing()) { 
          ltlift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          rtlift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          lblift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          rblift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          ltlift.stop(vex::brakeType::hold);
          rtlift.stop(vex::brakeType::hold);
          lblift.stop(vex::brakeType::hold);
          rblift.stop(vex::brakeType::hold);
        }
        
            
        //CLAW CONTROL
        if(Controller1.ButtonL1.pressing()) { 
            ClawMotor.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
            ClawMotor.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
            ClawMotor.stop(vex::brakeType::hold);        
        }

        //expand
        if(Controller1.ButtonX.pressing()) { 
            expand.spin(vex::directionType::fwd, expandPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonB .pressing()) { 
            expand.spin(vex::directionType::rev, expandPCT, vex::velocityUnits::pct);
        }
        else { 
            expand.stop(vex::brakeType::hold);        
        }
        
        
		vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    Controller1.Screen.clearScreen(); //clears controller screen unless something is displaying (idk if clears batt/time info)
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