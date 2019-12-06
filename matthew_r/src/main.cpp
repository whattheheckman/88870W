/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nathan Brown                                              */
/*    Created:      Sat Oct 05 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      LeftWheel(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor      RightWheel(vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor      LeftLift(vex::PORT9, vex::gearSetting::ratio36_1, false);
vex::motor      RightLift(vex::PORT10, vex::gearSetting::ratio36_1, true);
vex::motor      LeftClaw(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor      RightClaw(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::controller Controller1(vex::controllerType::primary);
//#endregion config_globals



int main() {
    
   
    
    //Use these variables to set the speed of the arm and claw.
    int liftSpeedPCT = 75;
    int clawSpeedPCT = 45;

    //Create an infinite loop so that the program can pull remote control values every iteration.
    //This loop causes the program to run forever.
    while(1) {

        //DRIVE CONTROL
        //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
        //Since we are using a single joystick, we will need to calculate the final volicity for each motor.
        LeftWheel.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()), vex::velocityUnits::pct); //(Axis3+Axis1)/2
        RightWheel.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);//(Axis3-Axis1)/2
        
        
        //LIFT CONTROL
        if(Controller1.ButtonR2.pressing()) {
          LeftLift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          RightLift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR1.pressing()) { 
          LeftLift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          RightLift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else {
          LeftLift.stop(vex::brakeType::hold);
          RightLift.stop(vex::brakeType::hold);
        }
        
            
        //CLAW CONTROL
        if(Controller1.ButtonL1.pressing()) { 
            LeftClaw.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
            RightClaw.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
            LeftClaw.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
            RightClaw.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);

        }
        else { 
            LeftClaw.stop(vex::brakeType::hold);     
            RightClaw.stop(vex::brakeType::hold);        
        }
        
		vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
        Controller1.Screen.clearScreen(); //clears controller screen unless something is displaying (idk if clears batt/time info)
    }

}
