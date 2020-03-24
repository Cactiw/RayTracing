//
// Created by cactiw on 24.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_LIGHT_H
#define MACHINEGRAPHICS1TASK_LIGHT_H


#include "Object.h"

class Light: public Object {
    float brightness;

public:
    Light(Vec3f position, float brightness);
};


#endif //MACHINEGRAPHICS1TASK_LIGHT_H
