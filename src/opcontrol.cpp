#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	pros::Task control_catapult(catapult_control, NULL);
	pros::Task control_arcade(arcade_control, NULL);
	pros::Task control_intake(intake_control, NULL);
	pros::Task control_armbar(arm_bar_control, NULL);
	pros::Task control_brake(brake_control, NULL);
	arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	setBrakeBrake();

	/*if(!pros::lcd::is_initialized()){
        pros::lcd::initialize();
    }*/
	while (true) {
		
		//pros::lcd::print(1,"Yaw Value: %f", yaw.get_value() );
		//pros::lcd::print(2,"Pitch Value: %f", pitch.get_value() );
		
		if(master.get_digital(DIGITAL_A) ){
			rotatePID(90);
		}

		pros::delay(10);
	}
}
