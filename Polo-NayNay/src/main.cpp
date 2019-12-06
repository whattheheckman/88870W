/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nathan Brown                                              */
/*    Created:      Tue Oct 22 2019                                           */
/*    Description:  Polo and NayNay's Robot                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

vex::competition Competition;
vex::motor left_Wheel(vex::PORT1, vex::gearSetting::ratio36_1, false);
vex::motor right_Wheel(vex::PORT2, vex::gearSetting::ratio36_1, true);
vex::motor lyft(vex::PORT3, vex::gearSetting::ratio36_1, true);
vex::motor top_Left(vex::PORT4, vex::gearSetting::ratio36_1, false);
vex::motor top_Right(vex::PORT5, vex::gearSetting::ratio36_1, true);
vex::motor left_Tickler(vex::PORT6, vex::gearSetting::ratio36_1, false);
vex::motor right_Tickler(vex::PORT7, vex::gearSetting::ratio36_1, true);
vex::controller Controller1(vex::controllerType::primary);

void drivetrainBrake(){
  left_Wheel.stop(vex::brakeType::brake);
  right_Wheel.stop(vex::brakeType::brake);
}

int liftSpeedPCT = 100;
int clawSpeedPCT = 50;
int dpadSpeedPCT = 100;
int intakeSpeedPCT = 100;
int rotateSpeedPCT = 75;
int clampPCT = 35;
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
  left_Wheel.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  right_Wheel.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(3000);
  left_Wheel.spin(vex::directionType::rev, 75 , vex::velocityUnits::pct); 
  right_Wheel.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::this_thread::sleep_for(2000);
}

//Driver Code
void usercontrol( void ) {
  while (1) {
    left_Wheel.spin(vex::directionType::fwd, ((Controller1.Axis3.value() + Controller1.Axis1.value())  * joyspeedMod), vex::velocityUnits::pct); //(Axis3+Axis1)/2
    right_Wheel.spin(vex::directionType::fwd, ((Controller1.Axis3.value() - Controller1.Axis1.value()) * joyspeedMod), vex::velocityUnits::pct);//(Axis3-Axis1)/2

       //DRIVETRAIN DPAD
       if (Controller1.ButtonUp.pressing()) { //nudge fwd/rev
          left_Wheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
          right_Wheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) {
          left_Wheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);
          right_Wheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);            
        }
        
        Controller1.ButtonUp.released(drivetrainBrake);
        Controller1.ButtonDown.released(drivetrainBrake);
                
        //INTAKE CONTROL
        if(Controller1.ButtonR1.pressing()) {
          left_Tickler.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          right_Tickler.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing()) { 
          left_Tickler.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          right_Tickler.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          left_Tickler.stop(vex::brakeType::hold);
          right_Tickler.stop(vex::brakeType::hold);
        }

        //SCISSOR CONTROL
        if(Controller1.ButtonL1.pressing()) {
          top_Left.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          top_Right.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
          top_Left.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          top_Right.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          top_Left.stop(vex::brakeType::hold);
        }
        
        //Intake Rotato
        if(Controller1.ButtonX.pressing()) { 
          lyft.spin(vex::directionType::fwd, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonB .pressing()) { 
          lyft.spin(vex::directionType::rev, rotateSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
          lyft.stop(vex::brakeType::hold);        
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