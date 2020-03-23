//
// Created by cactiw on 23.03.2020.
//

#include "Ray.h"

Vec3f Ray::getBeginPoint() const {
    return this->beginPoint;
}

Vec3f Ray::getTargetPoint() const {
    return this->targetPoint;
}
