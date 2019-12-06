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
vex::motor      CenterWheel(vex::PORT3, vex::gearSetting::ratio18_1, true);
vex::motor      LeftLift(vex::PORT9, vex::gearSetting::ratio36_1, false);
vex::motor      RightLift(vex::PORT10, vex::gearSetting::ratio36_1, true);
vex::motor      ClawMotor(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::controller Controller1(vex::controllerType::primary);
vex::competition Competition;
//#endregion config_globals

void drivetrainBrake(){
    LeftWheel.stop(vex::brakeType::brake);
    RightWheel.stop(vex::brakeType::brake);
}

void CenterWheelBrake(){
    CenterWheel.stop(vex::brakeType::brake);
}

int main() {
    
   
    
    //Use these variables to set the speed of the arm and claw.
    int liftSpeedPCT = 75;
    int clawSpeedPCT = 50;
    int dpadSpeedPCT = 35;
    
    //Create an infinite loop so that the program can pull remote control values every iteration.
    //This loop causes the program to run forever.
    while(1) {

        //DRIVE CONTROL
        //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
        //Since we are using a single joystick, we will need to calculate the final volicity for each motor.
        LeftWheel.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()), vex::velocityUnits::pct); //(Axis3+Axis1)/2
        RightWheel.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);//(Axis3-Axis1)/2

        if (Controller1.ButtonB.pressing()) {         //DRIVETRAIN BRAKES
            Controller1.rumble("...");
            Controller1.Screen.print("CenterWheel BRAKE");
            CenterWheelBrake();
            CenterWheel.stop(vex::brakeType::brake);
        }
        
        
        
        //DRIVETRAIN DPAD
        if (Controller1.ButtonUp.pressing()) { //nudge fwd/rev
            LeftWheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
            RightWheel.spin(vex::directionType::fwd,dpadSpeedPCT,vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) {
            LeftWheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);
            RightWheel.spin(vex::directionType::rev,dpadSpeedPCT,vex::velocityUnits::pct);            
        }
        
        if (Controller1.ButtonLeft.pressing()) { //nudge left/right
            CenterWheel.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        }
        else if (Controller1.ButtonRight.pressing()) {
            CenterWheel.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        }
        
        Controller1.ButtonUp.released(drivetrainBrake);
        Controller1.ButtonDown.released(drivetrainBrake);
        Controller1.ButtonLeft.released(CenterWheelBrake);
        Controller1.ButtonRight.released(CenterWheelBrake);
        
        
        
        //LIFT CONTROL
        if(Controller1.ButtonR2.pressing()) {
          LeftLift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
          RightLift.spin(vex::directionType::fwd, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR1.pressing()) { 
          LeftLift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
          RightLift.spin(vex::directionType::rev, liftSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonY.pressing()) {
          LeftLift.stop(vex::brakeType::brake);
          RightLift.stop(vex::brakeType::brake);
        }
        else {
          LeftLift.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
          RightLift.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
        }
        
            
        //CLAW CONTROL
        if(Controller1.ButtonL1.pressing()) { 
            ClawMotor.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
            ClawMotor.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { 
            ClawMotor.stop(vex::brakeType::brake);        
        }
        
		vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    }

}