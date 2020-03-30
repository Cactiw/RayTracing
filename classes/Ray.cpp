//
// Created by cactiw on 23.03.2020.
//

#include "Ray.h"

Ray::Ray(Vec3f bp, Vec3f tp): beginPoint(bp), targetPoint(tp) {
    direction = (targetPoint - beginPoint).normalize();
}


Vec3f Ray::getBeginPoint() const {
    return this->beginPoint;
}

Vec3f Ray::getTargetPoint() const {
    return this->targetPoint;
}

Vec3f Ray::getDirection() const {
    return this->direction;
}
