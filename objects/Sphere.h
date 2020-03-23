//
// Created by cactiw on 21.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_SPHERE_H
#define MACHINEGRAPHICS1TASK_SPHERE_H

#include "../vector.cpp"
#include "../classes/Ray.h"
#include "Object.h"

class Sphere : public Object{
    Vec3f center;
    float radius;

    Vec3f color;

public:

    Sphere(Vec3f ctr, Vec3f clr, float radius) : Object(ctr, clr) {
        this->radius = radius;
    }

    [[nodiscard]] Vec3f getCenter() const;
    [[nodiscard]] float getRadius() const;

    [[nodiscard]] float check_intersect(const Ray &ray) const override;

};


#endif //MACHINEGRAPHICS1TASK_SPHERE_H
