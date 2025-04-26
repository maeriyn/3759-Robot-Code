#include "main.h"
#include "eternal/api.hpp"
#include "eternal/logger/stdout.hpp"
#include "pros/misc.h"


// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);


// drive motors
pros::Motor lF(-18, pros::E_MOTOR_GEARSET_06); // left front motor. port 8, reversed
pros::Motor lM(-19, pros::E_MOTOR_GEARSET_06); // left middle motor. port 20, reversed
pros::Motor lB(-20, pros::E_MOTOR_GEARSET_06); // left back motor. port 19
pros::Motor rF(1, pros::E_MOTOR_GEARSET_06); // right front motor. port 2
pros::Motor rM(2, pros::E_MOTOR_GEARSET_06); // right middle motor. port 11
pros::Motor rB(9, pros::E_MOTOR_GEARSET_06); // right back motor. port 13, reversed


// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group


// Inertial Sensor on port 11
pros::Imu imu(14);


// tracking wheels
pros::Rotation horizontalEnc(11, true);
// horizontal tracking wheel. 2.75" diameter, 3.7" offset, back of the robot
eternal::TrackingWheel horizontal(&horizontalEnc, eternal::Omniwheel::NEW_275, 2);






int pintake = 17;
int pcatapult = -15;


pros::Motor catapult(pcatapult, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor intake(pintake, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);






pros::ADIDigitalOut IntakePneumatic1(2);
pros::ADIDigitalOut IntakePneumatic2(3);
pros::ADIDigitalOut wingpneumatic(1);
pros::ADIDigitalOut LiftPneumatic1(6);
pros::ADIDigitalOut LiftPneumatic2(5);
pros::ADIDigitalOut hangpneumatic(4);






// drivetrain settings
eternal::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11, // 10 inch track width
                              eternal::Omniwheel::NEW_325, // using new 3.25" omnis
                              360, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);


// lateral motion controller
eternal::ControllerSettings linearController(10, // proportional gain (kP)
                                            30, // derivative gain (kD)
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);


// angular motion controller
eternal::ControllerSettings angularController(2, // proportional gain (kP)
                                             10, // derivative gain (kD)
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             20 // maximum acceleration (slew)
);




eternal::OdomSensors sensors(&horizontal, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


// create the chassis
eternal::Chassis chassis(drivetrain, linearController, angularController, sensors);




void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
hangp_down();
intakep_up();




    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        eternal::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            eternal::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}


/**
 * Runs while the robot is disabled
 */
void disabled() {}


/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {






}


// get a path used for pure pursuit


ASSET(example_txt);








//example stuff:


/*
        //chassis.waitUntilDone();
    // chassis.moveToPose(20, 15, 90, 4000);
    // example movement: Turn to face the point x:45, y:-45. Timeout set to 1000
    // dont turn faster than 60 (out of a maximum of 127)
   // chassis.turnTo(45, -45, 1000, true, 60);
    // example movement: Follow the path in path.txt. Lookahead at 15, Timeout set to 4000
    // following the path with the back of the robot (forwards = false)
 
   
    chassis.follow(example_txt, 15, 4000, false);
    // wait until the chassis has travelled 10 inches. Otherwise the code directly after
    // the movement will run immediately
    // Unless its another movement, in which case it will wait
    chassis.waitUntil(10);


    */






void autonomous() {
   
    ////////////////////////////////////////////////////
    //////////////matchload side auton//////////////////
    ////////////////////////////////////////////////////
    /*
intakep_down();
   chassis.setPose(-32, -55, 0);
 chassis.moveToPose(-32, -10, 0, 3000);
  chassis.waitUntilDone();
 chassis.turnTo(-68, -12, 1000, true, 90);
  chassis.waitUntilDone();
  pros::delay(150);
  intake = -50;
 chassis.moveToPose(-42, -10, -90, 1000, 0, 0,6, 90);
  chassis.waitUntilDone();
pros::delay(550);
  chassis.moveToPose(-20, -12, -90, 2500, false);
  chassis.waitUntilDone();
  pros::delay(500);
  intake = 0;
    chassis.moveToPose(-42, -56, -138, 3500);
  chassis.waitUntilDone();
  hangp_up();
  pros::delay(500);
 
   chassis.turnTo(0, -60, 1000, true, 80);
  chassis.waitUntilDone();
  pros::delay(500);
  hangp_down();
   chassis.moveToPose(-7, -54, 91, 3500);  




*/


    ////////////////////////////////////////////////////
    //////////////opposite side auton///////////////////
    ////////////////////////////////////////////////////




   chassis.setPose(32, -55, 0);
   intakep_down();
   intake = 25;
 chassis.moveToPose(32, -10, 0, 3000);
  chassis.waitUntilDone();
 chassis.turnTo(68, -10, 1000, true, 90);
  chassis.waitUntilDone();
  pros::delay(150);
  intake = -50;
 chassis.moveToPose(48, -10, 90, 2500, 0, 0,6, 120);
  chassis.waitUntilDone();
pros::delay(550);
chassis.moveToPose(20, -12, 225, 2500, false);
chassis.waitUntilDone();
  pros::delay(500);
chassis.moveToPose(4, -38, 225, 1500);
chassis.waitUntilDone();
  pros::delay(500);









}


