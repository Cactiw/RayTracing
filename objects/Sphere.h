//
// Created by cactiw on 21.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_SPHERE_H
#define MACHINEGRAPHICS1TASK_SPHERE_H

#include "../vector.cpp"
#include "../classes/Ray.h"
#include "Object.h"
#include "../classes/Color.h"

class Sphere : public Object{
    float radius;
    float radius2;

public:

    Sphere(Vec3f ctr, Color clr, float radius) : Object(ctr, clr) {
        this->radius = radius;
        this->radius2 = radius * radius;
    }

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] float check_intersect(const Ray &ray) const override;

};


#endif //MACHINEGRAPHICS1TASK_SPHERE_H
