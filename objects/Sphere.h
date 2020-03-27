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

    Sphere(Vec3f center, Material material, float radius) : Object(center, material) {
        this->radius = radius;
        this->radius2 = radius * radius;
    }

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] float check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal) const override;

};


#endif //MACHINEGRAPHICS1TASK_SPHERE_H
