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
    rotatePID(-90);

    movePID(-6);
    fireCatapult();
    armCatapult();
    movePID(12);
    rotatePID(-35);
    movePID(17.75,50);
    pros::delay(500);
    movePID(-6);
    pros::delay(250);
    movePID(-2);
    pros::delay(1000);
    fireCatapult();
}

void blueFront(){
    armCatapult();
    intake_mode = 1;
    movePID(-12);
    movePID(45);//to cap
    movePID(-52);
    movePID(5);
    rotatePID(90);//back up to align
    movePID(-6);
    fireCatapult();
    intake_mode = 1;
    armCatapult();
    movePID(7.8);//to cap
    rotatePID(35);
    movePID(17.75, 50);
    pros::delay(500);
    movePID(-6);
    pros::delay(250);
    movePID(-2);
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
    rotatePID(98);
    fireCatapult();
    armCatapult();

    movePID(-30);
    reset_arm_encoder();
    movePID(3);
    rotatePID(180);
    movePID(-24);
    movePID(-5, 50);
    pros::delay(200);
    set_arm_angle(2, 50);
    set_arm_bar(0);
    pros::delay(200);
    movePID(16,50);
    rotatePID(270);
    movePID(5);
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
    //redFront();
    //blueFront();
    //blueBack();
    //redBack();
    //climbPlatform();
    //rotatePID(-370);
    pros::lcd::print(7,"completed");
}
