//
// Created by cactiw on 23.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_RAY_H
#define MACHINEGRAPHICS1TASK_RAY_H

#include "../computations/vector.cpp"


class Ray {
    Vec3f beginPoint;
    Vec3f targetPoint;
    Vec3f direction;

public:
    Ray(Vec3f bp, Vec3f tp);

    [[nodiscard]] Vec3f getBeginPoint() const;
    [[nodiscard]] Vec3f getTargetPoint() const;
    [[nodiscard]] Vec3f getDirection() const;
};


#endif //MACHINEGRAPHICS1TASK_RAY_H
