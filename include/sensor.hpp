#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_
#include "main.h"

extern bool fire_catapult;
extern double slow_mode;
extern double d_max_volt;
extern int i_encoder_port;
extern int autoCatMode;

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
extern pros::ADIGyro yaw;
extern pros::ADIGyro pitch;



#endif