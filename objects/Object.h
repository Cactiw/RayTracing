//
// Created by cactiw on 23.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_OBJECT_H
#define MACHINEGRAPHICS1TASK_OBJECT_H

#include "../vector.cpp"


class Object {
    Vec3f center;
    Vec3f color;

public:
    Object(Vec3f &ctr, Vec3f &clr): center(ctr), color(clr) {}

    virtual float check_intersect() = 0;
};


#endif //MACHINEGRAPHICS1TASK_OBJECT_H
