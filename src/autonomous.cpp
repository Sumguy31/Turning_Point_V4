#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

int iAutoTimer;
void redFront(){
    //armCatapult();
    autoCatMode = 1;
    intake_mode = 1;
    pros::delay(300);
    movePID(-8);
    square();
    movePID(43);
    movePID(-43);
    square();
    movePID(3);
    rotatePID(-87);

    movePID(-6);
    pros::delay(700);
    //fireCatapult();
    //armCatapult();
    autoCatMode = 2;
    pros::delay(600);
    rotatePID(-100);
    intake_mode= 1;
    movePID(70);
    movePID(-22);
    rotatePID(0);
    intake_mode = -1;
    square();
    movePID(24);
    //rotatePID(-22);
    movePID(-24);
    square();
    rotatePID(-90);
    movePID(-46);
    rotatePID(0);
    square();
    //climbPlatform();
                while(inchesToDegrees(45) > get_average_encoder()){
                set_right_drive(100);
                set_left_drive(100);
            }
    set_left_drive(0);
    set_right_drive(0);
    /*pros::delay(300);
    movePID(8,40);
    movePID(-4.5);
    rotatePID(-49);  */
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
    autoCatMode = 2;
    //fireCatapult();
    /*Scrape and score
    movePID(13.5);
    rotatePID(-40);
    movePID(16.25,40);
    pros::delay(250);
    movePID(-4);
    pros::delay(1000);
    fireCatapult();*/
}

void blueFront(){
    //armCatapult();
    autoCatMode = 1;
    intake_mode = 1;
    pros::delay(300);
    movePID(-8);
    square();
    movePID(43);//to cap
    movePID(-43);
    square();
    movePID(3);
    rotatePID(88);//back up to align
    movePID(-6);
    pros::delay(300);
    //fireCatapult();
    //armCatapult();
    autoCatMode = 2;
    pros::delay(300);
    //flag and tag
    rotatePID(95);
    intake_mode = 1;
    movePID(70);
    movePID(-24);
    rotatePID(0);
    intake_mode = -1;
    square();
    movePID(24);
    rotatePID(16.5);
    //fireCatapult();
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
    autoCatMode = 2;
    pros::delay(400);

    /* //Scrape and score
    movePID(9);//to cap
    rotatePID(35);
    movePID(15.75, 40);
    pros::delay(500);
    movePID(-6);
    pros::delay(1000);
    fireCatapult();*/
    //////////////////////////////////////////////////
}

void redBack(){
    autoCatMode = 1;
    intake_mode = 1;
    pros::delay(300);
    movePID(-8);
    square();
    movePID(43);   
    movePID(-43);
    square();
    rotatePID(-95);
    movePID(25.5);
    rotatePID(0);
    intake_mode = 0;
    square();
    climbPlatform();
    movePID(2);
    pros::delay(1000);
    movePID(8,40);
    movePID(-4.5);
    rotatePID(-49);     
    /*movePID(-9);
    pros::delay(500);
    rotatePID(-95);
    climbPlatform();
    pros::delay(300);
    movePID(3.5);
    rotatePID(-48);
    movePID(2);*/
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
    autoCatMode = 2;
}

void blueBack(){
    intake_mode = 1;
    //armCatapult();
    autoCatMode = 1;
    pros::delay(300);
    movePID(-8);
    square();
    movePID(43);
    movePID(-10);
    pros::delay(100);
    rotatePID(90);
    climbPlatform();
    pros::delay(1000);
    movePID(2);
    rotatePID(45);
    movePID(1);
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
   autoCatMode = 2;
}

void flagTagBlue(){
    arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    //armCatapult();
    autoCatMode = 1;
    movePID(-36, 60);
    movePID(-5, 40);
    pros::delay(300);
    set_arm_angle(2,50);
    set_arm_bar(0);
    movePID(19.5);
    rotatePID(120);
    movePID(17);
    set_arm_angle(3);
    set_arm_bar(0);
    pros::delay(300);
    movePID(-12);
    set_arm_angle(0);
    set_arm_bar(0);
    movePID(-8);
    rotatePID(30);
    movePID(-16);
    rotatePID(-73);
    climbPlatform();
    rotatePID(-108);
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
    autoCatMode = 2;
    //fireCatapult();
}

void flagTagRed(){
    arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    autoCatMode = 1;
    movePID(-36, 60);
    movePID(-5, 40);
    pros::delay(300);
    set_arm_angle(2,50);
    set_arm_bar(0);
    movePID(19.5);
    rotatePID(-120);
    movePID(17);
    set_arm_angle(3);
    set_arm_bar(0);
    movePID(-8);
    rotatePID(73);
    climbPlatform();
    rotatePID(108);
    while(iAutoTimer < 14200){
        pros::delay(5);
    }
    autoCatMode = 2;
}
void autonomous() {
    //yaw.reset();
    //pitch.reset();
    pros::Task autoIntake(intakeAuto, NULL);
    //pros::Task LCDisplay(autoLCD, NULL);
    setBrakeBrake();
    pros::Task cataAuto(catapultAuto, NULL);
    pros::Task timeAuto(autoTimer, NULL);
    /*if(autonNumber == 2 || autonNumber == 4){
        pros::Task cataTimer(fireLast, NULL);
    }*/
    //pros::Task autoCatapult(catapultAuto, NULL);
    switch (autonNumber){
        case 0:
            //test function

            break;
        
        case 1:
            redFront();
            break;

        case 2:
            redBack();
            break;

        case 3:
            blueFront();
            break;

        case 4:
            blueBack();
            //flagTagBlue();

            break;
        default:
            break;
    }
    //blueFront();
    //blueBack();
    //redBack();
    //climbPlatform();
    //rotatePID(-370);
    pros::lcd::print(7,"completed");
}
