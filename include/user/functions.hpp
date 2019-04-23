#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

extern int intake_mode;


//Functions
int get_arm_position();

int get_right_encoder();
int get_left_encoder();

int inchesToDegrees(int inches);

void set_right_drive(int volt);
void set_left_drive(int volt);

void setBrakeBrake();
void setBrakeHold();
void setBrakeCoast();

void reset_arm_encoder();

void set_arm_bar(int volt);
void set_arm_angle(int position, int power);
void set_arm_angle(int position);

void autoLCD(void* x);

void arcade_control(void *x);
void catapult_control(void *y);
void intake_control(void *z);
void arm_bar_control(void *W);

void catapultAuto(void *y);
void intakeAuto(void *z);

void armCatapult();
void fireCatapult();

void movePID(int distance);
void movePID(int distance, int maxPower);
void rotatePID(int target);

void rotatePID(int angle);

void climbPlatform();

#endif