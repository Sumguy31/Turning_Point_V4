#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_
#include "main.h"

class armBar
{ public:

    double angle;
    
    void setArmBar(int voltage){
        arm_left.move(voltage);
        arm_right.move(voltage);
    }

};


#endif