#include "main.h"


int climb = 175; //182 measured
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
    if(!pros::lcd::is_initialized()){
        pros::lcd::initialize();
    }
    pros::lcd::clear();
    while(pros::competition::is_autonomous()){
        pros::lcd::print(2,"yaw value: %f", yaw.get_value());
        pros::lcd::print(3,"Pitch value: %f", pitch.get_value());
        pros::lcd::print(5, "Intake Mode: %d", intake_mode);
        pros::delay(20);
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
    sMovePid.kP = 0.6;
    sMovePid.kI = 0;
    sMovePid.kD = 1;

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
    int maxPower = 80;
    int minVelocity = 10;
    int timer = 0;
    bool exit = false;

    resetDriveEncoder();
    while( abs(get_average_encoder() - distance) > maxError && !exit){
        int PIDPower = iMovePid(distance);
        int power = abs(PIDPower) < maxPower ? PIDPower : maxPower*(PIDPower/ abs(PIDPower));
        set_left_drive(power);
        set_right_drive(power);
        if(timer > 200 && abs(drive_left_1.get_actual_velocity()) < minVelocity){
            exit = true;
        }
        pros::delay(10);
        timer +=10;
    }
    set_left_drive(0);
    set_right_drive(0);
}
void movePID(int distance, int maxPower){
    distance = inchesToDegrees(distance);
    int maxError = 10;
    int minVelocity = 10;
    int timer = 0;
    bool exit = false;

    resetDriveEncoder();
    while( abs(get_average_encoder() - distance) > maxError && !exit){
        int PIDPower = iMovePid(distance);
        int power = abs(PIDPower) < maxPower ? PIDPower : maxPower*(PIDPower/ abs(PIDPower));
        set_left_drive(power);
        set_right_drive(power);
        if(timer > 200 && abs(drive_left_1.get_actual_velocity()) < minVelocity){
            exit = true;
        }
        pros::delay(10);
        timer +=10;
    }
    set_left_drive(0);
    set_right_drive(0);
}

PID sRotatePid;

int iRotatePid(int target){
    sRotatePid.kP = 0.6;
    sRotatePid.kI = 0;
    sRotatePid.kD = 4;

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
    int maxPower = 80;
    int timer = 0;
    int minVelocity = 1;
    bool exit = false;

    sRotatePid.integral = 0;

    while( abs(yaw.get_value() - angle) > maxError && !exit){
        int PIDPower = iRotatePid(angle);
        int power = abs(PIDPower) < maxPower ? PIDPower : maxPower*(PIDPower/ abs(PIDPower));
        set_left_drive(power);
        set_right_drive(-power);

        if(timer > 200 && abs(drive_left_1.get_actual_velocity()) < minVelocity){
            exit = true;
        }
        pros::delay(10);
        timer += 10;
    }
    pros::lcd::print(5, "Difference: %d", abs(yaw.get_value() - angle));
    pros::lcd::print(6, "Target Angle %d", angle);
    set_left_drive(0);
    set_right_drive(0);
}

void rotatePID(int angle, int maxPower){
    angle = degreesToTicks(angle);
    int maxError = 50;
    int timer = 0;
    int minVelocity = 30;
    bool exit = false;

    while( abs(yaw.get_value() - angle) > maxError ){
        int PIDPower = iRotatePid(angle);
        int power = abs(PIDPower) < maxPower ? PIDPower : maxPower*(PIDPower/ abs(PIDPower));
        set_left_drive(power);
        set_right_drive(-power);
        if(timer > 200 && abs(drive_left_1.get_actual_velocity()) < minVelocity){
            exit = true;
        }
        pros::delay(10);
        timer += 10;
    }
    set_left_drive(0);
    set_right_drive(0);
}

void catapultAuto(void* x){
    while(pros::competition::is_autonomous()){
        if(autoCatMode == 1){
            armCatapult();
            autoCatMode = 0;
        }
        else if(autoCatMode == 2){
            fireCatapult();
            autoCatMode = 1;
        }else{
            catapult.move_voltage(0);
        }
        pros::delay(10);
    }
}

void intakeAuto(void *z){
    while(pros::competition::is_autonomous()){
        if(intake_mode == 1){
            intake.move_velocity(-500);        
            //in
        }
        else if(intake_mode == -1){
            intake.move_velocity(500);
            //out
        }
        else{
            intake.move_velocity(0);
        }
        pros::delay(10);
    }
}

void climbPlatform(){
    int highPitch = 120;
    int lowPitch = 50;
    int power1 = 120;
    int power2 = 90;
    setBrakeBrake();

    while(abs(pitch.get_value()) < highPitch){
        set_right_drive(power1);
        set_left_drive(power1);
        pros::delay(5);
    }
    while(abs(pitch.get_value()) > lowPitch ){
        set_right_drive(power2);
        set_left_drive(power2);
        pros::delay(5);
    }
    set_right_drive(0);
    set_left_drive(0);

}

void square(){
    int minVelocity = 2;
    set_left_drive(-70);
    set_right_drive(-70);
    pros::delay(100);
    while(abs(drive_left_2.get_actual_velocity()) > minVelocity || abs(drive_right_2.get_actual_velocity()) > minVelocity){
        pros::delay(10);
    }
    set_left_drive(0);
    set_right_drive(0);
}

void autoTimer(void *x){
    iAutoTimer = 0;
    while( pros::competition::is_autonomous()){
        pros::delay(10);
        iAutoTimer += 10;
    }
}