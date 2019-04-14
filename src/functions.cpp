#include "main.h"


int climb = 175; //182 measured
bool inAuto = false;
int autoCatMode = 0;// 0 is hold, 1 is arm, 2 is fire

int get_right_encoder(){
    int position = drive_right_1.get_position() + drive_right_2.get_position();
    return position;
}

int get_left_encoder(){
    int position = drive_left_1.get_position() + drive_left_2.get_position();
    return position;
}

int get_average_encoder(){
    int position = (get_left_encoder() + get_right_encoder() )/2;
    return position;
}

int inchesToDegrees(int inches){
    int degrees =( 360 * inches ) / (6.28);
    return degrees;
}

int degreesToTicks(int degrees){
    int ticks = (97/9) *degrees;
    return ticks;
}

void resetLeftEncoder(){
    drive_left_1.tare_position();
    drive_left_2.tare_position();
}

void resetRightEncoder(){
    drive_right_1.tare_position();
    drive_right_2.tare_position();
}

void resetDriveEncoder(){
    resetLeftEncoder();
    resetRightEncoder();
}

void setBrakeBrake(){
    drive_left_1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    drive_left_2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    drive_right_1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    drive_right_2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void setBrakeHold(){
    drive_left_1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    drive_left_2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    drive_right_1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    drive_right_2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void setBrakeCoast(){
    drive_left_1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    drive_left_2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    drive_right_1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    drive_right_2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void autoLCD(void* x){
    while(true){
        pros::lcd::print(2,"yaw value: %f", yaw.get_value());
        pros::delay(10);
    }
}



typedef struct {
    float current;
	float kP;
	float kI;
	float kD;
	float target;
	float integral;
	float error;
	float derivative;
	float lastError;
} PID;

PID sMovePid;

int iMovePid(int target){
    sMovePid.kP = 0.2;
    sMovePid.kI = 0;
    sMovePid.kD = 0.7;

    sMovePid.current = get_average_encoder();
    sMovePid.error = target - sMovePid.current;
    sMovePid.integral += sMovePid.error;
    sMovePid.derivative = sMovePid.error - sMovePid.lastError;
    sMovePid.lastError = sMovePid.error;

    return ( ((sMovePid.error)*(sMovePid.kP)) + ((sMovePid.derivative)*(sMovePid.kD)) + ((sMovePid.integral)*(sMovePid.kI)) );
}


void movePID(int distance){
    distance = inchesToDegrees(distance);
    int maxError = 10;
    int maxPower = 70;

    resetDriveEncoder();
    while( abs(get_average_encoder() - distance) > maxError ){
        int power = iMovePid(distance) < maxPower ? iMovePid(distance) : maxPower;
        set_left_drive(power);
        set_right_drive(power);
        pros::delay(10);
    }
    set_left_drive(0);
    set_right_drive(0);
}

PID sRotatePid;

int iRotatePid(int target){
    sRotatePid.kP = 0.3;
    sRotatePid.kI = 0;
    sRotatePid.kD = 2;

    sRotatePid.current = yaw.get_value();
    sRotatePid.error = target - sRotatePid.current;
    sRotatePid.integral += sRotatePid.error;
    sRotatePid.derivative = sRotatePid.error - sRotatePid.lastError;
    sRotatePid.lastError = sRotatePid.error;

    return ( ((sRotatePid.error)*(sRotatePid.kP)) + ((sRotatePid.derivative)*(sRotatePid.kD)) + ((sRotatePid.integral)*(sRotatePid.kI)) );
}


void rotatePID(int angle){
    angle = degreesToTicks(angle);
    int maxError = 20;
    int maxPower = 50;

    while( abs(yaw.get_value() - angle) > maxError ){
        int power = iRotatePid(angle) < maxPower ? iRotatePid(angle) : maxPower*(iRotatePid(angle)/abs(iRotatePid(angle)));
        set_left_drive( power);
        set_right_drive( -power);
        pros::delay(10);
    }
}

void catapultAuto(void* x){
    while(inAuto){
        if(autoCatMode == 1){
            while(catapult_limit.get_value() == false){
                catapult.move_voltage(127);
                pros::delay(10);
            }
            autoCatMode = 0;
        }
        else if(autoCatMode == 2){
            while(catapult_limit.get_value() == true){
                catapult.move_voltage(127);
                pros::delay(10);
            }
        }else{
            catapult.move_voltage(0);
        }
        pros::delay(10);
    }
}