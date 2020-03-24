//
// Created by cactiw on 23.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_OBJECT_H
#define MACHINEGRAPHICS1TASK_OBJECT_H

#include "../vector.cpp"
#include "../classes/Ray.h"
#include "../classes/Color.h"


class Object {
    Vec3f center;
    Color color;

public:
    Object(Vec3f ctr, Color clr): center(ctr), color(clr) {}

    [[nodiscard]] virtual float check_intersect(const Ray &ray) const {return -1;};

    [[nodiscard]] Vec3f getCenter() const;
    [[nodiscard]] Color getColor() const;
};


#endif //MACHINEGRAPHICS1TASK_OBJECT_H
