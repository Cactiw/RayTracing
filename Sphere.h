//
// Created by cactiw on 21.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_SPHERE_H
#define MACHINEGRAPHICS1TASK_SPHERE_H

#include "vector.cpp"


class Sphere {
    Vec3f center;
    float radius;

    Vec3f color;

public:

    Sphere(Vec3f center, float radius, Vec3f color) {
        this->center = center;
        this->radius = radius;
        this->color = color;
    }

    Vec3f getCenter();
    float getRadius();
    Vec3f getColor();

};


#endif //MACHINEGRAPHICS1TASK_SPHERE_H