/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors
    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.arcade(leftY, rightX);


        moveIntake();
        cata_task();
        intakep_control();


        wingp_control();
        wing2p_control();
        hangp_control();


        // delay to save resources
        pros::delay(10);
    }
}


void moveIntake() {


bool getIntake = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
bool getOuttake = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);


const int intakespeed = 127;


  if((getIntake)){


  intake = -intakespeed;


  } else if(getOuttake) {


  intake = intakespeed;


  } else {


  intake = 0;


  }


}




void cata_task(){


bool getLaunch = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);


const int cataspeed = -127;


if (getLaunch){


catapult = cataspeed;


} else {


catapult = 0;


}
}




    /***************************************************************************************
    - pneumatic control                                                               *
    ***************************************************************************************/


    int intakep_intakep  = 0;
    bool intakep_toggle = true;




    void set_intakep(bool in) {
       intakepneumatic.set_value(in);
     
        }


    void intakep_up()   {
      set_intakep(false);
      intakep_toggle = true;
    }


    void intakep_down() {
      set_intakep(true);
      intakep_toggle = false;
    }


    void
    intakep_control() {
      if (controller.get_digital(DIGITAL_LEFT) && intakep_intakep==0) {
        intakep_toggle = !intakep_toggle;
    intakep_intakep = 1;
      }
      else if (!controller.get_digital(DIGITAL_LEFT)) {
        intakep_intakep = 0;
      }


      if (intakep_toggle)
        intakep_up();
      else
        intakep_down();
    }


   
////////////////////////////////////////////////////


         int wingp_wingp  = 0;
    bool wingp_toggle = true;








    void set_wingp(bool in)
    {
     frontwingpneumatic1.set_value(in);
     frontwingpneumatic2.set_value(in);
     }




    void wingp_up()   {
      set_wingp(false);
      wingp_toggle = true;
    }




    void wingp_down() {
      set_wingp(true);
      wingp_toggle = false;
    }




    void
    wingp_control() {
      if (controller.get_digital(DIGITAL_R2) && wingp_wingp==0) {
        wingp_toggle = !wingp_toggle;
    wingp_wingp = 1;
      }
      else if (!controller.get_digital(DIGITAL_R2)) {
        wingp_wingp = 0;
      }




      if (wingp_toggle)
        wingp_up();
      else
        wingp_down();
    }






///////////////////////////////////////////////
    int wing2p_wing2p  = 0;
    bool wing2p_toggle = true;








    void set_wing2p(bool in)
    {
     backwingpneumatic1.set_value(in);
     backwingpneumatic2.set_value(in);
     }




    void wing2p_up()   {
      set_wing2p(false);
      wing2p_toggle = true;
    }




    void wing2p_down() {
      set_wing2p(true);
      wing2p_toggle = false;
    }




    void
    wing2p_control() {
      if (controller.get_digital(DIGITAL_UP) && wing2p_wing2p==0) {
        wing2p_toggle = !wing2p_toggle;
    wing2p_wing2p = 1;
      }
      else if (!controller.get_digital(DIGITAL_DOWN)) {
        wing2p_wing2p = 0;
      }




      if (wing2p_toggle)
        wing2p_up();
      else
        wing2p_down();
    }






///////////////////////////////////////////////
    int hangp_hangp  = 0;
    bool hangp_toggle = true;








    void set_hangp(bool in) {
       hangpneumatic1.set_value(in);
       hangpneumatic2.set_value(in);
        }




    void hangp_up()   {
      set_hangp(false);
      hangp_toggle = true;
    }




    void hangp_down() {
      set_hangp(true);
      hangp_toggle = false;
    }




    void
    hangp_control() {
      if (controller.get_digital(DIGITAL_RIGHT) && hangp_hangp==0) {
        hangp_toggle = !hangp_toggle;
    hangp_hangp = 1;
      }
      else if (!controller.get_digital(DIGITAL_RIGHT)) {
        hangp_hangp = 0;
      }




      if (hangp_toggle)
        hangp_up();
      else
        hangp_down();
    }





