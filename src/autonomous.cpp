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
void redFront(){
    armCatapult();
    intake_mode = 1;
    movePID(-12);
    movePID(45);
    movePID(-52);
    movePID(5);
    rotatePID(-95);

    movePID(-6);
    pros::delay(500);
    fireCatapult();
    armCatapult();
    movePID(13.5);
    rotatePID(-40);
    movePID(16.25,40);
    pros::delay(250);
    movePID(-4);
    pros::delay(1000);
    fireCatapult();
}

void blueFront(){
    armCatapult();
    intake_mode = 1;
    movePID(-12);
    movePID(48);//to cap
    movePID(-52);
    movePID(5);
    rotatePID(90);//back up to align
    movePID(-6);
    pros::delay(500);
    fireCatapult();
    pros::delay(100);
    armCatapult();
    movePID(9);//to cap
    rotatePID(35);
    movePID(15.75, 40);
    pros::delay(500);
    movePID(-6);
    pros::delay(1000);
    fireCatapult();
}

void redBack(){
    arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    armCatapult();
    intake_mode = 1;
    movePID(-12);
    movePID(45);
    movePID(-52);
    movePID(6);
    rotatePID(-98);
    fireCatapult();
    armCatapult();

    movePID(-30);
    reset_arm_encoder();
    movePID(3);
    rotatePID(-185);
    movePID(-24);
    movePID(-5, 50);
    pros::delay(200);
    set_arm_angle(2, 50);
    set_arm_bar(0);
    pros::delay(200);
    movePID(13,50);
    rotatePID(-285);
    movePID(5);
    set_arm_angle(3);
    set_arm_bar(0);

    movePID(-24);
    rotatePID(-225);
    movePID(-12,80);
    rotatePID(-270);
    climbPlatform();
}

void blueBack(){
    arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    armCatapult();
    intake_mode = 1;
    movePID(-12);
    movePID(45);
    movePID(-52);
    movePID(6);
    rotatePID(92);
    fireCatapult();
    armCatapult();

    movePID(-36);
    reset_arm_encoder();
    movePID(3);
    rotatePID(183);
    movePID(-28);
    movePID(-5, 50);
    pros::delay(200);
    set_arm_angle(2, 50);
    set_arm_bar(0);
    pros::delay(200);
    rotatePID(160);
    movePID(25,50);
    rotatePID(270);
    movePID(7);
    set_arm_angle(3);
    set_arm_bar(0);

    movePID(-12);
    rotatePID(40);
    movePID(16,80);
    rotatePID(90);
    climbPlatform();
}

void autonomous() {
    //yaw.reset();
    //pitch.reset();
    setBrakeBrake();
    pros::Task autoIntake(intakeAuto, NULL);
    pros::Task LCDisplay(autoLCD, NULL);
    //pros::Task autoCatapult(catapultAuto, NULL);
    redFront();
    //blueFront();
    //blueBack();
    //redBack();
    //climbPlatform();
    //rotatePID(-370);
    pros::lcd::print(7,"completed");
}
