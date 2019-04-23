#include "main.h"

//Global Variables
int intake_mode = 0;// 0 is off || 1 is on || -1 is reverse
bool fire_catapult = false;
double slow_mode = 0.75;
double d_max_volt = 127;
int i_encoder_port = 20;

float angle[4] = {
    0, //bottom
    224,//flat
    475, // up 45 deg
    858 //scored
};



//controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

//Motors:
pros::Motor catapult(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_left(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_right(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor drive_right_1(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);//back
pros::Motor drive_right_2(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);//front

pros::Motor drive_left_1(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);//back
pros::Motor drive_left_2(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);//front

//Sensor
pros::ADIDigitalIn catapult_limit('h');
pros::ADIGyro yaw('e', 1);
pros::ADIGyro pitch('f', 1);


int get_arm_position(){
    int position = arm_left.get_position() + arm_right.get_position();
    position = position/2;
    return position;
}

bool buttonPress(){
    if(master.get_digital(DIGITAL_DOWN) || master.get_digital(DIGITAL_RIGHT) || master.get_digital(DIGITAL_LEFT)){
        return true;
    }else{
        return false;
    }
}

void reset_arm_encoder(){
    arm_left.tare_position();
    arm_right.tare_position();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

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
void armCatapult(){    
    while(!catapult_limit.get_value()){
        catapult.move(d_max_volt);
        pros::lcd::set_text(4, "arming Catapult");
        pros::delay(10);
    }
    pros::lcd::set_text(4, "finished Catapult");
    catapult.move(0);
}

void fireCatapult(){    
    for(int i = 0; i<=40; i++){
        catapult.move_velocity(75);
        pros::delay(10);
    }
    catapult.move(0);
}

void catapult_control(void *y){
    armCatapult();
    while(true){
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            fireCatapult();
            armCatapult();
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            armCatapult();
        }
        else{
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

void set_arm_angle(int position){
    int timer = 0;
    int deadzone = 20;
    int power = 100;
    int current_position = get_arm_position();
    if(position == 0){
        while(abs( master.get_analog(ANALOG_LEFT_Y) ) < deadzone && get_arm_position() > 10 ){
            set_arm_bar(-power);
            pros::delay(10);
        }
        reset_arm_encoder();
    }else{
        while(abs( master.get_analog(ANALOG_LEFT_Y) ) < deadzone && abs(get_arm_position() - angle[position]) > 20){
            if(current_position > angle[position]){
                set_arm_bar(-power);
            }else{
                set_arm_bar(power);
            }
            pros::delay(10);
        }
    }
}

void set_arm_angle(int position, int power){
    int timer = 0;
    int deadzone = 20;
    int current_position = get_arm_position();
    if(position == 0){
        while(abs( master.get_analog(ANALOG_LEFT_Y) ) < deadzone && get_arm_position() > 10 ){
            set_arm_bar(-power);
            pros::delay(10);
        }
        reset_arm_encoder();
    }else{
        while(abs( master.get_analog(ANALOG_LEFT_Y) ) < deadzone && abs(get_arm_position() - angle[position]) > 20){
            if(current_position > angle[position]){
                set_arm_bar(-power);
            }else{
                set_arm_bar(power);
            }
            pros::delay(10);
        }
    }
}

void arm_bar_control(void *w){
    int deadzone = 20;

    //int power = abs( master.get_analog(ANALOG_LEFT_Y) ) > deadzone ? master.get_analog(ANALOG_LEFT_Y) : 0;
    while(true){
        if(  abs( master.get_analog(ANALOG_LEFT_Y) ) > deadzone){
            set_arm_bar(master.get_analog(ANALOG_LEFT_Y));
        }else{
            if( master.get_digital(DIGITAL_LEFT) ){
                set_arm_angle(1);
            }else if( master.get_digital(DIGITAL_DOWN) ){
                set_arm_angle(0);
            }else if( master.get_digital(DIGITAL_RIGHT) ){
                set_arm_angle(2,50);
            }else{
                set_arm_bar(0);
            }
        }
        pros::delay(10);
    }
}