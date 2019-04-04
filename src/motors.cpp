#include "main.h"

//Global Variables
int intake_mode = 0;// 0 is off || 1 is on || -1 is reverse
bool fire_catapult = false;
double slow_mode = 0.75;
double d_max_volt = 127;
int i_encoder_port = 20;

//controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

//Motors:
pros::Motor catapult(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_left(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_right(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor drive_right_1(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);//back
pros::Motor drive_right_2(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);//front

pros::Motor drive_left_1(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);//back
pros::Motor drive_left_2(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);//front

//Sensor
pros::ADIDigitalIn catapult_limit('h');

void set_right_drive(int volt){
    drive_right_1.move(volt);
    drive_right_2.move(volt);
}

void set_left_drive(int volt){
    drive_left_1.move(volt);
    drive_left_2.move(volt);
}

void set_arm_bar(int volt){
    arm_left.move(volt);
    arm_right.move(volt);
}

void arcade_control(void *X){
    while(true){
        int deadzone = 20;
        int slowzone = 30;

        int left = master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_X);
        int right = master.get_analog(ANALOG_RIGHT_Y) - master.get_analog(ANALOG_RIGHT_X);

        int left_power = abs(left) > deadzone ? left : 0;
        int right_power = abs(right) > deadzone ? right : 0;
        float power_adjust = 0.985;

        if(master.get_digital(DIGITAL_UP)){
            //turbo mode
            set_left_drive(left_power );
            set_right_drive(right_power);
        }else{
            //normal mode
            set_right_drive(right_power * slow_mode);
            set_left_drive(left_power * slow_mode);
        }
        pros::delay(10);
    }
}

void catapult_control(void *y){
    while(true){
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            catapult.move(d_max_volt);
        }
        else if(!catapult_limit.get_value()){
            catapult.move(d_max_volt);
        }
        else{
            catapult.move(0);
        }
        pros::delay(10);
    }
}

void intake_control(void *z){
    while(true){
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            intake.move(-d_max_volt);
            //in
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            intake.move(d_max_volt);
            //out
        }
        else{
            intake.move(0);
        }

        pros::delay(10);
    }
}

void arm_bar_control(void *w){
    int deadzone = 20;

    //int power = abs( master.get_analog(ANALOG_LEFT_Y) ) > deadzone ? master.get_analog(ANALOG_LEFT_Y) : 0;
    while(true){
        set_arm_bar(master.get_analog(ANALOG_LEFT_Y));
        pros::delay(10);
    }
}
