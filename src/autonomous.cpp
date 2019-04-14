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
void autonomous() {
    inAuto = true;
    setBrakeBrake();
    pros::Task autoCat(catapultAuto, NULL);
    pros::Task LCDisplay(autoLCD, NULL);
    //pros::lcd::print(3, "Motor Power: %d", iMovePid(inchesToDegrees(34)));
    autoCatMode = 1;
    movePID(36);
    rotatePID(90);
    pros::lcd::print(4,"completed");
}
