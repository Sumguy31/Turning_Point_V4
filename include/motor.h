#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"

extern bool fire_catapult;
extern double slow_mode;
extern double d_max_volt;
extern int i_encoder_port;

//motor predeclarations
extern pros::Motor catapult;
extern pros::Motor intake;
extern pros::Motor arm_left;
extern pros::Motor arm_right;
extern pros::Motor drive_right_1;
extern pros::Motor drive_right_2;
extern pros::Motor drive_left_1;
extern pros::Motor drive_left_2;


//Controler predeclaration
extern pros::Controller master;

//Sensor predeclaration
extern pros::ADIDigitalIn catapult_limit;

//Functions

void set_arm_bar(int volt);
void set_right_drive(int volt);
void set_left_drive(int volt);
void arcade_control(void *x);
void catapult_control(void *y);
void intake_control(void *z);
void arm_bar_control(void *W);

void t_intake_auto(void *x);
void t_catapult_auto(void *y);

#endif