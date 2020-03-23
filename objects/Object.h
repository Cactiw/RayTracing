//
// Created by cactiw on 23.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_OBJECT_H
#define MACHINEGRAPHICS1TASK_OBJECT_H

#include "../vector.cpp"
#include "../classes/Ray.h"


class Object {
    Vec3f center;
    Vec3f color;

public:
    Object(Vec3f ctr, Vec3f clr): center(ctr), color(clr) {}

    [[nodiscard]] virtual float check_intersect(const Ray &ray) const {return -1;};

    [[nodiscard]] Vec3f getColor() const;
};


#endif //MACHINEGRAPHICS1TASK_OBJECT_H
